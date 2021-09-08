#!/bin/bash
gcc -o ex1 ex1.c
for i in 1 2 3 4 5 6 7 8 9 10
do
  ./ex1
done
rm ex1