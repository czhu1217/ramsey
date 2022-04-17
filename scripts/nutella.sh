#!/usr/bin/env bash

if [ $# -lt 2 ]
then echo "Not enough arguments. Input number of vertices and k value."
else

    N=$1
    K=$2
    N2=$(( N * N ))

        COUNTER=0

        SATISFIABLE=1

        echo "Generating all ${N}-vertex non-isomorphic graphs with nauty..."
        ./nauty/nauty27r3/geng ${N} > both_${N}_${K}.txt

        echo -e "\nGenerating all satisfying ${N}-vertex graphs using k = ${K} with cadical..."

        ./psbR.out -A $N -k $K > all${N}_${K}.cnf
        > all_adjmat_${N}_${K}.txt
        > missing_${N}_${K}.txt

        SECONDS=0

        while [ $SATISFIABLE = 1 ]

        do
            #get soln from cadical and cut to relevant part
            (../cadical/build/cadical -q --forcephase=1 --phase=0 all${N}_${K}.cnf | sed -e "/${N2}/q") > all_out_${N}_${K}.txt

            #check if unsatisfiable
            if grep -q "UNSATISFIABLE" all_out_${N}_${K}.txt

            then SATISFIABLE=0

            else

                COUNTER=$((COUNTER+1))

                #get rid of non-numbers
                (grep --colour -E -o -e '-?[0-9]*' all_out_${N}_${K}.txt | xargs -n ${N2} | awk 'NR>1{exit};1') > all_nbs_${N}_${K}.txt

                #run adjmat on each line
                (cat all_nbs_${N}_${K}.txt | ./adjmat.out `xargs`) >> all_adjmat_${N}_${K}.txt

                #flip signs and add to cnf
                (cat all_nbs_${N}_${K}.txt | ./flip.out `xargs`) >> all${N}_${K}.cnf
                echo 0 >> all${N}_${K}.cnf

                #increment clauses by 1
                perl -i -pe '/p cnf/ && s/(\d+)$/$1+1/e' all${N}_${K}.cnf

            fi

        done

        DURATION_IN_SECONDS=$SECONDS

        #print number of graphs
        echo "Found $COUNTER satisfying graphs in $DURATION_IN_SECONDS seconds"

        echo -e "\nComparing isomorphic graphs..."

        #convert to g6 format
        ./nauty/nauty27r3/amtog -q -n${N} all_adjmat_${N}_${K}.txt g6_${N}_${K}.txt

        #compare isomorphisms
        ./nauty/nauty27r3/shortg -dk g6_${N}_${K}.txt ig6_${N}_${K}.txt

        #convert output to adjmat format
        ./nauty/nauty27r3/listg -A ig6_${N}_${K}.txt iso_${N}_${K}.txt

        if [ -s iso_${N}_${K}.txt ]
        then echo "Graphs that are isomorphic to each other written to iso_${N}_${K}.txt"
        else echo "No isomorphic graphs"
             rm iso_${N}_${K}.txt
        fi

        echo -e "\nChecking for missing graphs..."

        cat g6_${N}_${K}.txt >> both_${N}_${K}.txt
        ./nauty/nauty27r3/shortg -q -vk both_${N}_${K}.txt both_${N}_${K}.txt 2> missing_cmp_${N}_${K}.txt
        ./nauty/nauty27r3/listg -A both_${N}_${K}.txt both_mat_${N}_${K}.txt

        #isolate graphs that are not isomorphic to anything
        (grep -P -o '\d+ :\s+\d+$' missing_cmp_${N}_${K}.txt) > temp_cmp_${N}_${K}.txt
        while IFS= read line; do
              VAR=$(echo "$line" | grep -P -o '^\s*\d+' | sed -e 's/^[[:space:]]*//')
              (grep -P -A $(( N + 1 )) "Graph\s*${VAR}," both_mat_${N}_${K}.txt) >> missing_${N}_${K}.txt ;
        done < temp_cmp_${N}_${K}.txt

        if [ -s missing_${N}_${K}.txt ]
        then echo "Missing graphs written to missing_${N}_${K}.txt"
        else echo "Not missing any graphs"
             rm missing_${N}_${K}.txt
        fi

	#badly written symmbreak check
	if [ ${K} -gt 0 ]
	then

	    echo -e "\nChecking symmetry breaking..."

	    COUNT=1

	    ./nauty/nauty27r3/shortg -v -uq ig6_${N}_${K}.txt 2> symbreak_cmp_${N}_${K}.txt

	    perl -i -pe 's/(\d+) : //' symbreak_cmp_${N}_${K}.txt
            sed -i '/^[[:space:]]*$/d' symbreak_cmp_${N}_${K}.txt

            while IFS= read line; do

		K_SAME=1
		>scmp_${N}_${K}.txt

		#isolate graphs that are isomorphic to each other
	  	for VAR in $line; do
                    (grep -P -A $(( N + 1 )) "Graph\s*${VAR}," iso_${N}_${K}.txt) >> symcheck_${N}_${K}_${COUNT}.txt
                    (grep -P -A ${K} "Graph\s*${VAR}," symcheck_${N}_${K}_${COUNT}.txt | grep -P -v "Graph\s*${VAR},") >> scmp_${N}_${K}.txt
	        done

		#verify that top k lines of isomorphic graphs are identical
                LINES=$(wc -l < scmp_${N}_${K}.txt)
		for (( i = 1; i <= ${K}; i++ )); do
		  FST=$(awk "NR==${i}" scmp_${N}_${K}.txt)
		  for (( j = ${i} + ${K}; j <= ${LINES}; j += ${K} )); do
		    OTR=$(awk "NR==${j}" scmp_${N}_${K}.txt)
		    if [ "$FST" != "$OTR" ]
		    then K_SAME=0
		    fi
		  done
		done

		if [ $K_SAME = 1 ]
		then >symcheck_${N}_${K}_${COUNT}.txt
		else COUNT=$((COUNT+1))
		fi

	    done < symbreak_cmp_${N}_${K}.txt

	    if [ ${COUNT} -gt 1 ]
	    then echo "$((COUNT-1)) unbroken symmetries written to symcheck_${N}_${K}_#.txt"
	    else echo "All good"
		 rm symcheck_${N}_${K}_*.txt
	    fi

	    #cleanup
	    rm symbreak_cmp_${N}_${K}.txt
	    rm scmp_${N}_${K}.txt

	fi

        #cleanup
        rm all_out_${N}_${K}.txt
        rm all_nbs_${N}_${K}.txt
        rm g6_${N}_${K}.txt
        rm ig6_${N}_${K}.txt
        rm both_${N}_${K}.txt
        rm both_mat_${N}_${K}.txt
        rm missing_cmp_${N}_${K}.txt
        rm temp_cmp_${N}_${K}.txt

fi
