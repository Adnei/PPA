#!/bin/bash
FILE="${1}.logs"
RESULT=""
echo "Executing tests...";
echo "#mtx;th;time" > "${FILE}";
for i in {100,500,1000,1500}; do
	for th in {1,5,10,15,20,25,30}; do
    RESULT=$( ./${1} ${i} ${th} );
		echo "${i};${th};${RESULT}" >> "${FILE}";
	done;
done;
echo "We're done!";
