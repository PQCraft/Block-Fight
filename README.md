# Block-Fight
A SDL2 Demo game
If you are reading this, then I still aven't found a way to get this to compile with Windows using mingw.
The build.sh is a linux gcc compile script.
You will need to install SDL2 (`sudo apt install libsdl2-dev` on Ubuntu) and SDL2_ttf (`sudo apt install libsdl2-ttf-dev` on Ubuntu)
Run build.sh. If it compiles correctly, it will start the game.
If you want to build it using the terminal, use `gcc -o block-fight main.c -no-pie -I/usr/include -lSDL2main -lSDL2 -lSDL2_ttf`.
When running it from another directory, use run-block-fight.sh as it will get rid of the segmentation fault when Block Fight cannot find the GUI font.
To toggle fullscreen, press Alt+Enter.
