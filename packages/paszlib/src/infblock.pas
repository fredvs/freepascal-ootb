unit infblock;

{ infblock.h and
  infblock.c -- interpret and process block types to last block
  Copyright (C) 1995-1998 Mark Adler

  Pascal tranlastion
  Copyright (C) 1998 by Jacques Nomssi Nzali
  For conditions of distribution and use, see copyright notice in readme.txt
}

interface

{$I zconf.inc}

uses
  zbase;

function inflate_blocks_new(var z : z_stream;
                            c : check_func;  { check function }
                            w : cardinal     { window size }
                            ) : pInflate_blocks_state;

function inflate_blocks (var s : inflate_blocks_state;
                         var z : z_stream;
                         r : integer             { initial return code }
                         ) : integer;

procedure inflate_blocks_reset (var s : inflate_blocks_state;
                                var z : z_stream;
                                c : Pcardinal); { check value on output }


function inflate_blocks_free(var s : pInflate_blocks_state;
                             var z : z_stream) : integer;

procedure inflate_set_dictionary(var s : inflate_blocks_state;
                                 const d : array of byte;  { dictionary }
                                 n : cardinal);         { dictionary length }

function inflate_blocks_sync_point(var s : inflate_blocks_state) : integer;

implementation

uses
  infcodes, inftrees, infutil{$IFDEF ZLIB_DEBUG}, SysUtils{$ENDIF};

