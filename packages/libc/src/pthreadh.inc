
Const
  PTHREAD_CREATE_JOINABLE = 0;
  PTHREAD_CREATE_DETACHED = 1;

  PTHREAD_INHERIT_SCHED = 0;
  PTHREAD_EXPLICIT_SCHED = 1;

  PTHREAD_SCOPE_SYSTEM = 0;
  PTHREAD_SCOPE_PROCESS = 1;

  PTHREAD_MUTEX_TIMED_NP = 0;
  PTHREAD_MUTEX_RECURSIVE_NP = 1;
  PTHREAD_MUTEX_ERRORCHECK_NP = 2;
  PTHREAD_MUTEX_ADAPTIVE_NP = 3;
  PTHREAD_MUTEX_NORMAL = PTHREAD_MUTEX_TIMED_NP;
  PTHREAD_MUTEX_RECURSIVE = PTHREAD_MUTEX_RECURSIVE_NP;
  PTHREAD_MUTEX_ERRORCHECK = PTHREAD_MUTEX_ERRORCHECK_NP;
  PTHREAD_MUTEX_DEFAULT = PTHREAD_MUTEX_NORMAL;
  PTHREAD_MUTEX_FAST_NP = PTHREAD_MUTEX_ADAPTIVE_NP;

  PTHREAD_PROCESS_PRIVATE = 0;
  PTHREAD_PROCESS_SHARED = 1;

  PTHREAD_RWLOCK_PREFER_READER_NP = 0;
  PTHREAD_RWLOCK_PREFER_WRITER_NP = 1;
  PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP = 2;
  PTHREAD_RWLOCK_DEFAULT_NP = PTHREAD_RWLOCK_PREFER_WRITER_NP;

  PTHREAD_ONCE_INIT = 0;
      
type
  TPThreadCleanupRoutine = procedure(Arg: Pointer); cdecl;

  P_pthread_cleanup_buffer = ^_pthread_cleanup_buffer;
  _pthread_cleanup_buffer = record
       __routine :  TPThreadCleanupRoutine;
       __arg : pointer;
       __canceltype : longint;
       __prev : P_pthread_cleanup_buffer;
    end;


Const
  PTHREAD_CANCEL_ENABLE = 0;
  PTHREAD_CANCEL_DISABLE = 1;

  PTHREAD_CANCEL_DEFERRED = 0;
  PTHREAD_CANCEL_ASYNCHRONOUS = 1;

  PTHREAD_CANCELED = Pointer(-1);
  PTHREAD_BARRIER_SERIAL_THREAD = -1;

  NONRECURSIVE  = 0;
  RECURSIVE     = 1;
  
  
      

  // procedural types used in parameters to pthread functions
Type
  TStartRoutine = function (_para1:pointer): integer; cdecl;// pthread_create
  TKeyValueDestructor = procedure(ValueInKey: Pointer); cdecl;
  TInitOnceProc = Procedure;cdecl;
  TForkHandler = procedure; cdecl;
  
  

