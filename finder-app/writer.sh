#!/bin/bash

FILEPATH=$1
WRITESTR=$2

should_exit=false

if [ -z "$FILEPATH" ]; then
	echo "Empty filepath"
	should_exit=true
fi

if [ -z "$WRITESTR" ]; then
	echo "Empty writestr"
	should_exit=true
fi

if [ "$should_exit" = true ]; then
	exit 1
fi

mkdir -p $(dirname $FILEPATH)
touch $FILEPATH
echo "$WRITESTR" >> $FILEPATH