#!/bin/bash

# Define variables
file="integer.txt"
lock="$file.lock"

# Check if file exists
#if [ ! -f $file ]
#then
  echo 0 > $file
#fi

# Check if there is another process using this file
while [ -f "$lock" ]
do
  :
done

echo $lock
touch $lock
while [ $(tail -1 $file) -le 100 ]
do
  echo $(( $(tail -1 $file) + 1 )) >> $file
#  sleep 0.3
done
rm $lock