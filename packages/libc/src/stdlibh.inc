
type

   Pdiv_t = ^div_t;
   div_t = record
        quot : longint;
        rem : longint;
     end;

   Pldiv_t = ^ldiv_t;
   ldiv_t = record
        quot : longint;
        rem : longint;
     end;

   Plldiv_t = ^lldiv_t;
   lldiv_t = record
        quot : int64;
        rem : int64;
     end;

const
   RAND_MAX = 2147483647;
   EXIT_FAILURE = 1;
   EXIT_SUCCESS = 0;

function MB_CUR_MAX : size_t;cdecl; external clib name '__ctype_get_mb_cur_max' + LIBC_SUFFIX ;
function __ctype_get_mb_cur_max:size_t;cdecl;external clib name '__ctype_get_mb_cur_max' + LIBC_SUFFIX ;
function atof(__nptr:Pchar):double;cdecl;external clib name 'atof' + LIBC_SUFFIX ;
function atoi(__nptr:Pchar):longint;cdecl;external clib name 'atoi' + LIBC_SUFFIX ;
function atol(__nptr:Pchar):longint;cdecl;external clib name 'atol' + LIBC_SUFFIX ;
function atoll(__nptr:Pchar):int64;cdecl;external clib name 'atoll' + LIBC_SUFFIX ;
function strtod(__nptr:Pchar; __endptr:PPchar):double;cdecl;external clib name 'strtod' + LIBC_SUFFIX ;
function strtof(__nptr:Pchar; __endptr:PPchar):double;cdecl;external clib name 'strtof' + LIBC_SUFFIX ;
function strtold(NumPtr: PChar; EndPtr: PPChar): Extended; cdecl; external clib name 'strtold' + LIBC_SUFFIX ;
function strtol(__nptr:Pchar; __endptr:PPchar; __base:longint):longint;cdecl;external clib name 'strtol' + LIBC_SUFFIX ;
function strtoul(__nptr:Pchar; __endptr:PPchar; __base:longint):dword;cdecl;external clib name 'strtoul' + LIBC_SUFFIX ;
function strtoq(__nptr:Pchar; __endptr:PPchar; __base:longint):int64;cdecl;external clib name 'strtoq' + LIBC_SUFFIX ;
function strtouq(__nptr:Pchar; __endptr:PPchar; __base:longint):qword;cdecl;external clib name 'strtouq' + LIBC_SUFFIX ;
function strtoll(__nptr:Pchar; __endptr:PPchar; __base:longint):int64;cdecl;external clib name 'strtoll' + LIBC_SUFFIX ;
function strtoull(__nptr:Pchar; __endptr:PPchar; __base:longint):qword;cdecl;external clib name 'strtoull' + LIBC_SUFFIX ;
function __strtol_l(__nptr:Pchar; __endptr:PPchar; __base:longint; __loc:__locale_t):longint;cdecl;external clib name '__strtol_l' + LIBC_SUFFIX ;
function __strtoul_l(__nptr:Pchar; __endptr:PPchar; __base:longint; __loc:__locale_t):dword;cdecl;external clib name '__strtoul_l' + LIBC_SUFFIX ;
function __strtoll_l(__nptr:Pchar; __endptr:PPchar; __base:longint; __loc:__locale_t):int64;cdecl;external clib name '__strtoll_l' + LIBC_SUFFIX ;
function __strtoull_l(__nptr:Pchar; __endptr:PPchar; __base:longint; __loc:__locale_t):qword;cdecl;external clib name '__strtoull_l' + LIBC_SUFFIX ;
function __strtod_l(__nptr:Pchar; __endptr:PPchar; __loc:__locale_t):double;cdecl;external clib name '__strtod_l' + LIBC_SUFFIX ;
function __strtof_l(__nptr:Pchar; __endptr:PPchar; __loc:__locale_t):double;cdecl;external clib name '__strtof_l' + LIBC_SUFFIX ;
function __strtold_l(__nptr: PChar; __endptr: PPChar;__loc: __locale_t): Extended; cdecl;external clib name '__strtold_l' + LIBC_SUFFIX ;
function __strtod_internal(__nptr:Pchar; __endptr:PPchar; __group:longint):double;cdecl;external clib name '__strtod_internal' + LIBC_SUFFIX ;
function __strtof_internal(__nptr:Pchar; __endptr:PPchar; __group:longint):double;cdecl;external clib name '__strtof_internal' + LIBC_SUFFIX ;
function __strtold_internal(__nptr: PChar; __endptr: PPChar;  __group: longint): Extended; cdecl;external clib name '__strtold_internal' + LIBC_SUFFIX ;
function __strtol_internal(__nptr:Pchar; __endptr:PPchar; __base:longint; __group:longint):longint;cdecl;external clib name '__strtol_internal' + LIBC_SUFFIX ;
function __strtoul_internal(__nptr:Pchar; __endptr:PPchar; __base:longint; __group:longint):dword;cdecl;external clib name '__strtoul_internal' + LIBC_SUFFIX ;
function __strtoll_internal(__nptr:Pchar; __endptr:PPchar; __base:longint; __group:longint):int64;cdecl;external clib name '__strtoll_internal' + LIBC_SUFFIX ;
function __strtoull_internal(__nptr:Pchar; __endptr:PPchar; __base:longint; __group:longint):qword;cdecl;external clib name '__strtoull_internal' + LIBC_SUFFIX ;
function a64l(__s:Pchar):longint;cdecl;external clib name 'a64l' + LIBC_SUFFIX ;
function l64a(N: longint): PChar; cdecl;external clib name 'l64a' + LIBC_SUFFIX ;

