#!/usr/bin/env bash

if [ $# -lt 2 ]
then echo "Not enough arguments. Input number of vertices and k value."
else

    N=$1
    K=$2
    N2=$(( N * N ))

    SATISFIABLE=1

    ./unaryAdder/ramsey.exe $N $K
    ./toCNF.exe all${N}_${K}.out
    > all_adjmat_${N}_${K}.txt
    > missing_${N}_${K}.txt

    ./../allsat-cadical/build/cadical --allsat -n -q all${N}_${K}.cnf 
fi