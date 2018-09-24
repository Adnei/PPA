#!/bin/bash
FILE=""
NEWDIR=""
echo "Executing tests...";
for i in {100,500,1000,1500}; do
  NEWDIR="${i}x${i} ${1} logs";	
	mkdir "${NEWDIR}";
	FILE="${PWD}/${NEWDIR}/${i}x${i}.log";
	echo "#mtx;time{1,5,10,15,20,25,30}threads" >> "${FILE}";
	for th in {1,5,10,15,20,25,30}; do
		echo -n "${i}; " >> "${FILE}";
		./${1} ${i} ${th} >> "${FILE}";
	done;
done;
echo "We're done!";
