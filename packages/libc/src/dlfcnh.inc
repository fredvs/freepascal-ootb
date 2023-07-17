
Const
  RTLD_NEXT = Pointer(-1);
  RTLD_DEFAULT = nil;
  
type

   PDl_info = ^Dl_info;
   Dl_info = record
        dli_fname : Pchar;
        dli_fbase : pointer;
        dli_sname : Pchar;
        dli_saddr : pointer;
     end;

Type
  TDLInfo = Dl_info;
  PDLInfo = ^TDLInfo;

{$if defined(linux) and defined(cpu64)}

function dlopen(__file:Pchar; __mode:longint):pointer;cdecl;external dllib name 'dlopen@GLIBC_2.2.5';
function dlclose(__handle:pointer):longint;cdecl;external dllib name 'dlclose@GLIBC_2.2.5';
function dlsym(__handle:pointer; __name:Pchar):pointer;cdecl;external dllib name 'dlsym@GLIBC_2.2.5';
function dlvsym(__handle:pointer; __name:Pchar; __version:Pchar):pointer;cdecl;external dllib name 'dlvsym@GLIBC_2.2.5';
function dlerror:Pchar;cdecl;external clib name 'dlerror@GLIBC_2.2.5';

function dladdr(__address:pointer; __info:PDl_info):longint;cdecl;external dllib name 'dladdr@GLIBC_2.2.5';

{ ---------------------------------------------------------------------
    Borland compatibility types
  ---------------------------------------------------------------------}

function dladdr(__address:pointer; var __info: Dl_info):longint;cdecl;external dllib name 'dladdr@GLIBC_2.2.5';

{$else}
{$if defined(linux) and defined(cpu32)}

function dlopen(__file:Pchar; __mode:longint):pointer;cdecl;external dllib name 'dlopen@GLIBC_2.0';
function dlclose(__handle:pointer):longint;cdecl;external dllib name 'dlclose@GLIBC_2.0';
function dlsym(__handle:pointer; __name:Pchar):pointer;cdecl;external dllib name 'dlsym@GLIBC_2.0';
function dlvsym(__handle:pointer; __name:Pchar; __version:Pchar):pointer;cdecl;external dllib name 'dlvsym@GLIBC_2.0';
function dlerror:Pchar;cdecl;external clib name 'dlerror@GLIBC_2.0';

function dladdr(__address:pointer; __info:PDl_info):longint;cdecl;external dllib name 'dladdr@GLIBC_2.0';

{ ---------------------------------------------------------------------
    Borland compatibility types
  ---------------------------------------------------------------------}

function dladdr(__address:pointer; var __info: Dl_info):longint;cdecl;external dllib name 'dladdr@GLIBC_2.0';

{$else}

function dlopen(__file:Pchar; __mode:longint):pointer;cdecl;external dllib name 'dlopen';
function dlclose(__handle:pointer):longint;cdecl;external dllib name 'dlclose';
function dlsym(__handle:pointer; __name:Pchar):pointer;cdecl;external dllib name 'dlsym';
function dlvsym(__handle:pointer; __name:Pchar; __version:Pchar):pointer;cdecl;external dllib name 'dlvsym';
function dlerror:Pchar;cdecl;external clib name 'dlerror';

function dladdr(__address:pointer; __info:PDl_info):longint;cdecl;external dllib name 'dladdr';

{ ---------------------------------------------------------------------
    Borland compatibility types
  ---------------------------------------------------------------------}

function dladdr(__address:pointer; var __info: Dl_info):longint;cdecl;external dllib name 'dladdr';

{$endif}
{$endif}