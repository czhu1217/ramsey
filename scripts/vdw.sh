#!/bin/bash
cd cnfs
./../vdw2c $1 2 3 $2
cd ../../cadical/
./build/cadical ./../research/cnfs/vdw2c$1_2_3-$2.cnf
cd ../research