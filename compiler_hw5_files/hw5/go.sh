#!/bin/bash
make
./run.sh ./parser $1
qemu-riscv64 a.out
