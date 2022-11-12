#!/bin/bash
make
./run.sh ./src/parser $1
qemu-riscv64 a.out