function __random:longint;cdecl;external clib name 'random' + LIBC_SUFFIX ;
procedure srandom(__seed:dword);cdecl;external clib name 'srandom' + LIBC_SUFFIX ;
function initstate(__seed:dword; __statebuf:Pchar; __statelen:size_t):Pchar;cdecl;external clib name 'initstate' + LIBC_SUFFIX ;
function setstate(__statebuf:Pchar):Pchar;cdecl;external clib name 'setstate' + LIBC_SUFFIX ;

Type
  Prandom_data = ^random_data;
  random_data = record
       fptr : Pint32_t;
       rptr : Pint32_t;
       state : Pint32_t;
       rand_type : longint;
       rand_deg : longint;
       rand_sep : longint;
       end_ptr : Pint32_t;
    end;


function random_r(__buf:Prandom_data; __result:Pint32_t):longint;cdecl;external clib name 'random_r' + LIBC_SUFFIX ;
function srandom_r(__seed:dword; __buf:Prandom_data):longint;cdecl;external clib name 'srandom_r' + LIBC_SUFFIX ;
function initstate_r(__seed:dword; __statebuf:Pchar; __statelen:size_t; __buf:Prandom_data):longint;cdecl;external clib name 'initstate_r' + LIBC_SUFFIX ;
function setstate_r(__statebuf:Pchar; __buf:Prandom_data):longint;cdecl;external clib name 'setstate_r' + LIBC_SUFFIX ;
function rand:longint;cdecl;external clib name 'rand' + LIBC_SUFFIX ;
procedure srand(__seed:dword);cdecl;external clib name 'srand' + LIBC_SUFFIX ;
function rand_r(__seed:Pdword):longint;cdecl;external clib name 'rand_r' + LIBC_SUFFIX ;
function drand48:double;cdecl;external clib name 'drand48' + LIBC_SUFFIX ;

Type
  TRandWordArray = Array[0..2] of word;

