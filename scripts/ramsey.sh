#!/bin/bash
cd cnfs
./../maxedge $1 $2 $3 $4
./../toCNF maxedge$1_$2_$3_$4.out
cd ../../ubcsat/
./ubcsat -alg ddfw  -runs 10 -cutoff 300000 -solve -i ./../ramsey/cnfs/maxedge$1_$2_$3_$4.cnf
cd ../ramsey