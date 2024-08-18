
function feclearexcept(__excepts:longint):longint;cdecl;external clib name 'feclearexcept' + LIBC_SUFFIX;
function fegetexceptflag(__flagp:Pfexcept_t; __excepts:longint):longint;cdecl;external clib name 'fegetexceptflag' + LIBC_SUFFIX;
function feraiseexcept(__excepts:longint):longint;cdecl;external clib name 'feraiseexcept' + LIBC_SUFFIX;
function fesetexceptflag(__flagp:Pfexcept_t; __excepts:longint):longint;cdecl;external clib name 'fesetexceptflag' + LIBC_SUFFIX;
function fetestexcept(__excepts:longint):longint;cdecl;external clib name 'fetestexcept' + LIBC_SUFFIX;
function fegetround:longint;cdecl;external clib name 'fegetround' + LIBC_SUFFIX;
function fesetround(__rounding_direction:longint):longint;cdecl;external clib name 'fesetround' + LIBC_SUFFIX;
function fegetenv(__envp:Pfenv_t):longint;cdecl;external clib name 'fegetenv' + LIBC_SUFFIX;
function feholdexcept(__envp:Pfenv_t):longint;cdecl;external clib name 'feholdexcept' + LIBC_SUFFIX;
function fesetenv(__envp:Pfenv_t):longint;cdecl;external clib name 'fesetenv' + LIBC_SUFFIX;
function feupdateenv(__envp:Pfenv_t):longint;cdecl;external clib name 'feupdateenv' + LIBC_SUFFIX;
function feenableexcept(__excepts:longint):longint;cdecl;external clib name 'feenableexcept' + LIBC_SUFFIX;
function fedisableexcept(__excepts:longint):longint;cdecl;external clib name 'fedisableexcept' + LIBC_SUFFIX;
function fegetexcept:longint;cdecl;external clib name 'fegetexcept' + LIBC_SUFFIX;

{ ---------------------------------------------------------------------
    Borland compatibility types
  ---------------------------------------------------------------------}

// Type
function fegetexceptflag(var __flagp:fexcept_t; __excepts:longint):longint;cdecl;external clib name 'fegetexceptflag' + LIBC_SUFFIX;
function fesetexceptflag(const __flagp:fexcept_t; __excepts:longint):longint;cdecl;external clib name 'fesetexceptflag' + LIBC_SUFFIX;
function fegetenv(var __envp:fenv_t):longint;cdecl;external clib name 'fegetenv' + LIBC_SUFFIX;
function feholdexcept(var __envp:fenv_t):longint;cdecl;external clib name 'feholdexcept' + LIBC_SUFFIX;
function fesetenv(const __envp:fenv_t):longint;cdecl;external clib name 'fesetenv' + LIBC_SUFFIX;
function feupdateenv(var __envp:fenv_t):longint;cdecl;external clib name 'feupdateenv' + LIBC_SUFFIX;
