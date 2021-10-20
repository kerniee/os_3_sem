#!/bin/bash

declare -a FILES=(_ex3.txt)

# remove files
for file in "${FILES[@]}"
do
  [ ! -e "${file}" ] || rm "${file}"
done
[ ! -e ex1.txt ] || rm ex1.txt

echo Matvey > _ex3.txt
chmod a-x _ex3.txt
ls -l _ex3.txt > ex3.txt
chmod uo+rwx _ex3.txt
ls -l _ex3.txt >> ex3.txt
chmod g=o _ex3.txt
ls -l _ex3.txt >> ex3.txt

echo "660 means
110(read and write) rights to owner,
110(read and write) rights to group,
000(no) rights to others " >> ex3.txt
echo "775 means
111(read, write and execute) rights to owner,
111(read, write and execute) rights to group,
101(read and execute) rights to others " >> ex3.txt
echo "777 means
111(read, write and execute) rights to owner,
111(read, write and execute) rights to group,
111(read, write and execute) rights to others " >> ex3.txt
