#!/bin/bash
cd cnfs
./../vdw2c $1 2 3 $2
./../../ubcsat -alg ddfw  -runs $3 -solve -i -uniqueSol ./../ramsey/cnfs/vdw2c$1_2_3-$2.cnf
cd ../research