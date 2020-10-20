#!/bin/bash
rm block-fight.exe
gcc -o block-fight main.c -no-pie -O2 -lSDL2main -lSDL2 -lSDL2_ttf -mwindows
