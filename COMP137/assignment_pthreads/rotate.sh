#!/bin/bash 

for((i=0;i<8;i++))
do
	sed -i 'thread_count=2^$i' serial_vector_rotate.c
	gcc serial_vector_rotate.c -o output -g -Wall -pthread -lm
	echo ./output
done
