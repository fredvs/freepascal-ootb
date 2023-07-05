

function sched_setparam(__pid:__pid_t; __param:Psched_param):longint;cdecl;external clib name 'sched_setparam@GLIBC_2.2.5';
function sched_getparam(__pid:__pid_t; __param:Psched_param):longint;cdecl;external clib name 'sched_getparam@GLIBC_2.2.5';
function sched_setscheduler(__pid:__pid_t; __policy:longint; __param:Psched_param):longint;cdecl;external clib name 'sched_setscheduler@GLIBC_2.2.5';
function sched_getscheduler(__pid:__pid_t):longint;cdecl;external clib name 'sched_getscheduler@GLIBC_2.2.5';
function sched_yield:longint;cdecl;external clib name 'sched_yield@GLIBC_2.2.5';
function sched_get_priority_max(__algorithm:longint):longint;cdecl;external clib name 'sched_get_priority_max@GLIBC_2.2.5';
function sched_get_priority_min(__algorithm:longint):longint;cdecl;external clib name 'sched_get_priority_min@GLIBC_2.2.5';
function sched_rr_get_interval(__pid:__pid_t; __t:Ptimespec):longint;cdecl;external clib name 'sched_rr_get_interval@GLIBC_2.2.5';

{ ---------------------------------------------------------------------
    Borland compatibility types
  ---------------------------------------------------------------------}

function sched_setparam(__pid:__pid_t; var __param: sched_param):longint;cdecl;external clib name 'sched_setparam@GLIBC_2.2.5';
function sched_getparam(__pid:__pid_t; var __param: sched_param):longint;cdecl;external clib name 'sched_getparam@GLIBC_2.2.5';
function sched_setscheduler(__pid:__pid_t; __policy:longint; var __param: sched_param):longint;cdecl;external clib name 'sched_setscheduler@GLIBC_2.2.5';
function sched_rr_get_interval(__pid:__pid_t; var __t: timespec):longint;cdecl;external clib name 'sched_rr_get_interval@GLIBC_2.2.5';
