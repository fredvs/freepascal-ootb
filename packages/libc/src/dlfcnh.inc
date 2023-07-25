
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


function dlopen(__file:Pchar; __mode:longint):pointer;cdecl;external dllib name 'dlopen' + LIBC_SUFFIX;
function dlclose(__handle:pointer):longint;cdecl;external dllib name 'dlclose' + LIBC_SUFFIX;
function dlsym(__handle:pointer; __name:Pchar):pointer;cdecl;external dllib name 'dlsym' + LIBC_SUFFIX;
function dlvsym(__handle:pointer; __name:Pchar; __version:Pchar):pointer;cdecl;external dllib name 'dlvsym' + LIBC_SUFFIX;
function dlerror:Pchar;cdecl;external clib name 'dlerror' + LIBC_SUFFIX;

function dladdr(__address:pointer; __info:PDl_info):longint;cdecl;external dllib name 'dladdr' + LIBC_SUFFIX;

{ ---------------------------------------------------------------------
    Borland compatibility types
  ---------------------------------------------------------------------}

function dladdr(__address:pointer; var __info: Dl_info):longint;cdecl;external dllib name 'dladdr' + LIBC_SUFFIX;