function erand48(var __xsubi: trandwordarray):double;cdecl;external clib name 'erand48' + LIBC_SUFFIX ;
function lrand48:longint;cdecl;external clib name 'lrand48' + LIBC_SUFFIX ;
function nrand48(var __xsubi: trandwordarray):longint;cdecl;external clib name 'nrand48' + LIBC_SUFFIX ;
function mrand48:longint;cdecl;external clib name 'mrand48' + LIBC_SUFFIX ;
function jrand48(var __xsubi:trandwordarray):longint;cdecl;external clib name 'jrand48' + LIBC_SUFFIX ;
procedure srand48(__seedval:longint);cdecl;external clib name 'srand48' + LIBC_SUFFIX ;
function seed48(var __seed16v:trandwordarray):Pword;cdecl;external clib name 'seed48' + LIBC_SUFFIX ;
procedure lcong48(var __param:trandwordarray);cdecl;external clib name 'lcong48' + LIBC_SUFFIX ;

type
  Pdrand48_data = ^drand48_data;
  drand48_data = record
       __x : array[0..2] of word;
       __old_x : array[0..2] of word;
       __c : word;
       __init : word;
       __a : qword;
    end;

function drand48_r(__buffer:Pdrand48_data; __result:Pdouble):longint;cdecl;external clib name 'drand48_r' + LIBC_SUFFIX ;
function erand48_r(var __xsubi: TRandWordArray; __buffer:Pdrand48_data; __result:Pdouble):longint;cdecl;external clib name 'erand48_r' + LIBC_SUFFIX ;
function lrand48_r(__buffer:Pdrand48_data; __result:Plongint):longint;cdecl;external clib name 'lrand48_r' + LIBC_SUFFIX ;
function nrand48_r(var __xsubi: TRandWordArray; __buffer:Pdrand48_data; __result:Plongint):longint;cdecl;external clib name 'nrand48_r' + LIBC_SUFFIX ;
function mrand48_r(__buffer:Pdrand48_data; __result:Plongint):longint;cdecl;external clib name 'mrand48_r' + LIBC_SUFFIX ;
function jrand48_r(var __xsubi: TRandWordArray; __buffer:Pdrand48_data; __result:Plongint):longint;cdecl;external clib name 'jrand48_r' + LIBC_SUFFIX ;
function srand48_r(__seedval:longint; __buffer:Pdrand48_data):longint;cdecl;external clib name 'srand48_r' + LIBC_SUFFIX ;
function seed48_r(var __seed16v: TRandWordArray; __buffer:Pdrand48_data):longint;cdecl;external clib name 'seed48_r' + LIBC_SUFFIX ;
function lcong48_r(__param: pword; __buffer:Pdrand48_data):longint;cdecl;external clib name 'lcong48_r' + LIBC_SUFFIX ;

procedure __abort; cdecl; external clib name 'abort' + LIBC_SUFFIX ;

type
  TAtExitProc = procedure; cdecl;
  TOnExitProc = procedure(status: longint; arg: Pointer); cdecl;

function atexit(__func:TAtExitProc):longint;cdecl;external clib name 'atexit' + LIBC_SUFFIX ;
function on_exit(__func:TOnExitProc; __arg:pointer):longint;cdecl;external clib name 'on_exit' + LIBC_SUFFIX ;
procedure __exit(Status: longint); cdecl;external clib name 'exit' + LIBC_SUFFIX ;
//procedure _Exit (__status : longint);cdecl; external clib name '_exit' + LIBC_SUFFIX ;

function getenv(__name:Pchar):Pchar;cdecl;external clib name 'getenv' + LIBC_SUFFIX ;
function __secure_getenv(__name:Pchar):Pchar;cdecl;external clib name '__secure_getenv' + LIBC_SUFFIX ;
function putenv(__string:Pchar):longint;cdecl;external clib name 'putenv' + LIBC_SUFFIX ;
function setenv(__name:Pchar; __value:Pchar; __replace:longint):longint;cdecl;external clib name 'setenv' + LIBC_SUFFIX ;
function unsetenv(__name:Pchar):longint;cdecl;external clib name 'unsetenv' + LIBC_SUFFIX ;
function clearenv:longint;cdecl;external clib name 'clearenv' + LIBC_SUFFIX ;
function mktemp(__template:Pchar):Pchar;cdecl;external clib name 'mktemp' + LIBC_SUFFIX ;
function mkstemp(__template:Pchar):longint;cdecl;external clib name 'mkstemp' + LIBC_SUFFIX ;
function mkstemp64(__template:Pchar):longint;cdecl;external clib name 'mkstemp64' + LIBC_SUFFIX ;
function mkdtemp(__template:Pchar):Pchar;cdecl;external clib name 'mkdtemp' + LIBC_SUFFIX ;
// **************** detect whether system symbol is hidden. Should be as of 1.9.4
// **************** End of detect
function __system(__command:Pchar):longint;cdecl;external clib name 'system' + LIBC_SUFFIX ;
function system(__command:Pchar):longint;cdecl;external clib name 'system' + LIBC_SUFFIX ;
function canonicalize_file_name(__name:Pchar):Pchar;cdecl;external clib name 'canonicalize_file_name' + LIBC_SUFFIX ;
function realpath(__name:Pchar; __resolved:Pchar):Pchar;cdecl;external clib name 'realpath' + LIBC_SUFFIX ;

