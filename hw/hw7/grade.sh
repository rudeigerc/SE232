#!/bin/bash

rm -f RedundantParentheses

if [ -f RedundantParentheses.cpp ]; then
	clang++ RedundantParentheses.cpp --std=c++11 -O2 -o RedundantParentheses
else
	echo "RedundantParentheses.cpp not found"
	exit 1
fi

score=0
for trace in $(ls traces); do
	res=$(gtimeout 2 ./RedundantParentheses <traces/$trace | head -1)
	ans=$(tail -1 traces/$trace)
	if [[ $res == $ans ]]; then
		score=$(($score + 10))
		echo -e "$trace......\033[32mPassed\033[0m"
	else
		echo "-------"
		echo "$trace: $(head -1 traces/$trace)"
		echo "Your answer: $res"
		echo "Standard answer: $ans"
		echo "-------"
		echo -e "$trace......\033[31mFailed\033[0m"
	fi
done

echo "Homework 7: Redundant Parentheses score: $score / 90"
