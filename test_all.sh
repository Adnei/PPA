#!/bin/bash
FILE="${1}.logs";
RESULT="";
echo "Executing tests...";
echo "#mtx;th;time" > "${FILE}";
for i in {100,500,1000,1500}; do
	for th in {1,5,10,15,20,25,30}; do
		RES_SUM=0;
		for exec_idx in `seq 1 ${2}`; do
			RES_SUM=$( awk "BEGIN {print ${RES_SUM}+$( ./${1} ${i} ${th} ) ; exit}" );
		done;
		AVG=$( python -c "print ${RES_SUM}/${2}" );
		echo "${i};${th};${AVG}" >> "${FILE}";
	done;
done;
echo "We're done!";