Type
  __compar_fn_t = function (_para1:pointer; _para2:pointer):longint;cdecl;
  comparison_fn_t = __compar_fn_t;

function bsearch(__key:pointer; __base:pointer; __nmemb:size_t; __size:size_t; __compar:__compar_fn_t):pointer;cdecl;external clib name 'bsearch' + LIBC_SUFFIX ;
procedure qsort(__base:pointer; __nmemb:size_t; __size:size_t; __compar:__compar_fn_t);cdecl;external clib name 'qsort' + LIBC_SUFFIX ;

function __abs(X: longint): longint; cdecl;external clib name 'abs' + LIBC_SUFFIX ;
function labs(X: Longint): Longint; cdecl;external clib name 'labs' + LIBC_SUFFIX ;
function llabs(X: Int64): Int64; cdecl;external clib name 'llabs' + LIBC_SUFFIX ;
function __div(Numer: longint; Denom: longint): div_t; cdecl;external clib name 'div' + LIBC_SUFFIX ;
function ldiv(Numer: Longint; Denom: Longint): ldiv_t; cdecl;external clib name 'ldiv' + LIBC_SUFFIX ;
function lldiv(Numer: Int64; Denom: Int64): lldiv_t; cdecl;external clib name 'lldiv' + LIBC_SUFFIX ;

function ecvt(__value:double; __ndigit:longint; __decpt:Plongint; __sign:Plongint):Pchar;cdecl;external clib name 'ecvt' + LIBC_SUFFIX ;
function fcvt(__value:double; __ndigit:longint; __decpt:Plongint; __sign:Plongint):Pchar;cdecl;external clib name 'fcvt' + LIBC_SUFFIX ;
function gcvt(__value:double; __ndigit:longint; __buf:Pchar):Pchar;cdecl;external clib name 'gcvt' + LIBC_SUFFIX ;
function qecvt(__value: extended; __ndigit: longint; __decpt: Plongint;  __sign: plongint): PChar; cdecl;external clib name 'qecvt' + LIBC_SUFFIX ;
function qfcvt(__value: extended; __ndigit: longint; __decpt: plongint;  __sign: plongint): PChar; cdecl;external clib name 'qfcvt' + LIBC_SUFFIX ;
function qgcvt(__value: extended; __ndigit: longint;  __buf: PChar): PChar; cdecl;external clib name 'qgcvt' + LIBC_SUFFIX ;

function ecvt_r(__value:double; __ndigit:longint; __decpt:Plongint; __sign:Plongint; __buf:Pchar; __len:size_t):longint;cdecl;external clib name 'ecvt_r' + LIBC_SUFFIX ;
function fcvt_r(__value:double; __ndigit:longint; __decpt:Plongint; __sign:Plongint; __buf:Pchar; __len:size_t):longint;cdecl;external clib name 'fcvt_r' + LIBC_SUFFIX ;
function qecvt_r(Value: Extended; __ndigit: longint; __decpt: Plongint; __sign: plongint; Buf: PChar; Len: size_t): longint; cdecl;external clib name 'qecvt_r' + LIBC_SUFFIX ;
function qfcvt_r(Value: Extended; __ndigit: longint; __decpt: plongint; __sign: plongint; Buf: PChar; Len: size_t): longint; cdecl;external clib name 'qfcvt_r' + LIBC_SUFFIX ;

