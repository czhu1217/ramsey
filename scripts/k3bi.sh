#!/bin/bash
cd k3bicnfs
./../binaryAdder/k3bi.exe $1 $2 $3
./../toCNF.exe k3_$1.out
./../../cadical/build/cadical k3_$1.cnf