procedure __pthread_initialize;cdecl;external threadslib name '__pthread_initialize' + LIBC_SUFFIX ;
function pthread_create(__thread:Ppthread_t; __attr:Ppthread_attr_t; __start_routine:TStartRoutine; __arg:pointer):longint;cdecl;external threadslib name 'pthread_create' + LIBC_SUFFIX ;
function pthread_self:pthread_t;cdecl;external threadslib name 'pthread_self' + LIBC_SUFFIX ;
function pthread_equal(__thread1:pthread_t; __thread2:pthread_t):longint;cdecl;external threadslib name 'pthread_equal' + LIBC_SUFFIX ;
procedure pthread_exit(__retval:pointer);cdecl;external threadslib name 'pthread_exit' + LIBC_SUFFIX ;
function pthread_join(__th:pthread_t; __thread_return:Ppointer):longint;cdecl;external threadslib name 'pthread_join' + LIBC_SUFFIX ;
function pthread_detach(__th:pthread_t):longint;cdecl;external threadslib name 'pthread_detach' + LIBC_SUFFIX ;
function pthread_attr_init(__attr:Ppthread_attr_t):longint;cdecl;external threadslib name 'pthread_attr_init' + LIBC_SUFFIX ;
function pthread_attr_destroy(__attr:Ppthread_attr_t):longint;cdecl;external threadslib name 'pthread_attr_destroy' + LIBC_SUFFIX ;
function pthread_attr_setdetachstate(__attr:Ppthread_attr_t; __detachstate:longint):longint;cdecl;external threadslib name 'pthread_attr_setdetachstate' + LIBC_SUFFIX ;
function pthread_attr_getdetachstate(__attr:Ppthread_attr_t; __detachstate:Plongint):longint;cdecl;external threadslib name 'pthread_attr_getdetachstate' + LIBC_SUFFIX ;
function pthread_attr_setschedparam(__attr:Ppthread_attr_t; __param:Psched_param):longint;cdecl;external threadslib name 'pthread_attr_setschedparam' + LIBC_SUFFIX ;
function pthread_attr_getschedparam(__attr:Ppthread_attr_t; __param:Psched_param):longint;cdecl;external threadslib name 'pthread_attr_getschedparam' + LIBC_SUFFIX ;
function pthread_attr_setschedpolicy(__attr:Ppthread_attr_t; __policy:longint):longint;cdecl;external threadslib name 'pthread_attr_setschedpolicy' + LIBC_SUFFIX ;
function pthread_attr_getschedpolicy(__attr:Ppthread_attr_t; __policy:Plongint):longint;cdecl;external threadslib name 'pthread_attr_getschedpolicy' + LIBC_SUFFIX ;
function pthread_attr_setinheritsched(__attr:Ppthread_attr_t; __inherit:longint):longint;cdecl;external threadslib name 'pthread_attr_setinheritsched' + LIBC_SUFFIX ;
function pthread_attr_getinheritsched(__attr:Ppthread_attr_t; __inherit:Plongint):longint;cdecl;external threadslib name 'pthread_attr_getinheritsched' + LIBC_SUFFIX ;
function pthread_attr_setscope(__attr:Ppthread_attr_t; __scope:longint):longint;cdecl;external threadslib name 'pthread_attr_setscope' + LIBC_SUFFIX ;
function pthread_attr_getscope(__attr:Ppthread_attr_t; __scope:Plongint):longint;cdecl;external threadslib name 'pthread_attr_getscope' + LIBC_SUFFIX ;
function pthread_attr_setguardsize(__attr:Ppthread_attr_t; __guardsize:size_t):longint;cdecl;external threadslib name 'pthread_attr_setguardsize' + LIBC_SUFFIX ;
function pthread_attr_getguardsize(__attr:Ppthread_attr_t; __guardsize:Psize_t):longint;cdecl;external threadslib name 'pthread_attr_getguardsize' + LIBC_SUFFIX ;
function pthread_attr_setstackaddr(__attr:Ppthread_attr_t; __stackaddr:pointer):longint;cdecl;external threadslib name 'pthread_attr_setstackaddr' + LIBC_SUFFIX ;
function pthread_attr_getstackaddr(__attr:Ppthread_attr_t; __stackaddr:Ppointer):longint;cdecl;external threadslib name 'pthread_attr_getstackaddr' + LIBC_SUFFIX ;
function pthread_attr_setstack(__attr:Ppthread_attr_t; __stackaddr:pointer; __stacksize:size_t):longint;cdecl;external threadslib name 'pthread_attr_setstack' + LIBC_SUFFIX ;
function pthread_attr_getstack(__attr:Ppthread_attr_t; __stackaddr:Ppointer; __stacksize:Psize_t):longint;cdecl;external threadslib name 'pthread_attr_getstack' + LIBC_SUFFIX ;
function pthread_attr_setstacksize(__attr:Ppthread_attr_t; __stacksize:size_t):longint;cdecl;external threadslib name 'pthread_attr_setstacksize' + LIBC_SUFFIX ;
function pthread_attr_getstacksize(__attr:Ppthread_attr_t; __stacksize:Psize_t):longint;cdecl;external threadslib name 'pthread_attr_getstacksize' + LIBC_SUFFIX ;
function pthread_getattr_np(__th:pthread_t; __attr:Ppthread_attr_t):longint;cdecl;external threadslib name 'pthread_getattr_np' + LIBC_SUFFIX ;
function pthread_setschedparam(__target_thread:pthread_t; __policy:longint; __param:Psched_param):longint;cdecl;external threadslib name 'pthread_setschedparam' + LIBC_SUFFIX ;
function pthread_getschedparam(__target_thread:pthread_t; __policy:Plongint; __param:Psched_param):longint;cdecl;external threadslib name 'pthread_getschedparam' + LIBC_SUFFIX ;
function pthread_getconcurrency:longint;cdecl;external threadslib name 'pthread_getconcurrency' + LIBC_SUFFIX ;
function pthread_setconcurrency(__level:longint):longint;cdecl;external threadslib name 'pthread_setconcurrency' + LIBC_SUFFIX ;
function pthread_yield:longint;cdecl;external threadslib name 'pthread_yield' + LIBC_SUFFIX ;
function pthread_mutex_init(__mutex:Ppthread_mutex_t; __mutex_attr:Ppthread_mutexattr_t):longint;cdecl;external threadslib name 'pthread_mutex_init' + LIBC_SUFFIX ;
function pthread_mutex_destroy(__mutex:Ppthread_mutex_t):longint;cdecl;external threadslib name 'pthread_mutex_destroy' + LIBC_SUFFIX ;
function pthread_mutex_trylock(__mutex:Ppthread_mutex_t):longint;cdecl;external threadslib name 'pthread_mutex_trylock' + LIBC_SUFFIX ;
function pthread_mutex_lock(__mutex:Ppthread_mutex_t):longint;cdecl;external threadslib name 'pthread_mutex_lock' + LIBC_SUFFIX ;
function pthread_mutex_timedlock(__mutex:Ppthread_mutex_t; __abstime:Ptimespec):longint;cdecl;external threadslib name 'pthread_mutex_timedlock' + LIBC_SUFFIX ;
function pthread_mutex_unlock(__mutex:Ppthread_mutex_t):longint;cdecl;external threadslib name 'pthread_mutex_unlock' + LIBC_SUFFIX ;
function pthread_mutexattr_init(__attr:Ppthread_mutexattr_t):longint;cdecl;external threadslib name 'pthread_mutexattr_init' + LIBC_SUFFIX ;
function pthread_mutexattr_destroy(__attr:Ppthread_mutexattr_t):longint;cdecl;external threadslib name 'pthread_mutexattr_destroy' + LIBC_SUFFIX ;
function pthread_mutexattr_getpshared(__attr:Ppthread_mutexattr_t; __pshared:Plongint):longint;cdecl;external threadslib name 'pthread_mutexattr_getpshared' + LIBC_SUFFIX ;
function pthread_mutexattr_setpshared(__attr:Ppthread_mutexattr_t; __pshared:longint):longint;cdecl;external threadslib name 'pthread_mutexattr_setpshared' + LIBC_SUFFIX ;
function pthread_mutexattr_settype(__attr:Ppthread_mutexattr_t; __kind:longint):longint;cdecl;external threadslib name 'pthread_mutexattr_settype' + LIBC_SUFFIX ;
function pthread_mutexattr_gettype(__attr:Ppthread_mutexattr_t; __kind:Plongint):longint;cdecl;external threadslib name 'pthread_mutexattr_gettype' + LIBC_SUFFIX ;
function pthread_cond_init(__cond:Ppthread_cond_t; __cond_attr:Ppthread_condattr_t):longint;cdecl;external threadslib name 'pthread_cond_init' + LIBC_SUFFIX ;
function pthread_cond_destroy(__cond:Ppthread_cond_t):longint;cdecl;external threadslib name 'pthread_cond_destroy' + LIBC_SUFFIX ;
function pthread_cond_signal(__cond:Ppthread_cond_t):longint;cdecl;external threadslib name 'pthread_cond_signal' + LIBC_SUFFIX ;
function pthread_cond_broadcast(__cond:Ppthread_cond_t):longint;cdecl;external threadslib name 'pthread_cond_broadcast' + LIBC_SUFFIX ;
function pthread_cond_wait(__cond:Ppthread_cond_t; __mutex:Ppthread_mutex_t):longint;cdecl;external threadslib name 'pthread_cond_wait' + LIBC_SUFFIX ;
function pthread_cond_timedwait(__cond:Ppthread_cond_t; __mutex:Ppthread_mutex_t; __abstime:Ptimespec):longint;cdecl;external threadslib name 'pthread_cond_timedwait' + LIBC_SUFFIX ;
function pthread_condattr_init(__attr:Ppthread_condattr_t):longint;cdecl;external threadslib name 'pthread_condattr_init' + LIBC_SUFFIX ;
function pthread_condattr_destroy(__attr:Ppthread_condattr_t):longint;cdecl;external threadslib name 'pthread_condattr_destroy' + LIBC_SUFFIX ;
function pthread_condattr_getpshared(__attr:Ppthread_condattr_t; __pshared:Plongint):longint;cdecl;external threadslib name 'pthread_condattr_getpshared' + LIBC_SUFFIX ;
function pthread_condattr_setpshared(__attr:Ppthread_condattr_t; __pshared:longint):longint;cdecl;external threadslib name 'pthread_condattr_setpshared' + LIBC_SUFFIX ;
function pthread_rwlock_init(__rwlock:Ppthread_rwlock_t; __attr:Ppthread_rwlockattr_t):longint;cdecl;external threadslib name 'pthread_rwlock_init' + LIBC_SUFFIX ;
function pthread_rwlock_destroy(__rwlock:Ppthread_rwlock_t):longint;cdecl;external threadslib name 'pthread_rwlock_destroy' + LIBC_SUFFIX ;
function pthread_rwlock_rdlock(__rwlock:Ppthread_rwlock_t):longint;cdecl;external threadslib name 'pthread_rwlock_rdlock' + LIBC_SUFFIX ;
function pthread_rwlock_tryrdlock(__rwlock:Ppthread_rwlock_t):longint;cdecl;external threadslib name 'pthread_rwlock_tryrdlock' + LIBC_SUFFIX ;
function pthread_rwlock_timedrdlock(__rwlock:Ppthread_rwlock_t; __abstime:Ptimespec):longint;cdecl;external threadslib name 'pthread_rwlock_timedrdlock' + LIBC_SUFFIX ;
function pthread_rwlock_wrlock(__rwlock:Ppthread_rwlock_t):longint;cdecl;external threadslib name 'pthread_rwlock_wrlock' + LIBC_SUFFIX ;
function pthread_rwlock_trywrlock(__rwlock:Ppthread_rwlock_t):longint;cdecl;external threadslib name 'pthread_rwlock_trywrlock' + LIBC_SUFFIX ;
function pthread_rwlock_timedwrlock(__rwlock:Ppthread_rwlock_t; __abstime:Ptimespec):longint;cdecl;external threadslib name 'pthread_rwlock_timedwrlock' + LIBC_SUFFIX ;
function pthread_rwlock_unlock(__rwlock:Ppthread_rwlock_t):longint;cdecl;external threadslib name 'pthread_rwlock_unlock' + LIBC_SUFFIX ;
function pthread_rwlockattr_init(__attr:Ppthread_rwlockattr_t):longint;cdecl;external threadslib name 'pthread_rwlockattr_init' + LIBC_SUFFIX ;
function pthread_rwlockattr_destroy(__attr:Ppthread_rwlockattr_t):longint;cdecl;external threadslib name 'pthread_rwlockattr_destroy' + LIBC_SUFFIX ;
function pthread_rwlockattr_getpshared(__attr:Ppthread_rwlockattr_t; __pshared:Plongint):longint;cdecl;external threadslib name 'pthread_rwlockattr_getpshared' + LIBC_SUFFIX ;
function pthread_rwlockattr_setpshared(__attr:Ppthread_rwlockattr_t; __pshared:longint):longint;cdecl;external threadslib name 'pthread_rwlockattr_setpshared' + LIBC_SUFFIX ;
function pthread_rwlockattr_getkind_np(__attr:Ppthread_rwlockattr_t; __pref:Plongint):longint;cdecl;external threadslib name 'pthread_rwlockattr_getkind_np' + LIBC_SUFFIX ;
function pthread_rwlockattr_setkind_np(__attr:Ppthread_rwlockattr_t; __pref:longint):longint;cdecl;external threadslib name 'pthread_rwlockattr_setkind_np' + LIBC_SUFFIX ;
function pthread_spin_init(__lock:Ppthread_spinlock_t; __pshared:longint):longint;cdecl;external threadslib name 'pthread_spin_init' + LIBC_SUFFIX ;
function pthread_spin_destroy(__lock:Ppthread_spinlock_t):longint;cdecl;external threadslib name 'pthread_spin_destroy' + LIBC_SUFFIX ;
function pthread_spin_lock(__lock:Ppthread_spinlock_t):longint;cdecl;external threadslib name 'pthread_spin_lock' + LIBC_SUFFIX ;
function pthread_spin_trylock(__lock:Ppthread_spinlock_t):longint;cdecl;external threadslib name 'pthread_spin_trylock' + LIBC_SUFFIX ;
function pthread_spin_unlock(__lock:Ppthread_spinlock_t):longint;cdecl;external threadslib name 'pthread_spin_unlock' + LIBC_SUFFIX ;
function pthread_barrier_init(__barrier:Ppthread_barrier_t; __attr:Ppthread_barrierattr_t; __count:dword):longint;cdecl;external threadslib name 'pthread_barrier_init' + LIBC_SUFFIX ;
function pthread_barrier_destroy(__barrier:Ppthread_barrier_t):longint;cdecl;external threadslib name 'pthread_barrier_destroy' + LIBC_SUFFIX ;
function pthread_barrierattr_init(__attr:Ppthread_barrierattr_t):longint;cdecl;external threadslib name 'pthread_barrierattr_init' + LIBC_SUFFIX ;
function pthread_barrierattr_destroy(__attr:Ppthread_barrierattr_t):longint;cdecl;external threadslib name 'pthread_barrierattr_destroy' + LIBC_SUFFIX ;
function pthread_barrierattr_getpshared(__attr:Ppthread_barrierattr_t; __pshared:Plongint):longint;cdecl;external threadslib name 'pthread_barrierattr_getpshared' + LIBC_SUFFIX ;
function pthread_barrierattr_setpshared(__attr:Ppthread_barrierattr_t; __pshared:longint):longint;cdecl;external threadslib name 'pthread_barrierattr_setpshared' + LIBC_SUFFIX ;
function pthread_barrier_wait(__barrier:Ppthread_barrier_t):longint;cdecl;external threadslib name 'pthread_barrier_wait' + LIBC_SUFFIX ;
function pthread_key_create(__key:Ppthread_key_t; __destr_function:TKeyValueDestructor):longint;cdecl;external threadslib name 'pthread_key_create' + LIBC_SUFFIX ;
function pthread_key_delete(__key:pthread_key_t):longint;cdecl;external threadslib name 'pthread_key_delete' + LIBC_SUFFIX ;
function pthread_setspecific(__key:pthread_key_t; __pointer:pointer):longint;cdecl;external threadslib name 'pthread_setspecific' + LIBC_SUFFIX ;
function pthread_getspecific(__key:pthread_key_t):pointer;cdecl;external threadslib name 'pthread_getspecific' + LIBC_SUFFIX ;
function pthread_once(__once_control:Ppthread_once_t; __init_routine:TinitOnceProc ):longint;cdecl;external threadslib name 'pthread_once' + LIBC_SUFFIX ;
function pthread_setcancelstate(__state:longint; __oldstate:Plongint):longint;cdecl;external threadslib name 'pthread_setcancelstate' + LIBC_SUFFIX ;
function pthread_setcanceltype(__type:longint; __oldtype:Plongint):longint;cdecl;external threadslib name 'pthread_setcanceltype' + LIBC_SUFFIX ;
function pthread_cancel(__thread:pthread_t):longint;cdecl;external threadslib name 'pthread_cancel' + LIBC_SUFFIX ;
procedure pthread_testcancel;cdecl;external threadslib name 'pthread_testcancel' + LIBC_SUFFIX ;
procedure _pthread_cleanup_push(__buffer:P_pthread_cleanup_buffer;__routine:TPThreadCleanupRoutine; __arg:pointer);cdecl;external threadslib name '_pthread_cleanup_push' + LIBC_SUFFIX ;
procedure _pthread_cleanup_pop(__buffer:P_pthread_cleanup_buffer; __execute:longint);cdecl;external threadslib name '_pthread_cleanup_pop' + LIBC_SUFFIX ;
procedure _pthread_cleanup_push_defer(__buffer:P_pthread_cleanup_buffer; __routine:TPThreadCleanupRoutine; __arg:pointer);cdecl;external threadslib name '_pthread_cleanup_push_defer' + LIBC_SUFFIX ;
procedure _pthread_cleanup_pop_restore(__buffer:P_pthread_cleanup_buffer; __execute:longint);cdecl;external threadslib name '_pthread_cleanup_pop_restore' + LIBC_SUFFIX ;
function pthread_getcpuclockid(__thread_id:pthread_t; __clock_id:Pclockid_t):longint;cdecl;external threadslib name 'pthread_getcpuclockid' + LIBC_SUFFIX ;
function pthread_atfork(__prepare:TForkHandler ; _parent:TForkHandler ; __child:TForkHandler ):longint;cdecl;external threadslib name 'pthread_atfork' + LIBC_SUFFIX ;
procedure pthread_kill_other_threads_np;cdecl;external threadslib name 'pthread_kill_other_threads_np' + LIBC_SUFFIX ;

