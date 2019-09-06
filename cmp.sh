#!/bin/zsh

av=("$@")
arg=${av[1]}

diff =(python3 fact.py "$arg") =(./a.out "$arg")