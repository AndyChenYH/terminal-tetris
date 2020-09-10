# terminal-tetris
terminal tetris for cool hackermen like myself


controls:
',' to move left
'.' to accelerate down
'/' to right
'x' to rotate clockwise
'z' to rotate counterclockwise
spacebar to hard drop
'p' to pause or unpause

Uses the NES rotation system
https://strategywiki.org/wiki/Tetris/Rotation_systems

# how to run:

make sure you have ncurses installed

compile with:

g++ -std=c++17 -lncurses tetris.cpp
