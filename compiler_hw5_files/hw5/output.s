	.section .sdata,"aw"
	.section .sbss,"aw",@nobits
	.globl  i
	.section  .sbss
	.align  2
	.type i, @object
	.size i, 4
i:
	.zero 4
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
	addi sp,sp,-16
	sw s1,-4(fp)
	addi t0, zero, 0
	lui t1,%hi(i)
	lw s1,%lo(i)(t1)
	mv s1, t0
	lui t0,%hi(i)
	sw s1,%lo(i)(t0)
_WHILE_5:
	lui t0,%hi(i)
	lw s1,%lo(i)(t0)
	addi t0, zero, 10
	sub t1, s1, t0
	sltz t1, t1
	beqz t1, _EXIT_5
	lui t0,%hi(i)
	lw s1,%lo(i)(t0)
	mv a0,s1
	jal _write_int
	lui t0,%hi(.LC6)
	addi a0,t0,%lo(.LC6)
	call _write_str
	lui t0,%hi(i)
	lw s1,%lo(i)(t0)
	addi t0, zero, 1
	add t1, s1, t0
	mv s1, t1
	lui t0,%hi(i)
	sw s1,%lo(i)(t0)
	j _WHILE_5
_EXIT_5:
MAIN_EXIT_:
	lw s1,-4(fp)
	ld ra,8(fp)
	addi sp,fp,16
	ld fp,0(fp)
	jr ra
	.size MAIN, .-MAIN
	.section .rodata
	.align 3
.LC6:
	.string "\n\000"
