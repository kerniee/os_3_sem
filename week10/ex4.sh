#!/bin/bash

cd tmp
[ ! -e file1 ] || touch file1
[ ! -e file2 ] || touch file2
[ ! -e link1 ] || ln file1 link1
cd ..

gcc -o ex4 ex4.c
./ex4 > ex4.txt