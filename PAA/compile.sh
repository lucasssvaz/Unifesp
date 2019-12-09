#!/bin/bash

NEWLINE=$'\n'

while [ "$1" != "" ]; do
    g++ -fno-asm -Dasm=error -lm -O2 -std=c++98 -o $1.out $1 2>&1

    echo "${NEWLINE}===============================${NEWLINE}$1 Done!${NEWLINE}===============================${NEWLINE}"

    shift

done