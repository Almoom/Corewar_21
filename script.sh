#!/bin/bash

RED='\033[1;31m'
GREEN='\033[0;32m'
EOC='\033[0m'

tests=($(ls test_binary/ | grep ".s$"))

for file in "${tests[@]}"
do

	# for (( c=1; c<=20; c++ ))
	# do
		my=$(./asm test_binary/$file)
		notmy=$(./asm2 test_binary/$file)

		if [ "$my" == "$notmy" ]
		then
			echo -e "${GREEN}$file : идентичны.${EOC}"
		else
			echo -e "${RED}$file : имеют различия.${EOC}"
			diff  <(echo "$my" ) <(echo "$notmy")
			##exit 0;
		fi
		rm -f test_binary/*.cor
	done
# done

tests=($(ls test_error/ | grep ".s$"))

for file in "${tests[@]}"
do

	# for (( c=1; c<=20; c++ ))
	# do
		my=$(./asm test_error/$file)
		notmy=$(./asm2 test_error/$file)

		if [ "$my" == "$notmy" ]
		then
			echo -e "${GREEN}$file : идентичны.${EOC}"
			echo "-----------------------------------"
		else
			echo -e "${RED}$file : имеют различия.${EOC}"
			echo "-----------------------------------"
			# diff  <(echo "$my" ) <(echo "$notmy")
			##exit 0;
		fi
		rm -f test_error/*.cor
	done
# done

# tests=($(ls test_error3/ | grep ".s$"))
#
# for file in "${tests[@]}"
# do
#
# 	# for (( c=1; c<=20; c++ ))
# 	# do
# 		my=$(./asm test_error3/$file)
# 		notmy=$(./asm2 test_error3/$file)
#
# 		if [ "$my" == "$notmy" ]
# 		then
# 			echo -e "${GREEN}$file : идентичны.${EOC}"
# 			echo "-----------------------------------"
# 		else
# 			echo -e "${RED}$file : имеют различия.${EOC}"
# 			echo "-----------------------------------"
# 			# diff  <(echo "$my" ) <(echo "$notmy")
# 			##exit 0;
# 		fi
# 		rm -f test_error3/*.cor
# 	done
# # done
