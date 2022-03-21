#!/bin/bash
cd k2cnf
./../k2new.exe $1 $2 $3
./../toCNF.exe k2_$1.out
./../../cadical/build/cadical k2_$1.cnf --unsat
