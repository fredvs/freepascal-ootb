{$if defined(linux) and defined(x86_64)}

function feclearexcept(__excepts:longint):longint;cdecl;external clib name 'feclearexcept@GLIBC_2.2.5';
function fegetexceptflag(__flagp:Pfexcept_t; __excepts:longint):longint;cdecl;external clib name 'fegetexceptflag@GLIBC_2.2.5';
function feraiseexcept(__excepts:longint):longint;cdecl;external clib name 'feraiseexcept@GLIBC_2.2.5';
function fesetexceptflag(__flagp:Pfexcept_t; __excepts:longint):longint;cdecl;external clib name 'fesetexceptflag@GLIBC_2.2.5';
function fetestexcept(__excepts:longint):longint;cdecl;external clib name 'fetestexcept@GLIBC_2.2.5';
function fegetround:longint;cdecl;external clib name 'fegetround@GLIBC_2.2.5';
function fesetround(__rounding_direction:longint):longint;cdecl;external clib name 'fesetround@GLIBC_2.2.5';
function fegetenv(__envp:Pfenv_t):longint;cdecl;external clib name 'fegetenv@GLIBC_2.2.5';
function feholdexcept(__envp:Pfenv_t):longint;cdecl;external clib name 'feholdexcept@GLIBC_2.2.5';
function fesetenv(__envp:Pfenv_t):longint;cdecl;external clib name 'fesetenv@GLIBC_2.2.5';
function feupdateenv(__envp:Pfenv_t):longint;cdecl;external clib name 'feupdateenv@GLIBC_2.2.5';
function feenableexcept(__excepts:longint):longint;cdecl;external clib name 'feenableexcept@GLIBC_2.2.5';
function fedisableexcept(__excepts:longint):longint;cdecl;external clib name 'fedisableexcept@GLIBC_2.2.5';
function fegetexcept:longint;cdecl;external clib name 'fegetexcept@GLIBC_2.2.5';

{ ---------------------------------------------------------------------
    Borland compatibility types
  ---------------------------------------------------------------------}

// Type
function fegetexceptflag(var __flagp:fexcept_t; __excepts:longint):longint;cdecl;external clib name 'fegetexceptflag@GLIBC_2.2.5';
function fesetexceptflag(const __flagp:fexcept_t; __excepts:longint):longint;cdecl;external clib name 'fesetexceptflag@GLIBC_2.2.5';
function fegetenv(var __envp:fenv_t):longint;cdecl;external clib name 'fegetenv@GLIBC_2.2.5';
function feholdexcept(var __envp:fenv_t):longint;cdecl;external clib name 'feholdexcept@GLIBC_2.2.5';
function fesetenv(const __envp:fenv_t):longint;cdecl;external clib name 'fesetenv@GLIBC_2.2.5';
function feupdateenv(var __envp:fenv_t):longint;cdecl;external clib name 'feupdateenv@GLIBC_2.2.5';

{$else}

{$if defined(linux) and defined(i386)}

function feclearexcept(__excepts:longint):longint;cdecl;external clib name 'feclearexcept@GLIBC_2.0';
function fegetexceptflag(__flagp:Pfexcept_t; __excepts:longint):longint;cdecl;external clib name 'fegetexceptflag@GLIBC_2.0';
function feraiseexcept(__excepts:longint):longint;cdecl;external clib name 'feraiseexcept@GLIBC_2.0';
function fesetexceptflag(__flagp:Pfexcept_t; __excepts:longint):longint;cdecl;external clib name 'fesetexceptflag@GLIBC_2.0';
function fetestexcept(__excepts:longint):longint;cdecl;external clib name 'fetestexcept@GLIBC_2.0';
function fegetround:longint;cdecl;external clib name 'fegetround@GLIBC_2.0';
function fesetround(__rounding_direction:longint):longint;cdecl;external clib name 'fesetround@GLIBC_2.0';
function fegetenv(__envp:Pfenv_t):longint;cdecl;external clib name 'fegetenv@GLIBC_2.0';
function feholdexcept(__envp:Pfenv_t):longint;cdecl;external clib name 'feholdexcept@GLIBC_2.0';
function fesetenv(__envp:Pfenv_t):longint;cdecl;external clib name 'fesetenv@GLIBC_2.0';
function feupdateenv(__envp:Pfenv_t):longint;cdecl;external clib name 'feupdateenv@GLIBC_2.0';
function feenableexcept(__excepts:longint):longint;cdecl;external clib name 'feenableexcept@GLIBC_2.0';
function fedisableexcept(__excepts:longint):longint;cdecl;external clib name 'fedisableexcept@GLIBC_2.0';
function fegetexcept:longint;cdecl;external clib name 'fegetexcept@GLIBC_2.0';

