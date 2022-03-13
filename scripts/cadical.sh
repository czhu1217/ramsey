#!/bin/bash
cd k2cnf
./../k2 $1 $2 $3 $4
./../toCNF maxedge$1_$2_$3_$4.out
./../../cadical/build/cadical maxedge$1_$2_$3_$4.cnf
