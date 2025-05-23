{
    This file is part of the Free Pascal run time library.
    Copyright (c) 2005 by Michael Van Canneyt, Peter Vreman,
    & Daniel Mantione, members of the Free Pascal development team.

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

{
 Linux ELF startup code for Free Pascal


 Stack layout at program start:

         nil
         envn
         ....
         ....           ENVIRONMENT VARIABLES
         env1
         env0
         nil
         argn
         ....
         ....           COMMAND LINE OPTIONS
         arg1
         arg0
         argc <--- esp
}

{$asmmode gas}

var
  libc_environ: pchar; external name '__environ@GLIBC_2.2.5';
  libc_fpu_control: word; external name '__fpu_control@GLIBC_2.2.5';
  libc_init_proc: procedure; external name '_init@GLIBC_2.2.5';
  libc_fini_proc: procedure; external name '_fini@GLIBC_2.2.5';
  _etext: pointer; external name '_etext@GLIBC_2.2.5';

  fpc_ret,fpc_ret_rbp : pointer;

procedure libc_atexit; external name 'atexit@GLIBC_2.2.5';
procedure libc_exit; external name '__libc_exit@GLIBC_2.2.5';
procedure libc_init; external name '__libc_init@GLIBC_2.2.5';
procedure libc_setfpucw; external name '__setfpucw@GLIBC_2.2.5';
procedure libc_start_main; external name '__libc_start_main@GLIBC_2.2.5';
procedure gmon_monstartup; external name 'monstartup@GLIBC_2.2.5';
procedure gmon_mcleanup; external name '_mcleanup@GLIBC_2.2.5';

procedure _FPC_libc_start; forward;
procedure _FPC_libc_haltproc(e:longint); forward;

procedure main_stub; assembler; nostackframe;
  asm
    { save return address }
    popq    %rax

    // stack alignment
    pushq	%rax

    movq    %rax,fpc_ret(%rip)
    movq    %rbp,fpc_ret_rbp(%rip)
    pushq   %rax

    { Initialize gmon }
    movq    _etext@GOTPCREL(%rip),%rsi
    movq    _FPC_libc_start@GOTPCREL(%rip),%rdi
    call    gmon_monstartup@PLT

    movq    gmon_mcleanup@GOTPCREL(%rip),%rdi
    call    libc_atexit@PLT

{$ifdef FPC_HAS_INDIRECT_ENTRY_INFORMATION}
    movq    SysInitEntryInformation@GOTPCREL(%rip),%rdi

    { Save initial stackpointer }
    movq    %rsp,TEntryInformation.OS.stkptr(%rdi)

    { store stack length }
    movq    StackLength@GOTPCREL(%rip),%rax
    movq    %rax,TEntryInformation.OS.stklen(%rdi)

    { store pointer to haltproc }
    movq    _FPC_libc_haltproc@GOTPCREL(%rip),%rax
    movq    %rax,TEntryInformation.OS.haltproc(%rdi)

    xorq    %rbp,%rbp
    call    SysEntry@PLT
{$else FPC_HAS_INDIRECT_ENTRY_INFORMATION}
    { Save initial stackpointer }
    movq    initialstkptr@GOTPCREL(%rip),%rax
    movq    %rsp,(%rax)

    { start the program }
    xorq    %rbp,%rbp
    call    PASCALMAIN@PLT
{$endif FPC_HAS_INDIRECT_ENTRY_INFORMATION}
    hlt
  end;


procedure ini_dummy;
  begin
  end;

{******************************************************************************
                          C library start/halt
 ******************************************************************************}

 procedure _FPC_libc_start; assembler; nostackframe; public name '_start';
  asm
    { Clear the frame pointer.  The ABI suggests this be done, to mark
     the outermost frame obviously.  }
    xorq %rbp, %rbp

    { Extract the arguments as encoded on the stack and set up
       the arguments for __libc_start_main (int (*main) (int, char **, char **),
    	   int argc, char *argv,
    	   void (*init) (void), void (*fini) (void),
    	   void (*rtld_fini) (void), void *stack_end).
       The arguments are passed via registers and on the stack:
    main:		%rdi
    argc:		%rsi
    argv:		%rdx
    init:		%rcx
    fini:		%r8
    rtld_fini:	%r9
    stack_end:      stack.  }

    movq %rdx, %r9          { Address of the shared library termination
                             function.  }
    popq %rsi               { Pop the argument count.  }
    movq %rsp, %rdx         { argv starts just at the current stack top.  }

{$ifdef FPC_HAS_INDIRECT_ENTRY_INFORMATION}
    movq SysInitEntryInformation@GOTPCREL(%rip),%rcx

    { argc is longint in EntryInformation, thus use %edi register }
    movl %esi,TEntryInformation.OS.argc(%rcx)
    movq %rsp,TEntryInformation.OS.argv(%rcx)
    leaq 8(,%rsi,8),%rax
    addq %rsp,%rax
    movq %rax,TEntryInformation.OS.envp(%rcx)
{$else FPC_HAS_INDIRECT_ENTRY_INFORMATION}
    movq operatingsystem_parameter_argc@GOTPCREL(%rip),%rax
    movq %rsi,(%rax)
    movq operatingsystem_parameter_argv@GOTPCREL(%rip),%rax
    movq %rsp,(%rax)
    leaq 8(,%rsi,8),%rax
    addq %rsp,%rax
    movq operatingsystem_parameter_envp@GOTPCREL(%rip),%rcx
    movq %rax,(%rcx)
{$endif FPC_HAS_INDIRECT_ENTRY_INFORMATION}

    { Align the stack to a 16 byte boundary to follow the ABI.  }
    andq  $0xfffffffffffffff0, %rsp

    pushq %rax              { Push garbage because we push 8 more bytes.  }

    { Provide the highest stack address to the user code (for stacks
     which grow downwards).  }
    pushq %rsp

    { Pass address of our own entry points to .fini and .init.  }
    movq ini_dummy@GOTPCREL(%rip), %r8
    movq ini_dummy@GOTPCREL(%rip), %rcx

    movq main_stub@GOTPCREL(%rip), %rdi

    { Call the user's main function, and exit with its value.
     But let the libc call main.    }
    call libc_start_main@PLT

    hlt                     { Crash if somehow `exit' does return.  }

    { We need this stuff to make gdb behave itself, otherwise
      gdb will chokes with SIGILL when trying to debug apps.
    }
(*
    .section ".note.ABI-tag", "a"
    .align 4
    .long 1f - 0f
    .long 3f - 2f
    .long  1
0:  .asciz "GNU"
1:  .align 4
2:  .long 0
    .long 2,4,0
3:  .align 4
*)
  end;

procedure _FPC_libc_haltproc(e:longint); assembler; nostackframe; public name '_haltproc';
  asm
    movl %edi,%eax
    popq    %rdx                    { keep stack aligned }
    movq fpc_ret(%rip),%rdx         { return to libc }
    movq fpc_ret_rbp(%rip),%rbp
    pushq %rdx
  end;