{ ---------------------------------------------------------------------
    Borland compatibility types
  ---------------------------------------------------------------------}

// Type
function fegetexceptflag(var __flagp:fexcept_t; __excepts:longint):longint;cdecl;external clib name 'fegetexceptflag@GLIBC_2.0';
function fesetexceptflag(const __flagp:fexcept_t; __excepts:longint):longint;cdecl;external clib name 'fesetexceptflag@GLIBC_2.0';
function fegetenv(var __envp:fenv_t):longint;cdecl;external clib name 'fegetenv@GLIBC_2.0';
function feholdexcept(var __envp:fenv_t):longint;cdecl;external clib name 'feholdexcept@GLIBC_2.0';
function fesetenv(const __envp:fenv_t):longint;cdecl;external clib name 'fesetenv@GLIBC_2.0';
function feupdateenv(var __envp:fenv_t):longint;cdecl;external clib name 'feupdateenv@GLIBC_2.0';

{$else}

function feclearexcept(__excepts:longint):longint;cdecl;external clib name 'feclearexcept';
function fegetexceptflag(__flagp:Pfexcept_t; __excepts:longint):longint;cdecl;external clib name 'fegetexceptflag';
function feraiseexcept(__excepts:longint):longint;cdecl;external clib name 'feraiseexcept';
function fesetexceptflag(__flagp:Pfexcept_t; __excepts:longint):longint;cdecl;external clib name 'fesetexceptflag';
function fetestexcept(__excepts:longint):longint;cdecl;external clib name 'fetestexcept';
function fegetround:longint;cdecl;external clib name 'fegetround';
function fesetround(__rounding_direction:longint):longint;cdecl;external clib name 'fesetround';
function fegetenv(__envp:Pfenv_t):longint;cdecl;external clib name 'fegetenv';
function feholdexcept(__envp:Pfenv_t):longint;cdecl;external clib name 'feholdexcept';
function fesetenv(__envp:Pfenv_t):longint;cdecl;external clib name 'fesetenv';
function feupdateenv(__envp:Pfenv_t):longint;cdecl;external clib name 'feupdateenv';
function feenableexcept(__excepts:longint):longint;cdecl;external clib name 'feenableexcept';
function fedisableexcept(__excepts:longint):longint;cdecl;external clib name 'fedisableexcept';
function fegetexcept:longint;cdecl;external clib name 'fegetexcept';

{ ---------------------------------------------------------------------
    Borland compatibility types
  ---------------------------------------------------------------------}

// Type
function fegetexceptflag(var __flagp:fexcept_t; __excepts:longint):longint;cdecl;external clib name 'fegetexceptflag';
function fesetexceptflag(const __flagp:fexcept_t; __excepts:longint):longint;cdecl;external clib name 'fesetexceptflag';
function fegetenv(var __envp:fenv_t):longint;cdecl;external clib name 'fegetenv';
function feholdexcept(var __envp:fenv_t):longint;cdecl;external clib name 'feholdexcept';
function fesetenv(const __envp:fenv_t):longint;cdecl;external clib name 'fesetenv';
function feupdateenv(var __envp:fenv_t):longint;cdecl;external clib name 'feupdateenv';

{$endif}
{$endif}