#!/bin/bash
if [ ! -d dump ]; then
mkdir "dump"
fi
a=1
while true
do
	if [ ! -f ./dump/"$a" ]; then
		script --force dump/"$a"
		break;
	else
		a=$(($a+1))
	fi
done