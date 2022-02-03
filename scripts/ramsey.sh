#!/bin/bash
cd cnfs
./../maxedge $1 $2 $3 $4
./../toCNF maxedge$1_$2_$3_$4.out
cd ../../cadical
./build/cadical ./../ramsey/cnfs/maxedge$1_$2_$3_$4.cnf
cd ../ramsey