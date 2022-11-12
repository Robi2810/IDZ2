	.file	"5.c"
.LC0:
	.string	"%s"
.LC1:
	.string	"incorrect input"
	.text
	.globl	get_string
	.type	get_string, @function
get_string:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	pushq	%rbx 			#char c
	pushq	%r15			#*test
	pushq	%r14			#char *s
	pushq	%r13			#capacit 
	pushq	%r12			#*len
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, %r12		#go to func int *len
	movq	%rsi, %r15		#go to func int *test
	movq	%r12, %rax
	movl	$0, (%rax)		#*len = 0
	movq	%r15, %rax
	movl	$0, (%rax)		#*test = 0
	movq	$1, %r13
	movl	$1, %edi		#capacit = 1
	call	malloc@PLT
	movq	%rax, %r14		#char *s
	call	getchar@PLT
	movb	%al, %bl		#char c 
	jmp	.L2
.L4:
	movq	%r12, %rax
	movl	(%rax), %eax
	leal	1(%rax), %ecx
	movq	%r12, %rdx
	movl	%ecx, (%rdx)
	movslq	%eax, %rdx
	movq	%r14, %rax
	addq	%rax, %rdx
	movzbl	%bl, %eax
	movb	%al, (%rdx)
	movq	%r12, %rax
	movl	(%rax), %eax
	cmpq	%rax, %r13
	jg	.L3
	salq	%r13
	movq	%r13, %rax
	movslq	%eax, %rdx
	movq	%r14, %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	realloc@PLT
	movq	%rax, %r14
.L3:
	call	getchar@PLT
	movb	%al, %bl
.L2:
	cmpb	$10, %bl
	jne	.L4
	movq	%r12, %rax
	movl	(%rax), %eax
	movslq	%eax, %rdx
	movq	%r14, %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	movq	%r14, %rax		#return s
	movq 	%rbp, %rsp
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	get_string, .-get_string
	.globl	change
	.type	change, @function
