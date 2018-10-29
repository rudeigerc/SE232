#!/bin/bash

# compile files
rm -f WordLadder RandomWriter

if [ -f RandomWriter.cpp ]; then
	clang++ RandomWriter.cpp --std=c++11 -O2 -o RandomWriter
else
	echo "RandomWriter.cpp not found"
fi

if [ -f WordLadder.cpp ]; then
	clang++ WordLadder.cpp --std=c++11 -O2 -o WordLadder
else
	echo "WordLadder.cpp not found"
	echo "Part A score: 0 / 45"
	exit 1
fi

function compare() {
	first=$1
	second=$2
	count=0
	if [ ${#first} -eq ${#second} ]; then
		for ((i = 0; i < ${#first}; i++)); do
			if [ ${first:i:1} != ${second:i:1} ]; then
				count=$(($count + 1))
			fi
		done
		if [ $count -ne 1 ]; then
			return 1
		else
			return 0
		fi
	else
		return 1
	fi
}

score=0
for trace in $(ls traces); do
	line=$(gtimeout 100 ./WordLadder <traces/$trace >&1 | head -1)
	if [[ $(echo "$line" | grep "ladder") == "" ]]; then
		echo -e "$trace......\033[31mFailed\033[0m"
		continue
	fi
	ans=$(tail -1 traces/$trace)

	if [[ $(echo "$ans" | grep "no ladder exists") != "" ]]; then
		if [ "$ans" != "no ladder exists" ]; then
			echo -e "$trace......\033[31mFailed\033[0m"
			continue
		fi
	else
		res=${line#*Found ladder:}
		array=(${res//"->"/ })
		if [ $ans -eq $((${#array[@]} - 1)) ]; then
			for index in ${!array[@]}; do
				if [ $index -lt $((${#array[@]} - 1)) ]; then
					if compare ${array[index]} ${array[index + 1]}; then
						:
					else
						echo -e "$trace......\033[31mFailed\033[0m"
						continue 2
					fi
				fi
			done
		else
			echo -e "$trace......\033[31mFailed\033[0m"
			continue
		fi
	fi

	echo -e "$trace......\033[32mPassed\033[0m"
	score=$(($score + 5))
done

echo "Part A score: $score / 45"