// Borland compatibility types
Type
  TPthreadCleanupBuffer = _pthread_cleanup_buffer;
  
function pthread_mutexattr_init(var __attr: pthread_mutexattr_t):longint;cdecl; external threadslib name 'pthread_mutexattr_init' + LIBC_SUFFIX ;
function pthread_mutexattr_settype(var __attr: pthread_mutexattr_t; Kind: Integer): Integer; cdecl;external threadslib name 'pthread_mutexattr_settype' + LIBC_SUFFIX ;
function pthread_mutexattr_destroy(var __attr: pthread_mutexattr_t):longint;cdecl; external threadslib name 'pthread_mutexattr_destroy' + LIBC_SUFFIX ;
function pthread_mutex_trylock(var __mutex: pthread_mutex_t):longint;cdecl; external threadslib name 'pthread_mutex_trylock' + LIBC_SUFFIX ;
function pthread_mutex_init(var __mutex: pthread_mutex_t; var __mutex_attr: pthread_mutexattr_t):longint;cdecl; external threadslib name 'pthread_mutex_t' + LIBC_SUFFIX ;
{ ---------------------------------------------------------------------
    Borland compatibility types
  ---------------------------------------------------------------------}

{
function pthread_create(var __thread:pthread_t; var __attr: pthread_attr_t; __start_routine:TStartRoutine; __arg:pointer):longint;cdecl; external threadslib;
function pthread_join(__th:pthread_t; var __thread_return:pointer):longint;cdecl; external threadslib;
function pthread_attr_init(var __attr: pthread_attr_t):longint;cdecl; external threadslib;
function pthread_attr_destroy(var __attr: pthread_attr_t):longint;cdecl; external threadslib;
function pthread_attr_setdetachstate(var __attr: pthread_attr_t; __detachstate:longint):longint;cdecl; external threadslib;
function pthread_attr_getdetachstate(var __attr: pthread_attr_t; var __detachstate:longint):longint;cdecl; external threadslib;
function pthread_attr_setschedparam(var __attr: pthread_attr_t; const __param: sched_param):longint;cdecl; external threadslib;
function pthread_attr_getschedparam(var __attr: pthread_attr_t; var __param: sched_param):longint;cdecl; external threadslib;
function pthread_attr_setschedpolicy(var __attr: pthread_attr_t; __policy:longint):longint;cdecl; external threadslib;
function pthread_attr_getschedpolicy(var __attr: pthread_attr_t; var __policy:longint):longint;cdecl; external threadslib;
function pthread_attr_setinheritsched(var __attr: pthread_attr_t; __inherit:longint):longint;cdecl; external threadslib;
function pthread_attr_getinheritsched(var __attr: pthread_attr_t; var __inherit: longint):longint;cdecl; external threadslib;
function pthread_attr_setscope(var __attr: pthread_attr_t; __scope:longint):longint;cdecl; external threadslib;
function pthread_attr_getscope(var __attr: pthread_attr_t; var __scope: longint):longint;cdecl; external threadslib;
function pthread_attr_setstackaddr(var __attr: pthread_attr_t; __stackaddr:pointer):longint;cdecl; external threadslib;
function pthread_attr_getstackaddr(var __attr: pthread_attr_t; var __stackaddr:pointer):longint;cdecl; external threadslib;
function pthread_attr_setstacksize(var __attr: pthread_attr_t; __stacksize:size_t):longint;cdecl; external threadslib;
function pthread_attr_getstacksize(var __attr: pthread_attr_t; var __stacksize: size_t):longint;cdecl; external threadslib;
function pthread_attr_getguardsize(var __attr: pthread_attr_t; var Guardsize: Cardinal): Integer; cdecl;external threadslib;
function pthread_attr_setguardsize(var __attr: pthread_attr_t; Guardsize: Cardinal): Integer; cdecl;external threadslib;
function pthread_setschedparam(__target_thread:pthread_t; __policy:longint; const __param: sched_param):longint;cdecl; external threadslib;
function pthread_getschedparam(__target_thread:pthread_t; var __policy: longint; var __param: sched_param):longint;cdecl; external threadslib;
function pthread_mutex_init(var __mutex: pthread_mutex_t; var __mutex_attr: pthread_mutexattr_t):longint;cdecl; external threadslib;
function pthread_mutex_destroy(var __mutex: pthread_mutex_t):longint;cdecl; external threadslib;
//function pthread_mutex_trylock(var __mutex: pthread_mutex_t):longint;cdecl; external threadslib;
function pthread_mutex_lock(var __mutex: pthread_mutex_t):longint;cdecl; external threadslib;
function pthread_mutex_unlock(var __mutex: pthread_mutex_t):longint;cdecl; external threadslib;
function pthread_mutexattr_init(var __attr: pthread_mutexattr_t):longint;cdecl; external threadslib;
function pthread_mutexattr_destroy(var __attr: pthread_mutexattr_t):longint;cdecl; external threadslib;
function pthread_mutexattr_getpshared(var __attr: pthread_mutexattr_t; var __pshared: longint):longint;cdecl; external threadslib;
function pthread_mutexattr_setpshared(var __attr: pthread_mutexattr_t; __pshared:longint):longint;cdecl; external threadslib;
//function pthread_mutexattr_settype(var __attr: pthread_mutexattr_t; Kind: Integer): Integer; cdecl;external threadslib;
function pthread_mutexattr_gettype(var __attr: pthread_mutexattr_t; var Kind: Integer): Integer; cdecl;external threadslib;
function pthread_cond_init(var __cond: pthread_cond_t;var __cond_attr: pthread_condattr_t):longint;cdecl; external threadslib;
function pthread_cond_destroy(var __cond: pthread_cond_t):longint;cdecl; external threadslib;
function pthread_cond_signal(var __cond: pthread_cond_t):longint;cdecl; external threadslib;
function pthread_cond_broadcast(var __cond: pthread_cond_t):longint;cdecl; external threadslib;
function pthread_cond_wait(var __cond: pthread_cond_t; var __mutex: pthread_mutex_t):longint;cdecl; external threadslib;
function pthread_cond_timedwait(var __cond: pthread_cond_t; var __mutex: pthread_mutex_t; var __abstime: timespec):longint;cdecl; external threadslib;
function pthread_condattr_init(var __attr: pthread_condattr_t):longint;cdecl; external threadslib;
function pthread_condattr_destroy(var __attr: pthread_condattr_t):longint;cdecl; external threadslib;
function pthread_condattr_getpshared(var __attr: pthread_condattr_t; var __pshared:longint):longint;cdecl; external threadslib;
function pthread_condattr_setpshared(var __attr: pthread_condattr_t; __pshared:longint):longint;cdecl; external threadslib;
function pthread_rwlock_init(var __rwlock: pthread_rwlock_t; var __attr: pthread_rwlockattr_t):longint;cdecl; external threadslib;
function pthread_rwlock_destroy(var __rwlock: pthread_rwlock_t):longint;cdecl;external threadslib;
function pthread_rwlock_rdlock(var __rwlock: pthread_rwlock_t):longint;cdecl;external threadslib;
function pthread_rwlock_tryrdlock(var __rwlock: pthread_rwlock_t):longint;cdecl;external threadslib;
function pthread_rwlock_timedrdlock(var __rwlock: pthread_rwlock_t; __abstime:Ptimespec):longint;cdecl;external threadslib;
function pthread_rwlock_wrlock(var __rwlock: pthread_rwlock_t):longint;cdecl;external threadslib;
function pthread_rwlock_trywrlock(var __rwlock: pthread_rwlock_t):longint;cdecl; external threadslib;
function pthread_rwlock_timedwrlock(var __rwlock: pthread_rwlock_t; __abstime:Ptimespec):longint;cdecl;external threadslib;
function pthread_rwlock_unlock(var __rwlock: pthread_rwlock_t):longint;cdecl;external threadslib;
function pthread_rwlockattr_init(var __attr: pthread_rwlockattr_t):longint;cdecl;external threadslib;
function pthread_rwlockattr_destroy(var __attr: pthread_rwlockattr_t):longint;cdecl;external threadslib;
function pthread_rwlockattr_getpshared(var __attr: pthread_rwlockattr_t; var __pshared: longint):longint;cdecl;external threadslib;
function pthread_rwlockattr_setpshared(var __attr: pthread_rwlockattr_t; __pshared:longint):longint;cdecl;external threadslib;
function pthread_rwlockattr_getkind_np(var __attr: pthread_rwlockattr_t; var __pref: longint):longint;cdecl;external threadslib;
function pthread_rwlockattr_setkind_np(var __attr: pthread_rwlockattr_t; __pref:longint):longint;cdecl;external threadslib;
function pthread_spin_init(var __lock: pthread_spinlock_t; __pshared:longint):longint;cdecl;external threadslib;
function pthread_spin_destroy(var __lock: pthread_spinlock_t):longint;cdecl;external threadslib;
function pthread_spin_lock(var __lock: pthread_spinlock_t):longint;cdecl;external threadslib;
function pthread_spin_trylock(var __lock: pthread_spinlock_t):longint;cdecl;external threadslib;
function pthread_spin_unlock(var __lock: pthread_spinlock_t):longint;cdecl;external threadslib;
function pthread_barrier_init(var __barrier: pthread_barrier_t;var __attr: pthread_barrierattr_t; __count:dword):longint;cdecl;external threadslib;
function pthread_barrier_destroy(var __barrier: pthread_barrier_t):longint;cdecl;external threadslib;
function pthread_barrierattr_init(var __attr: pthread_barrierattr_t):longint;cdecl;external threadslib;
function pthread_barrierattr_destroy(var __attr: pthread_barrierattr_t):longint;cdecl;external threadslib;
function pthread_barrierattr_getpshared(var __attr: pthread_barrierattr_t; var __pshared:longint):longint;cdecl;external threadslib;
function pthread_barrierattr_setpshared(var __attr: pthread_barrierattr_t; __pshared:longint):longint;cdecl;external threadslib;
function pthread_barrier_wait(var __barrier: pthread_barrier_t):longint;cdecl;external threadslib;
function pthread_key_create(var __key: pthread_key_t; __destr_function :TKeyValueDestructor):longint;cdecl; external threadslib;
function pthread_once(var __once_control: pthread_once_t; __init_routine:Tprocedure ):longint;cdecl; external threadslib;
function pthread_setcancelstate(__state:longint; var __oldstate:longint):longint;cdecl; external threadslib;
function pthread_setcanceltype(__type:longint;var __oldtype:longint):longint;cdecl; external threadslib;

procedure _pthread_cleanup_push(var __buffer: _pthread_cleanup_buffer; __routine:TPthreadCleanupRoutine; __arg:pointer);cdecl; external threadslib;
procedure _pthread_cleanup_pop(var __buffer:_pthread_cleanup_buffer; __execute:longint);cdecl; external threadslib;
function pthread_sigmask(__how:longint; var __newmask:__sigset_t; var __oldmask:__sigset_t):longint;cdecl; external threadslib;
}

{ Borland compatibility }

function GetCurrentThreadID: TTHreadID ; cdecl; external threadslib name 'pthread_self' + LIBC_SUFFIX ;
function InitializeCriticalSection(var lpCriticalSection: TRTLCriticalSection): Integer; 
function EnterCriticalSection(var lpCriticalSection: TRTLCriticalSection): Integer; cdecl; external threadslib name 'pthread_mutex_lock' + LIBC_SUFFIX ;
function LeaveCriticalSection(var lpCriticalSection: TRTLCriticalSection): Integer; cdecl; external threadslib name 'pthread_mutex_unlock' + LIBC_SUFFIX ;
function TryEnterCriticalSection(var lpCriticalSection: TRTLCriticalSection): Boolean; 
function DeleteCriticalSection(var lpCriticalSection: TRTLCriticalSection): Integer; cdecl; external threadslib name 'pthread_mutex_destroy' + LIBC_SUFFIX ;
          
Type
  TPThreadFunc = function(Parameter: Pointer): Integer; cdecl;
  PPthreadCleanupBuffer = ^_pthread_cleanup_buffer;