#!/bin/sh

FILESDIR=$1
SEARCHSTR=$2

should_exit=false

if [ -z "$FILESDIR" ]; then
	echo "Empty filesdir"
	should_exit=true
elif [ ! -d "$FILESDIR" ]; then
	echo "$FILESDIR is not a valid dir"
	should_exit=true
fi

if [ -z "$SEARCHSTR" ]; then
	echo "Empty searchstr"
	should_exit=true
fi

if [ "$should_exit" = true ]; then
	exit 1
fi

num_files=$(ls $FILESDIR | wc -l)
matching_lines=$(grep -r $SEARCHSTR $FILESDIR | wc -l)

echo "The number of files are $num_files and the number of matching lines are $matching_lines."