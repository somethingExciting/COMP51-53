#!/bin/bash

for((i=1;i<=8;i++))
do
	array_size=$(($i*256));
	./matrix_math 1 $array_size;
	./matrix_math 2 $array_size;
	echo $'\n'
done
