#!/bin/zsh

export LD_LIBRARY_PATH=$PWD/SFML/lib
/bin/zsh
v=$(expr $SHLVL - 1)
echo "Shell lvl: $v"
