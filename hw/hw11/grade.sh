#!/bin/bash

rm -f hw11

if [ -f hw11.cpp ]; then
	clang++ hw11.cpp -std=c++17 -O2 -o hw11
else
	echo "hw11.cpp not found"
	exit 1
fi

score=0
for trace in $(ls traces); do
	res=($(gtimeout 1 ./hw11 <traces/$trace))
	ans=($(tail -1 traces/$trace))
	if [[ ${res[@]} == ${ans[@]} ]]; then
		score=$(($score + 10))
		echo -e "$trace......\033[32mPassed\033[0m"
	else
		echo "-------"
		echo "$trace"
		echo "Your answer: ${res[@]}"
		echo "Standard answer: ${ans[@]}"
		echo "-------"
		echo -e "$trace......\033[31mFailed\033[0m"
	fi
done

echo -e "\033[1;37mHomework 11: LRU and LFU Cache\033[0m score: $score / 80"
