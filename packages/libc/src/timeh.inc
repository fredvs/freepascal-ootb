type

   Pclock_t = ^clock_t;
   clock_t = __clock_t;

   Ptime_t = ^time_t;
   time_t = __time_t;

   Pclockid_t = ^clockid_t;
   clockid_t = __clockid_t;

   Ptimer_t = ^timer_t;
   timer_t = __timer_t;

type
   Ptm = ^tm;
   tm = record
        tm_sec : longint;
        tm_min : longint;
        tm_hour : longint;
        tm_mday : longint;
        tm_mon : longint;
        tm_year : longint;
        tm_wday : longint;
        tm_yday : longint;
        tm_isdst : longint;
        case boolean of 
         false : (tm_gmtoff : longint;tm_zone : Pchar);
         true  : (__tm_gmtoff : longint;__tm_zone : Pchar);
	end;

   Pitimerspec = ^itimerspec;
   itimerspec = record
        it_interval : timespec;
        it_value : timespec;
     end;



var
  getdate_err : longint;cvar;external;

function clock:clock_t;cdecl;external clib name 'clock' + LIBC_SUFFIX ;
function __time(__timer:Ptime_t):time_t;cdecl;external clib name 'time' + LIBC_SUFFIX ;
function difftime(__time1:time_t; __time0:time_t):double;cdecl;external clib name 'difftime' + LIBC_SUFFIX ;
function mktime(__tp:Ptm):time_t;cdecl;external clib name 'mktime' + LIBC_SUFFIX ;
function strftime(__s:Pchar; __maxsize:size_t; __format:Pchar; __tp:Ptm):size_t;cdecl;external clib name 'strftime' + LIBC_SUFFIX ;
function strptime(__s:Pchar; __fmt:Pchar; __tp:Ptm):Pchar;cdecl;external clib name 'strptime' + LIBC_SUFFIX ;
function gmtime(__timer:Ptime_t):Ptm;cdecl;external clib name 'gmtime' + LIBC_SUFFIX ;
function localtime(__timer:Ptime_t):Ptm;cdecl;external clib name 'localtime' + LIBC_SUFFIX ;
function gmtime_r(__timer:Ptime_t; __tp:Ptm):Ptm;cdecl;external clib name 'gmtime_r' + LIBC_SUFFIX ;
function localtime_r(__timer:Ptime_t; __tp:Ptm):Ptm;cdecl;external clib name 'localtime_r' + LIBC_SUFFIX ;
function asctime(__tp:Ptm):Pchar;cdecl;external clib name 'asctime' + LIBC_SUFFIX ;
function ctime(__timer:Ptime_t):Pchar;cdecl;external clib name 'ctime' + LIBC_SUFFIX ;
function asctime_r(__tp:Ptm; __buf:Pchar):Pchar;cdecl;external clib name 'asctime_r' + LIBC_SUFFIX ;
function ctime_r(__timer:Ptime_t; __buf:Pchar):Pchar;cdecl;external clib name 'ctime_r' + LIBC_SUFFIX ;
procedure tzset;cdecl;external clib name 'tzset' + LIBC_SUFFIX ;
function stime(__when:Ptime_t):longint;cdecl;external clib name 'stime' + LIBC_SUFFIX ;
function timelocal(__tp:Ptm):time_t;cdecl;external clib name 'timelocal' + LIBC_SUFFIX ;
function dysize(__year:longint):longint;cdecl;external clib name 'dysize' + LIBC_SUFFIX ;
function nanosleep(__requested_time:Ptimespec; __remaining:Ptimespec):longint;cdecl;external clib name 'nanosleep' + LIBC_SUFFIX ;
function clock_getres(__clock_id:clockid_t; __res:Ptimespec):longint;cdecl;external clib name 'clock_getres' + LIBC_SUFFIX ;
function clock_gettime(__clock_id:clockid_t; __tp:Ptimespec):longint;cdecl;external clib name 'clock_gettime' + LIBC_SUFFIX ;
function clock_settime(__clock_id:clockid_t; __tp:Ptimespec):longint;cdecl;external clib name 'clock_settime' + LIBC_SUFFIX ;
function clock_nanosleep(__clock_id:clockid_t; __flags:longint; __req:Ptimespec; __rem:Ptimespec):longint;cdecl;external clib name 'clock_nanosleep' + LIBC_SUFFIX ;
function clock_getcpuclockid(__pid:pid_t; __clock_id:Pclockid_t):longint;cdecl;external clib name 'clock_getcpuclockid' + LIBC_SUFFIX ;
function timer_create(__clock_id:clockid_t; __evp:Psigevent; __timerid:Ptimer_t):longint;cdecl;external clib name 'timer_create' + LIBC_SUFFIX ;
function timer_delete(__timerid:timer_t):longint;cdecl;external clib name 'timer_delete' + LIBC_SUFFIX ;
function timer_settime(__timerid:timer_t; __flags:longint; __value:Pitimerspec; __ovalue:Pitimerspec):longint;cdecl;external clib name 'timer_settime' + LIBC_SUFFIX ;
function timer_gettime(__timerid:timer_t; __value:Pitimerspec):longint;cdecl;external clib name 'timer_gettime' + LIBC_SUFFIX ;
function timer_getoverrun(__timerid:timer_t):longint;cdecl;external clib name 'timer_getoverrun' + LIBC_SUFFIX ;
function getdate(__string:Pchar):Ptm;cdecl;external clib name 'getdate' + LIBC_SUFFIX ;
function getdate_r(__string:Pchar; __resbufp:Ptm):longint;cdecl;external clib name 'getdate_r' + LIBC_SUFFIX ;

