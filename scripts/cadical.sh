#!/bin/bash
cd bad
./../maxedge $1 $2 $3 $4
./../toCNF maxedge$1_$2_$3_$4.out
./../../cadical/build/cadical maxedge$1_$2_$3_$4.cnf