{ Tables for deflate from PKZIP's appnote.txt. }
Const
  border : array [0..18] of word  { Order of the bit length code lengths }
    = (16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15);

{ Notes beyond the 1.93a appnote.txt:

   1. Distance pointers never point before the beginning of the output
      stream.
   2. Distance pointers can point back across blocks, up to 32k away.
   3. There is an implied maximum of 7 bits for the bit length table and
      15 bits for the actual data.
   4. If only one code exists, then it is encoded using one bit.  (Zero
      would be more efficient, but perhaps a little confusing.)  If two
      codes exist, they are coded using one bit each (0 and 1).
   5. There is no way of sending zero distance codes--a dummy must be
      sent if there are none.  (History: a pre 2.0 version of PKZIP would
      store blocks with no distance codes, but this was discovered to be
      too harsh a criterion.)  Valid only for 1.93a.  2.04c does allow
      zero distance codes, which is sent as one code of zero bits in
      length.
   6. There are up to 286 literal/length codes.  Code 256 represents the
      end-of-block.  Note however that the static length tree defines
      288 codes just to fill out the Huffman codes.  Codes 286 and 287
      cannot be used though, since there is no length base or extra bits
      defined for them.  Similarily, there are up to 30 distance codes.
      However, static trees define 32 codes (all 5 bits) to fill out the
      Huffman codes, but the last two had better not show up in the data.
   7. Unzip can check dynamic Huffman blocks for complete code sets.
      The exception is that a single code would not be complete (see #4).
   8. The five bits following the block type is really the number of
      literal codes sent minus 257.
   9. Length codes 8,16,16 are interpreted as 13 length codes of 8 bits
      (1+6+6).  Therefore, to output three times the length, you output
      three codes (1+1+1), whereas to output four times the same length,
      you only need two codes (1+3).  Hmm.
  10. In the tree reconstruction algorithm, Code = Code + Increment
      only if BitLength(i) is not zero.  (Pretty obvious.)
  11. Correction: 4 Bits: # of Bit Length codes - 4     (4 - 19)
  12. Note: length code 284 can represent 227-258, but length code 285
      really is 258.  The last length deserves its own, short code
      since it gets used a lot in very redundant files.  The length
      258 is special since 258 - 3 (the min match length) is 255.
  13. The literal/length and distance code bit lengths are read as a
      single stream of lengths.  It is possible (and advantageous) for
      a repeat code (16, 17, or 18) to go across the boundary between
      the two sets of lengths. }


procedure inflate_blocks_reset (var s : inflate_blocks_state;
                                var z : z_stream;
                                c : Pcardinal); { check value on output }
begin
  if (c <> nil) then
    c^ := s.check;
  if (s.mode = BTREE) or (s.mode = DTREE) then
  begin
    freemem(s.sub.trees.blens);
    s.sub.trees.blens := nil;
  end;
  if (s.mode = CODES) then
    inflate_codes_free(s.sub.decode.codes, z);

  s.mode := ZTYPE;
  s.bitk := 0;
  s.bitb := 0;

  s.write := s.window;
  s.read := s.window;
  if Assigned(s.checkfn) then
  begin
    s.check := s.checkfn(cardinal(0), nil, 0);
    z.adler := s.check;
  end;
  {$IFDEF ZLIB_DEBUG}
  Tracev('inflate:   blocks reset');
  {$ENDIF}
end;


function inflate_blocks_new(var z : z_stream;
                            c : check_func;  { check function }
                            w : cardinal         { window size }
                            ) : pInflate_blocks_state;
var
  s : pInflate_blocks_state;
begin
  new(s);
  if (s = nil) then
  begin
    inflate_blocks_new := s;
    exit;
  end;
  getmem(s^.hufts,sizeof(inflate_huft)*MANY);

  if (s^.hufts = nil) then
  begin
    dispose(s);
    inflate_blocks_new := nil;
    exit;
  end;

  getmem(s^.window,w);
  if (s^.window = nil) then
  begin
    freemem(s^.hufts);
    dispose(s);
    inflate_blocks_new := nil;
    exit;
  end;
  s^.zend := s^.window;
  Inc(s^.zend, w);
  s^.checkfn := c;
  s^.mode := ZTYPE;
  {$IFDEF ZLIB_DEBUG}  
  Tracev('inflate:   blocks allocated');
  {$ENDIF}
  inflate_blocks_reset(s^, z, nil);
  inflate_blocks_new := s;
end;


function inflate_blocks (var s : inflate_blocks_state;
                         var z : z_stream;
                         r : integer) : integer;           { initial return code }

Type
  tblockaction = (baFallThrough,baContinue,baExit);

var
  t : cardinal;               { temporary storage }
  b : cardinal;              { bit buffer }
  k : cardinal;               { bits in bit buffer }
  p : Pbyte;             { input data pointer }
  n : cardinal;               { bytes available there }
  q : Pbyte;             { output window write pointer }
  m : cardinal;               { bytes to end of window or read pointer }
{ fixed code blocks }
var
  bl, bd : cardinal;
  tl, td : pInflate_huft;
var
  h : pInflate_huft;
  i, j, c : cardinal;
var
  cs : pInflate_codes_state;
  
  function do_btree : TBlockAction;
  
  begin
    while (s.sub.trees.index < 4 + (s.sub.trees.table shr 10)) do
    begin
      {NEEDBITS(3);}
      while (k < 3) do
      begin
        {NEEDBYTE;}
        if (n <> 0) then
          r :=Z_OK
        else
        begin
          {UPDATE}
          s.bitb := b;
          s.bitk := k;
          z.avail_in := n;
          Inc(z.total_in, ptruint(p)-ptruint(z.next_in));
          z.next_in := p;
          s.write := q;
          inflate_blocks := inflate_flush(s,z,r);
          exit(baExit);
        end;
        dec(n);
        b := b or (cardinal(p^) shl k);
        Inc(p);
        Inc(k, 8);
      end;

      s.sub.trees.blens^[border[s.sub.trees.index]] := cardinal(b) and 7;
      Inc(s.sub.trees.index);
      {DUMPBITS(3);}
      b := b shr 3;
      dec(k, 3);
    end;
    while (s.sub.trees.index < 19) do
    begin
      s.sub.trees.blens^[border[s.sub.trees.index]] := 0;
      Inc(s.sub.trees.index);
    end;
    s.sub.trees.bb := 7;
    t := inflate_trees_bits(s.sub.trees.blens^, s.sub.trees.bb,
                            s.sub.trees.tb, s.hufts^, z);
    if (t <> Z_OK) then
    begin
      freemem(s.sub.trees.blens);
      s.sub.trees.blens := nil;
      r := t;
      if (r = Z_DATA_ERROR) then
        s.mode := BLKBAD;
      { update pointers and return }
      s.bitb := b;
      s.bitk := k;
      z.avail_in := n;
      Inc(z.total_in, ptruint(p) - ptruint(z.next_in));
      z.next_in := p;
      s.write := q;
      inflate_blocks := inflate_flush(s,z,r);
      exit(baExit);
    end;
    s.sub.trees.index := 0;
    {$IFDEF ZLIB_DEBUG}
    Tracev('inflate:       bits tree ok');
    {$ENDIF}
    s.mode := DTREE;
    { fall through again }
    do_btree:=baFallThrough;
  end;
  
  function do_dtree : TBlockaction;
  
  begin
    while TRUE do
    begin
      t := s.sub.trees.table;
      if not (s.sub.trees.index < 258 +
                                 (t and $1f) + ((t shr 5) and $1f)) then
        break;
      t := s.sub.trees.bb;
      {NEEDBITS(t);}
      while (k < t) do
      begin
        {NEEDBYTE;}
        if (n <> 0) then
          r :=Z_OK
        else
        begin
          {UPDATE}
          s.bitb := b;
          s.bitk := k;
          z.avail_in := n;
          Inc(z.total_in, ptruint(p)-ptruint(z.next_in));
          z.next_in := p;
          s.write := q;
          inflate_blocks := inflate_flush(s,z,r);
          exit(baExit);
        end;
        dec(n);
        b := b or (cardinal(p^) shl k);
        Inc(p);
        Inc(k, 8);
      end;

      h := s.sub.trees.tb;
      Inc(h, cardinal(b) and inflate_mask[t]);
      t := h^.Bits;
      c := h^.Base;

      if (c < 16) then
      begin
        {DUMPBITS(t);}
        b := b shr t;
        dec(k, t);

        s.sub.trees.blens^[s.sub.trees.index] := c;
        Inc(s.sub.trees.index);
      end
      else { c = 16..18 }
      begin
        if c = 18 then
        begin
          i := 7;
          j := 11;
        end
        else
        begin
          i := c - 14;
          j := 3;
        end;
        {NEEDBITS(t + i);}
        while (k < t + i) do
        begin
          {NEEDBYTE;}
          if (n <> 0) then
            r :=Z_OK
          else
          begin
            {UPDATE}
            s.bitb := b;
            s.bitk := k;
            z.avail_in := n;
            Inc(z.total_in, ptruint(p)-ptruint(z.next_in));
            z.next_in := p;
            s.write := q;
            inflate_blocks := inflate_flush(s,z,r);
            exit(baExit);
          end;
          dec(n);
          b := b or (cardinal(p^) shl k);
          Inc(p);
          Inc(k, 8);
        end;

        {DUMPBITS(t);}
        b := b shr t;
        dec(k, t);

        Inc(j, cardinal(b) and inflate_mask[i]);
        {DUMPBITS(i);}
        b := b shr i;
        dec(k, i);

        i := s.sub.trees.index;
        t := s.sub.trees.table;
        if (i + j > 258 + (t and $1f) + ((t shr 5) and $1f)) or
           ((c = 16) and (i < 1)) then
        begin
          freemem(s.sub.trees.blens);
          s.sub.trees.blens := nil;
          s.mode := BLKBAD;
          z.msg := 'invalid bit length repeat';
          r := Z_DATA_ERROR;
          { update pointers and return }
          s.bitb := b;
          s.bitk := k;
          z.avail_in := n;
          Inc(z.total_in, ptruint(p) - ptruint(z.next_in));
          z.next_in := p;
          s.write := q;
          inflate_blocks := inflate_flush(s,z,r);
          exit(baExit);
        end;
        if c = 16 then
          c := s.sub.trees.blens^[i - 1]
        else
          c := 0;
        repeat
          s.sub.trees.blens^[i] := c;
          Inc(i);
          dec(j);
        until (j=0);
        s.sub.trees.index := i;
      end;
    end; { while }
    s.sub.trees.tb := nil;
    begin
      bl := 9;         { must be <= 9 for lookahead assumptions }
      bd := 6;         { must be <= 9 for lookahead assumptions }
      t := s.sub.trees.table;
      t := inflate_trees_dynamic(257 + (t and $1f),
              1 + ((t shr 5) and $1f),
              s.sub.trees.blens^, bl, bd, tl, td, s.hufts^, z);
      freemem(s.sub.trees.blens);
      s.sub.trees.blens := nil;
      if (t <> Z_OK) then
      begin
        if (t = cardinal(Z_DATA_ERROR)) then
          s.mode := BLKBAD;
        r := t;
        { update pointers and return }
        s.bitb := b;
        s.bitk := k;
        z.avail_in := n;
        Inc(z.total_in, ptruint(p) - ptruint(z.next_in));
        z.next_in := p;
        s.write := q;
        inflate_blocks := inflate_flush(s,z,r);
        exit(baExit);
      end;
      {$IFDEF ZLIB_DEBUG}
      Tracev('inflate:       trees ok');
      {$ENDIF}          
      { c renamed to cs }
      cs := inflate_codes_new(bl, bd, tl, td, z);
      if (cs = nil) then
      begin
        r := Z_MEM_ERROR;
        { update pointers and return }
        s.bitb := b;
        s.bitk := k;
        z.avail_in := n;
        Inc(z.total_in, ptruint(p) - ptruint(z.next_in));
        z.next_in := p;
        s.write := q;
        inflate_blocks := inflate_flush(s,z,r);
        exit(baExit);
      end;
      s.sub.decode.codes := cs;
    end;
    s.mode := CODES;
    do_dtree:=baFallThrough;
  end;


  function do_codes: tblockaction;
  
  begin
    { update pointers }
    s.bitb := b;
    s.bitk := k;
    z.avail_in := n;
    Inc(z.total_in, ptruint(p) - ptruint(z.next_in));
    z.next_in := p;
    s.write := q;

    r := inflate_codes(s, z, r);
    if (r <> Z_STREAM_END) then
    begin
      inflate_blocks := inflate_flush(s, z, r);
      exit(baExit);
    end;
    r := Z_OK;
    inflate_codes_free(s.sub.decode.codes, z);
    { load local pointers }
    p := z.next_in;
    n := z.avail_in;
    b := s.bitb;
    k := s.bitk;
    q := s.write;
    if ptruint(q) < ptruint(s.read) then
      m := cardinal(ptruint(s.read)-ptruint(q)-1)
    else
      m := cardinal(ptruint(s.zend)-ptruint(q));
    {$IFDEF ZLIB_DEBUG}
    if (ptruint(q) >= ptruint(s.read)) then
      Tracev('inflate:       codes end '+
          IntToStr(z.total_out + ptruint(q) - ptruint(s.read)) + ' total out')
    else
      Tracev('inflate:       codes end '+
              IntToStr(z.total_out + ptruint(s.zend) - ptruint(s.read) +
              ptruint(q) - ptruint(s.window)) +  ' total out');
    {$ENDIF}
    if (not s.last) then
    begin
      s.mode := ZTYPE;
      exit(baContinue); { break for switch statement in C-code }
    end;
    {$ifndef patch112}
    if (k > 7) then           { return unused byte, if any }
    begin
      {$IFDEF ZLIB_DEBUG}
      Assert(k < 16, 'inflate_codes grabbed too many bytes');
      {$ENDIF}
      dec(k, 8);
      inc(n);
      dec(p);                    { can always return one }
    end;
    {$endif}
    s.mode := DRY;
    do_codes:=baFallThrough;
  end;

  function do_dry : tblockaction;
  
  begin
    {FLUSH}
    s.write := q;
    r := inflate_flush(s,z,r);
    q := s.write;

    { not needed anymore, we are done:
    if ptruint(q) < ptruint(s.read) then
      m := cardinal(ptruint(s.read)-ptruint(q)-1)
    else
      m := cardinal(ptruint(s.zend)-ptruint(q));
    }

    if (s.read <> s.write) then
    begin
      { update pointers and return }
      s.bitb := b;
      s.bitk := k;
      z.avail_in := n;
      Inc(z.total_in, ptruint(p) - ptruint(z.next_in));
      z.next_in := p;
      s.write := q;
      inflate_blocks := inflate_flush(s,z,r);
      exit(baExit);
    end;
    s.mode := BLKDONE;
    do_dry:=baFallThrough;
  end;

  procedure do_blkdone;
    
  begin
    r := Z_STREAM_END;
    { update pointers and return }
    s.bitb := b;
    s.bitk := k;
    z.avail_in := n;
    Inc(z.total_in, ptruint(p) - ptruint(z.next_in));
    z.next_in := p;
    s.write := q;
    inflate_blocks := inflate_flush(s,z,r);
  end;
  
begin
  { copy input/output information to locals }
  p := z.next_in;
  n := z.avail_in;
  b := s.bitb;
  k := s.bitk;
  q := s.write;
  if ptruint(q) < ptruint(s.read) then
    m := cardinal(ptruint(s.read)-ptruint(q)-1)
  else
    m := cardinal(ptruint(s.zend)-ptruint(q));

{ decompress an inflated block }


  { process input based on current state }
  while True do
  Case s.mode of
    ZTYPE:
      begin
        {NEEDBITS(3);}
        while (k < 3) do
        begin
          {NEEDBYTE;}
          if (n <> 0) then
            r :=Z_OK
          else
          begin
            {UPDATE}
            s.bitb := b;
            s.bitk := k;
            z.avail_in := n;
            Inc(z.total_in, ptruint(p)-ptruint(z.next_in));
            z.next_in := p;
            s.write := q;
            inflate_blocks := inflate_flush(s,z,r);
            exit;
          end;
          dec(n);
          b := b or (cardinal(p^) shl k);
          Inc(p);
          Inc(k, 8);
        end;

        t := cardinal(b) and 7;
        s.last := boolean(t and 1);
        case (t shr 1) of
          0:                         { stored }
            begin
              {$IFDEF ZLIB_DEBUG}
              if s.last then
                Tracev('inflate:     stored block (last)')
              else
                Tracev('inflate:     stored block');
              {$ENDIF}
              {DUMPBITS(3);}
              b := b shr 3;
              dec(k, 3);

              t := k and 7;                  { go to byte boundary }
              {DUMPBITS(t);}
              b := b shr t;
              dec(k, t);

              s.mode := LENS;                { get length of stored block }
            end;
          1:                         { fixed }
            begin
              begin
                {$IFDEF ZLIB_DEBUG}
                if s.last then
                  Tracev('inflate:     fixed codes blocks (last)')
                else
                  Tracev('inflate:     fixed codes blocks');
                {$ENDIF}
                inflate_trees_fixed(bl, bd, tl, td, z);
                s.sub.decode.codes := inflate_codes_new(bl, bd, tl, td, z);
                if (s.sub.decode.codes = nil) then
                begin
                  r := Z_MEM_ERROR;
                  { update pointers and return }
                  s.bitb := b;
                  s.bitk := k;
                  z.avail_in := n;
                  Inc(z.total_in, ptruint(p) - ptruint(z.next_in));
                  z.next_in := p;
                  s.write := q;
                  inflate_blocks := inflate_flush(s,z,r);
                  exit;
                end;
              end;
              {DUMPBITS(3);}
              b := b shr 3;
              dec(k, 3);

              s.mode := CODES;
            end;
          2:                         { dynamic }
            begin
              {$IFDEF ZLIB_DEBUG}
              if s.last then
                Tracev('inflate:     dynamic codes block (last)')
              else
                Tracev('inflate:     dynamic codes block');
              {$ENDIF}                
              {DUMPBITS(3);}
              b := b shr 3;
              dec(k, 3);

              s.mode := TABLE;
            end;
          3:
            begin                   { illegal }
              {DUMPBITS(3);}
              b := b shr 3;
              dec(k, 3);

              s.mode := BLKBAD;
              z.msg := 'invalid block type';
              r := Z_DATA_ERROR;
              { update pointers and return }
              s.bitb := b;
              s.bitk := k;
              z.avail_in := n;
              Inc(z.total_in, ptruint(p) - ptruint(z.next_in));
              z.next_in := p;
              s.write := q;
              inflate_blocks := inflate_flush(s,z,r);
              exit;
            end;
        end;
      end;
    LENS:
      begin
        {NEEDBITS(32);}
        while (k < 32) do
        begin
          {NEEDBYTE;}
          if (n <> 0) then
            r :=Z_OK
          else
          begin
            {UPDATE}
            s.bitb := b;
            s.bitk := k;
            z.avail_in := n;
            Inc(z.total_in, ptruint(p)-ptruint(z.next_in));
            z.next_in := p;
            s.write := q;
            inflate_blocks := inflate_flush(s,z,r);
            exit;
          end;
          dec(n);
          b := b or (cardinal(p^) shl k);
          Inc(p);
          Inc(k, 8);
        end;

        if (((not b) shr 16) and $ffff) <> (b and $ffff) then
        begin
          s.mode := BLKBAD;
          z.msg := 'invalid stored block lengths';
          r := Z_DATA_ERROR;
          { update pointers and return }
          s.bitb := b;
          s.bitk := k;
          z.avail_in := n;
          Inc(z.total_in, ptruint(p) - ptruint(z.next_in));
          z.next_in := p;
          s.write := q;
          inflate_blocks := inflate_flush(s,z,r);
          exit;
        end;
        s.sub.left := cardinal(b) and $ffff;
        k := 0;
        b := 0;                      { dump bits }
        {$IFDEF ZLIB_DEBUG}
        Tracev('inflate:       stored length '+IntToStr(s.sub.left));
        {$ENDIF}
        if s.sub.left <> 0 then
          s.mode := STORED
        else
          if s.last then
            s.mode := DRY
          else
            s.mode := ZTYPE;
      end;
    STORED:
      begin
        if (n = 0) then
        begin
          { update pointers and return }
          s.bitb := b;
          s.bitk := k;
          z.avail_in := n;
          Inc(z.total_in, ptruint(p) - ptruint(z.next_in));
          z.next_in := p;
          s.write := q;
          inflate_blocks := inflate_flush(s,z,r);
          exit;
        end;
        {NEEDOUT}
        if (m = 0) then
        begin
          {WRAP}
          if (q = s.zend) and (s.read <> s.window) then
          begin
            q := s.window;
            if ptruint(q) < ptruint(s.read) then
              m := cardinal(ptruint(s.read)-ptruint(q)-1)
            else
              m := cardinal(ptruint(s.zend)-ptruint(q));
          end;

          if (m = 0) then
          begin
            {FLUSH}
            s.write := q;
            r := inflate_flush(s,z,r);
            q := s.write;
            if ptruint(q) < ptruint(s.read) then
              m := cardinal(ptruint(s.read)-ptruint(q)-1)
            else
              m := cardinal(ptruint(s.zend)-ptruint(q));

            {WRAP}
            if (q = s.zend) and (s.read <> s.window) then
            begin
              q := s.window;
              if ptruint(q) < ptruint(s.read) then
                m := cardinal(ptruint(s.read)-ptruint(q)-1)
              else
                m := cardinal(ptruint(s.zend)-ptruint(q));
            end;

            if (m = 0) then
            begin
              {UPDATE}
              s.bitb := b;
              s.bitk := k;
              z.avail_in := n;
              Inc(z.total_in, ptruint(p)-ptruint(z.next_in));
              z.next_in := p;
              s.write := q;
              inflate_blocks := inflate_flush(s,z,r);
              exit;
            end;
          end;
        end;
        r := Z_OK;

        t := s.sub.left;
        if (t > n) then
          t := n;
        if (t > m) then
          t := m;
        move(p^,q^,t);
        inc(p, t);  dec(n, t);
        inc(q, t);  dec(m, t);
        dec(s.sub.left, t);
        if (s.sub.left = 0) then
        begin
          {$IFDEF ZLIB_DEBUG}
          if (ptruint(q) >= ptruint(s.read)) then
            Tracev('inflate:       stored end '+
                IntToStr(z.total_out + ptruint(q) - ptruint(s.read)) + ' total out')
          else
            Tracev('inflate:       stored end '+
                    IntToStr(z.total_out + ptruint(s.zend) - ptruint(s.read) +
                    ptruint(q) - ptruint(s.window)) +  ' total out');
          {$ENDIF}
          if s.last then
            s.mode := DRY
          else
            s.mode := ZTYPE;
        end;
      end;
    TABLE:
      begin
        {NEEDBITS(14);}
        while (k < 14) do
        begin
          {NEEDBYTE;}
          if (n <> 0) then
            r :=Z_OK
          else
          begin
            {UPDATE}
            s.bitb := b;
            s.bitk := k;
            z.avail_in := n;
            Inc(z.total_in, ptruint(p)-ptruint(z.next_in));
            z.next_in := p;
            s.write := q;
            inflate_blocks := inflate_flush(s,z,r);
            exit;
          end;
          dec(n);
          b := b or (cardinal(p^) shl k);
          Inc(p);
          Inc(k, 8);
        end;

        t := cardinal(b) and $3fff;
        s.sub.trees.table := t;
  {$ifndef PKZIP_BUG_WORKAROUND}
        if ((t and $1f) > 29) or (((t shr 5) and $1f) > 29) then
        begin
          s.mode := BLKBAD;
          z.msg := 'too many length or distance symbols';
          r := Z_DATA_ERROR;
          { update pointers and return }
          s.bitb := b;
          s.bitk := k;
          z.avail_in := n;
          Inc(z.total_in, ptruint(p) - ptruint(z.next_in));
          z.next_in := p;
          s.write := q;
          inflate_blocks := inflate_flush(s,z,r);
          exit;
        end;
  {$endif}
        t := 258 + (t and $1f) + ((t shr 5) and $1f);
        getmem(s.sub.trees.blens,t*sizeof(cardinal));
        if (s.sub.trees.blens = nil) then
        begin
          r := Z_MEM_ERROR;
          { update pointers and return }
          s.bitb := b;
          s.bitk := k;
          z.avail_in := n;
          Inc(z.total_in, ptruint(p) - ptruint(z.next_in));
          z.next_in := p;
          s.write := q;
          inflate_blocks := inflate_flush(s,z,r);
          exit;
        end;
        {DUMPBITS(14);}
        b := b shr 14;
        dec(k, 14);

        s.sub.trees.index := 0;
        {$IFDEF ZLIB_DEBUG}
        Tracev('inflate:       table sizes ok');
        {$ENDIF}
        s.mode := BTREE;
        { fall trough case is handled by the while }
        { try GOTO for speed - Nomssi }
        if do_btree=baExit then
          Exit;
        if do_dtree=baExit then
          Exit;
        Case do_codes of
          baContinue : continue;
          baExit : Exit;
        end;
        if do_dry=baExit then
          exit;
        do_blkdone;
        exit;
      end;
    BTREE:
      begin
        if do_btree=baExit then
          Exit;
        if do_dtree=baExit then
          Exit;
        Case do_codes of
          baContinue : continue;
          baExit : Exit;
        end;
        if do_dry=baExit then
          exit;
        do_blkdone;
        exit;
      end;
    DTREE:
      begin
        if do_dtree=baExit then
          Exit;
        Case do_codes of
          baContinue : continue;
          baExit : Exit;
        end;
        if do_dry=baExit then
          exit;
        do_blkdone;
        exit;
      end;
    CODES:
      begin
        Case do_codes of
          baContinue : continue;
          baExit : Exit;
        end;
        if do_dry=baExit then
          exit;
        do_blkdone;
        exit;
      end;
    DRY:
      begin
        if do_dry=baExit then
          exit;
        do_blkdone;
        exit;
      end;
    BLKDONE:
      begin
        do_blkdone;
        exit;
      end;
    BLKBAD:
      begin
        r := Z_DATA_ERROR;
        { update pointers and return }
        s.bitb := b;
        s.bitk := k;
        z.avail_in := n;
        Inc(z.total_in, ptruint(p) - ptruint(z.next_in));
        z.next_in := p;
        s.write := q;
        inflate_blocks := inflate_flush(s,z,r);
        exit;
      end;
    else
    begin
      r := Z_STREAM_ERROR;
      { update pointers and return }
      s.bitb := b;
      s.bitk := k;
      z.avail_in := n;
      Inc(z.total_in, ptruint(p) - ptruint(z.next_in));
      z.next_in := p;
      s.write := q;
      inflate_blocks := inflate_flush(s,z,r);
      exit;
    end;
  end; { Case s.mode of }

end;


function inflate_blocks_free(var s : pInflate_blocks_state;
                             var z : z_stream) : integer;
begin
  inflate_blocks_reset(s^, z, nil);
  freemem(s^.window);
  freemem(s^.hufts);
  dispose(s);
  s := nil;
  {$IFDEF ZLIB_DEBUG}
  Trace('inflate:   blocks freed');
  {$ENDIF}  
  inflate_blocks_free := Z_OK;
end;


procedure inflate_set_dictionary(var s : inflate_blocks_state;
                                 const d : array of byte; { dictionary }
                                 n : cardinal);         { dictionary length }
begin
  move(d,s.window^,n);
  s.write := s.window;
  inc(s.write, n);
  s.read := s.write;
end;


{ Returns true if inflate is currently at the end of a block generated
  by Z_SYNC_FLUSH or Z_FULL_FLUSH.
  IN assertion: s <> nil }

function inflate_blocks_sync_point(var s : inflate_blocks_state) : integer;
begin
  inflate_blocks_sync_point := integer(s.mode = LENS);
end;

end.
