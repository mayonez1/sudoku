# sudoku

For full source documentation refer to sudoku/Documentation.md

For compilation instructions or makefile information refer to Part 0 of sudoku/Documentation.md

For information about the Square::create() function and algorithim refer to sudoku/extras/generation_algorithim.txt

For information about the .sudk file type refer to sudoku/extras/SUDK_Documentation.txt

For .sudk file examples refer to sudok-main/example.sudk (for a short 1-Block example) or sudoku/saves/newsave.sudk (for a full grid example)

All source code (.cpp files) can be found under sudoku/src

All header files/includes (.hpp files) can be found under sudoku/include

Default settings location is sudoku/settings/settings.txt

Default save file location is sudoku/saves/newsave.sudk (for the user-edited grid) and sudoku/saves/newcompletegrid.sudk (for the complete/answer grid)

Program uses ANSI escape codes for some output formatting, so, if your machine or terminal does not support ANSI, the output may look a bit off

A pre-compiled binary can be found under sudoku/bin, and can be run if you're on a UNIX-based machine (if you're on Windows you'll have to compile the source yourself)

Pre-compiled object files (.o and .d files) can be found under sudoku/obj

Program takes 1 optional argument, the settings file location can be changed if the new/non-default file location is specified by the user in the form of an argument, for example, typing <code>sudoku ./mypath/newsettings.txt</code> in your terminal would make the program use ./mypath/newsettings.txt as the filepath to the settings file instead of settings/settings.txt.

