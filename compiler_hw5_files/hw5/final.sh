#!/bin/bash
make
for fn in $@
do
    dir="${fn%/*}"
    bn="${fn%.c}"
    on="${bn##*/}"
    afn="${dir}/ans/${on}.ans"
    ./parser "$fn" &> /dev/null
    riscv64-linux-gnu-gcc -O0 -static main.S &> /dev/null
    qemu-riscv64 a.out > cur_out
    diff cur_out "$afn" > /dev/null
    if [[ $? != 0 ]];
    then
        echo "${fn} wrong"
        #diff cur_out "$afn"
    else
        echo "${fn} correct"
    fi
done