function mblen(__s:Pchar; __n:size_t):longint;cdecl;external clib name 'mblen' + LIBC_SUFFIX ;
function mbtowc(__pwc:Pwchar_t; __s:Pchar; __n:size_t):longint;cdecl;external clib name 'mbtowc' + LIBC_SUFFIX ;
function wctomb(__s:Pchar; __wchar:wchar_t):longint;cdecl;external clib name 'wctomb' + LIBC_SUFFIX ;
function mbstowcs(__pwcs:Pwchar_t; __s:Pchar; __n:size_t):size_t;cdecl;external clib name 'mbstowcs' + LIBC_SUFFIX ;
function wcstombs(__s:Pchar; __pwcs:Pwchar_t; __n:size_t):size_t;cdecl;external clib name 'wcstombs' + LIBC_SUFFIX ;
function rpmatch(__response:Pchar):longint;cdecl;external clib name 'rpmatch' + LIBC_SUFFIX ;
function getsubopt(__optionp:PPchar; __tokens:PPchar; __valuep:PPchar):longint;cdecl;external clib name 'getsubopt' + LIBC_SUFFIX ;
procedure setkey(__key:Pchar);cdecl;external clib name 'setkey' + LIBC_SUFFIX ;
function posix_openpt(__oflag:longint):longint;cdecl;external clib name 'posix_openpt' + LIBC_SUFFIX ;
function grantpt(__fd:longint):longint;cdecl;external clib name 'grantpt' + LIBC_SUFFIX ;
function unlockpt(__fd:longint):longint;cdecl;external clib name 'unlockpt' + LIBC_SUFFIX ;
function ptsname(__fd:longint):Pchar;cdecl;external clib name 'ptsname' + LIBC_SUFFIX ;
function ptsname_r(__fd:longint; __buf:Pchar; __buflen:size_t):longint;cdecl;external clib name 'ptsname_r' + LIBC_SUFFIX ;
function getpt:longint;cdecl;external clib name 'getpt' + LIBC_SUFFIX ;
function getloadavg(__loadavg:array of double; __nelem:longint):longint;cdecl;external clib name 'getloadavg' + LIBC_SUFFIX ;


{ ---------------------------------------------------------------------
    Borland compatibility types
  ---------------------------------------------------------------------}

Type
  TRandomData = random_data;
  PRandomData = ^TRandomData;

  TDrand48Data = drand48_data;
  PDrand48Data = ^TDrand48Data;

function erand48(__xsubi: pword):double;cdecl;external clib name 'erand48' + LIBC_SUFFIX ;
function nrand48(__xsubi: pword):longint;cdecl;external clib name 'nrand48' + LIBC_SUFFIX ;
function jrand48(__xsubi: pword):longint;cdecl;external clib name 'jrand48' + LIBC_SUFFIX ;
function seed48(__seed16v: pword):Pword;cdecl;external clib name 'seed48' + LIBC_SUFFIX ;
procedure lcong48(__param: pword);cdecl;external clib name 'lcong48' + LIBC_SUFFIX ;

function erand48_r(__xsubi:pword; __buffer:Pdrand48_data; __result:Pdouble):longint;cdecl;external clib name 'erand48_r' + LIBC_SUFFIX ;
function nrand48_r(__xsubi:pword; __buffer:Pdrand48_data; __result:Plongint):longint;cdecl;external clib name 'nrand48_r' + LIBC_SUFFIX ;
function jrand48_r(__xsubi:pword; __buffer:Pdrand48_data; __result:Plongint):longint;cdecl;external clib name 'jrand48_r' + LIBC_SUFFIX ;
function seed48_r(__seed16v:pword; __buffer:Pdrand48_data):longint;cdecl;external clib name 'seed48_r' + LIBC_SUFFIX ;

