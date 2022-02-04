#!/bin/bash
cd cnfs
./../vdw2c $1 2 3 $2 $3 $4
cd ../../ubcsat/
./ubcsat -alg ddfw  -runs $4 -solve -i ./../research/cnfs/vdw2c$1_2_3-$2.cnf
# ./ubcsat -alg ddfw -cutoff $3 -runs $4 -solve -i ./../research/cnfs/vdw2c$1_2_3-$2.cnf
# ./ubcsat -alg ddfw -cutoff $3 -runs $4 -solve -i ./../research/cnfs/vdw2c$1_2_3-$2.cnf
# ./ubcsat -alg ddfw -cutoff $3 -runs $4 -solve -i ./../research/cnfs/vdw2c$1_2_3-$2.cnf
# ./ubcsat -alg ddfw -cutoff $3 -runs $4 -solve -i ./../research/cnfs/vdw2c$1_2_3-$2.cnf
# ./ubcsat -alg ddfw -cutoff $3 -runs $4 -solve -i ./../research/cnfs/vdw2c$1_2_3-$2.cnf
# ./ubcsat -alg ddfw -cutoff $3 -runs $4 -solve -i ./../research/cnfs/vdw2c$1_2_3-$2.cnf
# ./ubcsat -alg ddfw -cutoff $3 -runs $4 -solve -i ./../research/cnfs/vdw2c$1_2_3-$2.cnf
# ./ubcsat -alg ddfw -cutoff $3 -runs $4 -solve -i ./../research/cnfs/vdw2c$1_2_3-$2.cnf
# ./ubcsat -alg ddfw -cutoff $3 -runs $4 -solve -i ./../research/cnfs/vdw2c$1_2_3-$2.cnf
cd ../research