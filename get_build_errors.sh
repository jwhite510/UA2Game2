#!/bin/bash

# log_output=$(more Saved/Logs/UA2.log)

# read the file from bottom to top
tac Saved/Logs/UA2.log | while read -r line
do
	echo $line

	# if line contains an error
	if [[ $line == *""* ]];



	# if line is the beginning
	if [[ $line == *"Starting HotReload"* ]];
	then
		break
	fi

done


