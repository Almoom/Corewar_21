#!/bin/bash

RED='\e[0;31m'
EOC='\e[0;30m'

tests=($(ls | grep ".s$"))



for file in "${tests[@]}"
do
	rm -f *.cor
	# for (( c=1; c<=20; c++ ))
	# do
		my=$(./asm $file)
		notmy=$(./asm2 $file)

		if [ "$my" == "$notmy" ]
		then
			echo "$file	: идентичны."
		else
			echo -e "______________$file	: имеют различия.___________"
			diff  <(echo "$my" ) <(echo "$notmy")
			##exit 0;
		fi
	done
