#!/bin/bash
gcc -o ex2 ex2.c
./ex2 & pstree
for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
do
  sleep 2
  pstree
done
rm ex2