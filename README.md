#### Project designed and developed by Bryson Weeks and Henry Sartor for Baylor CSI 1430

# sudoku

### References texts and the file structure

For full source documentation refer to sudoku/Documentation.md

For compilation instructions or makefile information refer to Part 0 of sudoku/Documentation.md

For information about the Square::create() function and algorithim refer to sudoku/extras/generation_algorithim.txt

For information about the .sudk file type refer to sudoku/extras/SUDK_Documentation.txt

For .sudk file examples refer to sudok-main/example.sudk (for a short 1-Block example) or sudoku/saves/newsave.sudk (for a full grid example)

All source code (.cpp files) can be found under sudoku/src

All header files/includes (.hpp files) can be found under sudoku/include

Default settings location is sudoku/settings/settings.txt

Default save file location is sudoku/saves/newsave.sudk (for the user-edited grid) and sudoku/saves/newcompletegrid.sudk (for the complete/answer grid)

A pre-compiled binary can be found under sudoku/bin, and can be run if you're on a UNIX-based machine (if you're on Windows you'll have to compile the source yourself)

Pre-compiled object files (.o and .d files) can be found under sudoku/obj

### Arguments

Program takes two arguments, by typing -f and then the path to a different settings file, you can run the program with a non-default settings file. For example:
<code>sudoku -f ./newsettingspath/settings.txt</code> (where sudoku is the name or filepath of your binary). Additionally, you can use the argument <code>-a 0/1</code> to turn ANSI escape codes on or off. For example: <code>sudoku -a 0</code> (run program without ANSI escape codes) or <code>sudoku -a 1</code> (run program with ANSI escape codes). By default, the setting is based on your OS, so if you are running any form of Windows, DOS, or any OS that the compiler does not recognize as Linux, MACOSX, BSD, or some derivative of UNIX, ANSI will be disabled by default (The one exception to this is cygwin, if you are using cygwin, ANSI is enabled by default). Do note that, the program can only detect your OS if you've compiled it on your own computer, if you are using the precompiled binary, ANSI is enabled by default.

