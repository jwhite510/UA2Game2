#!/bin/bash

# log_output=$(more Saved/Logs/UA2.log)

# read the file from bottom to top
tac Saved/Logs/UA2.log | while read -r line
do
	echo $line | sed -e 's/\\/\//g' | sed -e 's/C:\//\/mnt\/c\//gI' | sed -e 's/users/Users/g' | sed -e 's/ua23/UA23/g' | sed -e 's/ua2/UA2/g' | sed -e 's/source/Source/g'

	# echo $line

	# if line contains an error
	# if [[ $line == *""* ]];
	# if line is the beginning
	if [[ $line == *"Starting HotReload"* ]];
	then
		break
	fi

done


