#!/bin/bash
mkdir "archive-$2"
for i in `find $1  -type f ! -newermt "$2 00:00:00"` 
do 
	mv $i "archive-$2"
done