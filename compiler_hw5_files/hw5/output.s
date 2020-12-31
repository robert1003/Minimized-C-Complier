	.section .sdata,"aw"
	.section .sbss,"aw",@nobits
	.text
	.align 1
	.globl MAIN
	.type MAIN, @function
MAIN:
	fmv.w.x ft0,zero
	sd ra,-8(sp)
	sd fp,-16(sp)
	addi fp,sp,-16
	addi sp,sp,-16
	lui t0, 1953
	addi t0, t0, 528
	sub sp,sp,t0
	sw s1,-4(fp)
	addi t0, zero, 0
	lui t1, 977
	addi t1, t1, -1784
	sub t1,fp,t1
	lw s1,0(t1)
	mv s1, t0
	addi t0, zero, 123
	addi t1, zero, 123
	slli t2,t1,2
	lui t1, 977
	addi t1, t1, -1788
	sub t1,fp,t1
	add t2,t2,t1
	sw t0,0(t2)
	addi t0, zero, 456
	addi t1, zero, 456
	slli t2,t1,2
	lui t1, 1953
	addi t1, t1, 520
	sub t1,fp,t1
	add t2,t2,t1
	sw t0,0(t2)
	mv a0,s1
	jal _write_int
	addi t0, zero, 123
	slli t1,t0,2
	lui t2, 977
	addi t2, t2, -1788
	sub t2,fp,t2
	add t1,t1,t2
	lw t0,0(t1)
	mv a0,t0
	jal _write_int
	addi t0, zero, 456
	slli t1,t0,2
	lui t2, 1953
	addi t2, t2, 520
	sub t2,fp,t2
	add t1,t1,t2
	lw t0,0(t1)
	mv a0,t0
	jal _write_int
MAIN_EXIT_:
	lw s1,-4(fp)
	ld ra,8(fp)
	addi sp,fp,16
	ld fp,0(fp)
	jr ra
	.size MAIN, .-MAIN
	.section .rodata
