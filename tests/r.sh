#!/bin/bash

exec 2> error.txt

source color.sh

CC=gcc-13
LIBS="../Utils/utils.c"
CFLAGS="-Wall -Wextra -pedantic -std=c2x -Wshadow -Wpointer-arith -Wcast-qual"

compile() {
  if $CC $CFLAGS "t$1.c" $LIBS -o a.out 2>error.txt; then
    color_print $GREEN "COMPILED"
    return 0  
  else
    color_print $RED "COMPILATION ERROR"
    return 1  
  fi
}

run() {
  if ./a.out 2>error.txt; then
    color_print $GREEN "\nEXECUTED SUCCESSFULLY"
    return 0
  else
    color_print $RED "\nRUNTIME ERROR"
    return 1
  fi
}


if [ -z "$1" ]; then
  echo "Usage: $0 <filename>"
  exit 1
fi

color_print $GREEN "Compiling $1.c..."

if compile "$1"; then
  if [ -f "./a.out" ]; then
    color_print $GREEN "executing  $1..."
    run
    rm -f ./a.out
  else
    color_print $RED "Error: Compiled executable 'a.out' not found."
  fi
  fi

