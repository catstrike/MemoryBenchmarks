	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_atomicWrite            ## -- Begin function atomicWrite
	.p2align	4, 0x90
_atomicWrite:                           ## @atomicWrite
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi2:
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rsi
	movq	-8(%rbp), %rdi
	movq	%rsi, %rax
	movq	%rdi, %rdx
	## InlineAsm Start
	movq	%rax, (%rdx)
	## InlineAsm End
	movq	%rax, -16(%rbp)
	movq	%rdx, -8(%rbp)
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_writer                 ## -- Begin function writer
	.p2align	4, 0x90
_writer:                                ## @writer
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi3:
	.cfi_def_cfa_offset 16
Lcfi4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi5:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	leaq	L_.str(%rip), %rax
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	movq	%rdi, -16(%rbp)
	movq	%rax, %rdi
	movb	$0, %al
	callq	_printf
	movq	$0, -24(%rbp)
	movl	%eax, -28(%rbp)         ## 4-byte Spill
LBB1_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpq	$1000000, -24(%rbp)     ## imm = 0xF4240
	jae	LBB1_4
## BB#2:                                ##   in Loop: Header=BB1_1 Depth=1
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	$-1, (%rax)
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	$1, (%rax)
## BB#3:                                ##   in Loop: Header=BB1_1 Depth=1
	movq	-24(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -24(%rbp)
	jmp	LBB1_1
LBB1_4:
	xorl	%eax, %eax
                                        ## kill: %RAX<def> %EAX<kill>
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_reader                 ## -- Begin function reader
	.p2align	4, 0x90
_reader:                                ## @reader
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi6:
	.cfi_def_cfa_offset 16
Lcfi7:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi8:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	leaq	L_.str.1(%rip), %rax
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	movq	%rdi, -16(%rbp)
	movq	%rax, %rdi
	movb	$0, %al
	callq	_printf
	movq	$0, -24(%rbp)
	movl	%eax, -36(%rbp)         ## 4-byte Spill
LBB2_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpq	$1000000, -24(%rbp)     ## imm = 0xF4240
	jae	LBB2_7
## BB#2:                                ##   in Loop: Header=BB2_1 Depth=1
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	cmpq	$1, %rax
	je	LBB2_5
## BB#3:                                ##   in Loop: Header=BB2_1 Depth=1
	movq	-32(%rbp), %rax
	cmpq	$-1, %rax
	je	LBB2_5
## BB#4:                                ##   in Loop: Header=BB2_1 Depth=1
	leaq	L_.str.2(%rip), %rdi
	movq	-32(%rbp), %rsi
	movb	$0, %al
	callq	_printf
	movl	%eax, -40(%rbp)         ## 4-byte Spill
LBB2_5:                                 ##   in Loop: Header=BB2_1 Depth=1
	jmp	LBB2_6
LBB2_6:                                 ##   in Loop: Header=BB2_1 Depth=1
	movq	-24(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -24(%rbp)
	jmp	LBB2_1
LBB2_7:
	xorl	%eax, %eax
                                        ## kill: %RAX<def> %EAX<kill>
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi9:
	.cfi_def_cfa_offset 16
Lcfi10:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi11:
	.cfi_def_cfa_register %rbp
	subq	$96, %rsp
	leaq	L_.str.3(%rip), %rax
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rax, %rdi
	movb	$0, %al
	callq	_printf
	leaq	L_.str.4(%rip), %rdi
	movl	$4194304, %esi          ## imm = 0x400000
	movl	$64, %edx
	movl	$65536, %ecx            ## imm = 0x10000
	movl	%eax, -68(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	movl	$128, %ecx
	movl	%ecx, %edi
	movl	%eax, -72(%rbp)         ## 4-byte Spill
	callq	_malloc
	leaq	L_.str.5(%rip), %rdi
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	addq	$64, %rax
	addq	$1, %rax
	shrq	$6, %rax
	shlq	$6, %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	addq	$-3, %rax
	movq	%rax, -40(%rbp)
	movq	-24(%rbp), %rsi
	movb	$0, %al
	callq	_printf
	leaq	L_.str.6(%rip), %rdi
	movq	-32(%rbp), %rsi
	movl	%eax, -76(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str.7(%rip), %rdi
	movq	-40(%rbp), %rsi
	movl	%eax, -80(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	-48(%rbp), %rdi
	leaq	_reader(%rip), %rsi
	leaq	-64(%rbp), %r8
	movq	-40(%rbp), %r9
	movq	$1, (%r9)
	movq	-40(%rbp), %r9
	movq	%r9, -64(%rbp)
	movq	%r8, %rdx
	movl	%eax, -84(%rbp)         ## 4-byte Spill
	callq	_start_thread
	leaq	-56(%rbp), %rdi
	leaq	_writer(%rip), %rsi
	leaq	-64(%rbp), %rdx
	movl	%eax, -88(%rbp)         ## 4-byte Spill
	callq	_start_thread
	movq	-48(%rbp), %rdi
	movl	%eax, -92(%rbp)         ## 4-byte Spill
	callq	_join_thread
	movq	-56(%rbp), %rdi
	callq	_join_thread
	movq	-24(%rbp), %rdi
	callq	_free
	xorl	%eax, %eax
	addq	$96, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"Writer started.\n"

L_.str.1:                               ## @.str.1
	.asciz	"Reader started.\n"

L_.str.2:                               ## @.str.2
	.asciz	"Broken value! (%lli)\n"

L_.str.3:                               ## @.str.3
	.asciz	"=======================================================\n"

L_.str.4:                               ## @.str.4
	.asciz	"Cache size: %i, line size: %i, total lines: %i\n"

L_.str.5:                               ## @.str.5
	.asciz	"Base address:      %zu\n"

L_.str.6:                               ## @.str.6
	.asciz	"Beginning of line: %zu\n"

L_.str.7:                               ## @.str.7
	.asciz	"Variable address:  %zu\n"


.subsections_via_symbols
