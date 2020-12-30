	.section .sdata,"aw"
	.section .sbss,"aw",@nobits
	.text
	.align 1
	.globl _start_MAIN
	.type _start_MAIN, @function
_start_MAIN:
	sd ra,-8(sp)
	sd fp,-16(sp)
	addi fp,sp,-16
	addi sp,sp,-16
	addi sp,sp,-32
	sw s1,-4(fp)
	sw s2,-8(fp)
	fsw fs0,-12(fp)
	fsw fs1,-16(fp)
	lui t0,%hi(.LC5)
	addi a0,t0,%lo(.LC5)
	call _write_str
	call _read_int
	mv t0, a0
	lw s1,-20(fp)
	mv s1, t0
	lui t0,%hi(.LC5)
	addi a0,t0,%lo(.LC5)
	call _write_str
	call _read_int
	mv t0, a0
	lw s2,-24(fp)
	mv s2, t0
	lui t0,%hi(.LC5)
	addi a0,t0,%lo(.LC5)
	call _write_str
	call _read_float
	fmv.s ft0, fa0
	flw fs0,-28(fp)
	fmv.s fs0, ft0
	lui t0,%hi(.LC5)
	addi a0,t0,%lo(.LC5)
	call _write_str
	call _read_float
	fmv.s ft0, fa0
	flw fs1,-32(fp)
	fmv.s fs1, ft0
	mv a0,s1
	jal _write_int
	lui t0,%hi(.LC6)
	addi a0,t0,%lo(.LC6)
	call _write_str
	mv a0,s2
	jal _write_int
	lui t0,%hi(.LC6)
	addi a0,t0,%lo(.LC6)
	call _write_str
	fmv.s fa0,fs0
	jal _write_float
	lui t0,%hi(.LC6)
	addi a0,t0,%lo(.LC6)
	call _write_str
	fmv.s fa0,fs1
	jal _write_float
	lui t0,%hi(.LC6)
	addi a0,t0,%lo(.LC6)
	call _write_str
	addi t0, zero, 0
	mv a0, t0
	j main_EXIT_
main_EXIT_:
	flw fs1,-16(fp)
	flw fs0,-12(fp)
	lw s2,-8(fp)
	lw s1,-4(fp)
	ld ra,8(fp)
	addi sp,fp,16
	ld fp,0(fp)
	jr ra
	.size main, .-main
	.section .rodata
	.align 3
.LC6:
	.string "\n\000"
	.align 3
.LC5:
	.string "input:\000"
