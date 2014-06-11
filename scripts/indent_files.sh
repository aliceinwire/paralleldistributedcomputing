#!/bin/bash

for sourcefile in `find . -name "*.c" -or -name "*.h"`
do
	echo "indenting $sourcefile"
	indent -kr -i8 $sourcefile
done
echo "indentation completed for all source files"
