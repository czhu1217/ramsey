#!/bin/bash
cd k2cnf
./../k2.exe $1 $2 $3
./../toCNF k2_$1.out
./../../cadical/build/cadical k2_$1.cnf
