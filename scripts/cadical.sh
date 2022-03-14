#!/bin/bash
cd bad
./../k1 $1 $2 $3 $4
./../toCNF maxedge$1_$2_$3_$4.out
./../../cadical/build/cadical maxedge$1_$2_$3_$4.cnf --sat
