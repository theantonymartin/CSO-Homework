#!/bin/bash
while true
do 
	ps aux --sort -rss | head -n $((1+$1)) | tail -n $1
	sleep $2
done
