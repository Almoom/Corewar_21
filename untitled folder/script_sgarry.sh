#!/bin/bash


test_path="./test_binary"

tests=($(ls $test_path | grep ".s$"))

rm -f ./test_binary/*.cor
for file in "${tests[@]}"
do
	./asm $test_path/$file

done
# chmod 777 ./test_binary/*.cor
