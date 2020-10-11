#!/bin/bash
rm block-fight
gcc -o block-fight main.c -no-pie -O2 -I/usr/include -lSDL2main -lSDL2 -lSDL2_ttf
./block-fight &
