# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/)

## [Unreleased]

## [0.0.2] - 2021-04-19
### Added
- New settings type (types.cpp/hpp)
- ifstream extraction operator utilizing the new settings type (types.cpp/hpp)
- Global fetchSettings function with new settings type as the return (global.cpp/hpp)
- Arguments to the driver.cpp main function (formerly main.cpp)
- Square init function that takes an int as a parameter and initialises the square, using the int as the value for difficulty
- New (Unfinished) Menu class along with menu.hpp and menu.cpp files
> #### New Menu Class Functions:
> - <code>char Menu::getCommand(std::ostream&)</code> - Prompts the user to input a command via ostream takes in the command with cin and returns it in the form of a character
> - <code>void Menu::doCommand(char)</code> - Executes the command that was gotten with getCommand according to which screen the user is on
> - <code>void Menu::init(std::string)</code> - Initialises the menu class by setting the settingsFilePath variable to the inputted parameter
> - <code>void Menu::showMain(std::ostream&)</code> - Prints the main menu to the ostream
> - <code>void Menu::showSettings(std::ostream&)</code> - Prints the settings menu to the ostream
> - <code>void Menu::showCommands(std::ostream&)</code> - Prints the command/help menu to the ostream
> - <code>void Menu::editGrid(SUDK::grd&)</code> - Allows the user to edit the grid passed in using basic keyboard commands

### Changed
- The entire driver.cpp (formerly main.cpp) file - the iteration before was just used for testing, and this one is a WIP of what will become the final driver file
- <code>int difficulty</code> in Square class changed to <code>int skill</code> to be more consistent with the language of the rest of the project
- <code>void Square::load()</code> and <code>void Square::save()</code> are now public functions

### Removed
- The parameter versions of Square::load(), Square::save(), and Square::format (<code>void Square::load(std::string), void Square::save(std::string), void Square::format(int)</code>) were removed due to redundancy
- <code>void Square::testRun()</code> was removed due to no longer being needed
- <code>bool loadGame</code> in the Square class was removed due to redundancy

### Other Notes
- Documentation will be updated within a day or two
- A working version of the menu class should be uploaded sometime this week (hopefully)
- It's important to note that the source code does not work at this stage, however, the compiled objects/binaries that I've included are still working, and are compiled versions of the previous 0.0.1 version of the code


## [0.0.1] - 2021-04-19
### Added
- Empty menu class and header files (menu.cpp and menu.hpp)
- Compiled Binaries and Objects (can be found under sudoku/bin and sudoku/obj, respectively)

### Changed
- Overall file structure (source files can now be found under sudoku/src, headers under sudoku/include)
- make.mak is now Makefile.mk, it should now scale better with the project, and shouldn't require as much manual adjustment as new files are added to the project

## [0.0.1] - 2021-04-18
### Added
- This CHAGELOG which should hopefully document any changes made to the project
- documentation.txt, in which I've documented and explained the source to the best of my ability

### Changed
- Updated the implementation of the GLOBAL::mod_by_0 exception so that negative numbers are caught as well
- Updated the throw message of the GLOBAL::mod_by_0 exception to say "Attempted to modulus by zero or a negative"
- Restructured git directories

