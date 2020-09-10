# Block-Fight
A SDL2 Demo game<br>
<br>
# Compiling:
!: If you are reading this, then I still aven't found a way to cross compile this for Windows.<br>
The build.sh is a linux gcc compile script.<br>
You will need to install SDL2 (`sudo apt install libsdl2-dev` on Ubuntu) and SDL2_ttf (`sudo apt install libsdl2-ttf-dev` on Ubuntu)<br>
Run build.sh. If it compiles correctly, it will start the game.<br>
If you want to build it using the terminal, use `gcc -o block-fight main.c -no-pie -I/usr/include -lSDL2main -lSDL2 -lSDL2_ttf`.<br>
<br>
# Running:
When running it from another directory, use run-block-fight.sh as it will get rid of the segmentation fault when Block Fight cannot find the GUI font.<br>
To toggle fullscreen, press Alt+Enter.<br>
<br>
# Controls:
WAD to move the yellow block (P1)<br>
Arrow Keys to move the purple block (P2)<br>
