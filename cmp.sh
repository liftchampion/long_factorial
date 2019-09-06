#!/bin/zsh

av=("$@")
arg=${av[1]}
for (( i = 0; i <= $arg; i++ ))
do
  echo $i
  diff =(python3 fact.py "$i") =(./a.out "$i")
done