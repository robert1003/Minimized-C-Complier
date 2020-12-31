#!/bin/bash
$1 $2
riscv64-linux-gnu-gcc -O0 -static main.S
