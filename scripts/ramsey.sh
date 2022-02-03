#!/bin/bash
cd cnfs
./../maxedge $1 $2 $3
./../toCNF maxedge$1_$2_$3.out
cd ../../cadical
./build/cadical ./../research/cnfs/maxedge$1_$2_$3.cnf
cd ../research