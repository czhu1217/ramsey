#!/bin/bash
cd files
./../ramlex $1 $2 $3
./../toCNF ramsey$1_$2_$3.out
./../../cadical/build/cadical ramsey$1_$2_$3.cnf
