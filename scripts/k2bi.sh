#!/bin/bash
cd k2bicnfs
./../k2bi.exe $1 $2 $3
./../toCNF.exe k2_$1.out
./../../cadical/build/cadical k2_$1.cnf --unsat