{ ---------------------------------------------------------------------
    Borland compatibility types
  ---------------------------------------------------------------------}

Type
  TTime_T = Time_t;
  TCLOCKID_T = CLOCKID_T;
  TUnixTime = tm;
  PUnixTime = ^TUnixTime;

  TITimerSpec = itimerspec;

function __time(var __timer : ttime_t):time_t;cdecl;external clib name 'time' + LIBC_SUFFIX ;
function mktime(var __tp:tm):time_t;cdecl;external clib name 'mktime' + LIBC_SUFFIX ;
function strftime(__s:Pchar; __maxsize:size_t; __format:Pchar; var __tp:tm):size_t;cdecl;external clib name 'strftime' + LIBC_SUFFIX ;
function strptime(__s:Pchar; __fmt:Pchar; var __tp: tm):Pchar;cdecl;external clib name 'strptime' + LIBC_SUFFIX ;
function gmtime(var __timer : ttime_t):Ptm;cdecl;external clib name 'gmtime' + LIBC_SUFFIX ;
function localtime(var __timer : ttime_t):Ptm;cdecl;external clib name 'localtime' + LIBC_SUFFIX ;
function gmtime_r(var __timer : ttime_t; var __tp:tm):Ptm;cdecl;external clib name 'gmtime_r' + LIBC_SUFFIX ;
function localtime_r(var __timer : ttime_t; var __tp: tm):Ptm;cdecl;external clib name 'localtime_r' + LIBC_SUFFIX ;
function asctime(var __tp: tm):Pchar;cdecl;external clib name 'asctime' + LIBC_SUFFIX ;
function ctime(var __timer : ttime_t):Pchar;cdecl;external clib name 'ctime' + LIBC_SUFFIX ;
function asctime_r(var __tp:tm; __buf:Pchar):Pchar;cdecl;external clib name 'asctime_r' + LIBC_SUFFIX ;
function ctime_r(var __timer : ttime_t; __buf:Pchar):Pchar;cdecl;external clib name 'ctime_r' + LIBC_SUFFIX ;

function stime(var __when : ttime_t):longint;cdecl;external clib name 'stime' + LIBC_SUFFIX ;
function timegm(var __tp:tm):time_t;cdecl;external clib name 'timegm' + LIBC_SUFFIX ;
function timelocal(var __tp: tm):time_t;cdecl;external clib name 'timelocal' + LIBC_SUFFIX ;
function nanosleep(var __requested_time : ttimespec; var __remaining : ttimespec):longint;cdecl;external clib name 'nanosleep' + LIBC_SUFFIX ;
function clock_getres(var __clock_id:clockid_t; __res : ttimespec):longint;cdecl;external clib name 'clock_getres' + LIBC_SUFFIX ;
function clock_gettime(var __clock_id:clockid_t; __tp : ttimespec):longint;cdecl;external clib name 'clock_gettime' + LIBC_SUFFIX ;
function clock_settime(var __clock_id:clockid_t; __tp : ttimespec):longint;cdecl;external clib name 'clock_settime' + LIBC_SUFFIX ;
function clock_nanosleep(var __clock_id:clockid_t; __flags:longint; __req : ttimespec; var __rem : ttimespec):longint;cdecl;external clib name 'clock_nanosleep' + LIBC_SUFFIX ;
function clock_getcpuclockid(__pid:pid_t; var __clock_id: tclockid_t):longint;cdecl;external clib name 'clock_getcpuclockid' + LIBC_SUFFIX ;
function timer_create(__clock_id:clockid_t; var __ev :tsigevent; var __timerid:timer_t):longint;cdecl;external clib name 'timer_create' + LIBC_SUFFIX ;
function timer_settime(__timerid:timer_t; __flags:longint; const __value: titimerspec; var __ovalue:titimerspec):longint;cdecl;external clib name 'timer_settime' + LIBC_SUFFIX ;
function timer_gettime(__timerid:timer_t; var __value: titimerspec):longint;cdecl;external clib name 'timer_gettime' + LIBC_SUFFIX ;

