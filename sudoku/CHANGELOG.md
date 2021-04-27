# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/)

## [Unreleased]
- Full functionality for all Menu class member functions
- Updated for ver. 0.1.x

## [0.1.1] 2021-04-27
### Fixed
- Bug that caused the game to be unable to load at times (square.cpp)

### Changed
- When editing the grid, the command to exit is now -e (changed fronm 9 9 9) (menu.cpp)
- The <code>Square::init(int, string, string)</code> now requires another string parameter to be compatible with new functionality (square.hpp/cpp)
- 2nd line in settings.txt file now tells the filepath to the <code>SUDK::grd compGrid</code> variable when saving/loading

### Added
- <code>Menu::editGrid()</code> function now accepts more commands (menu.cpp)
- <code>Menu::getCommand(bool)</code> overload with boolean param - the boolean tells the function whether or not to print "Awaiting Command..." (menu.hpp/cpp)
- <code>Menu::showGridScreen()</code> function - displays the current grid (menu.hpp/cpp)
- <code>Square::getCompGrid()</code> and <code>Square::setCompGrid(SUDK::grd)</code> functions - mutators and accessors for the new <code>SUDK::grd compGrid</code> variable (square.hpp/cpp)
- #### Checking Functionality:
> - <code>SUDK::grd compGrid</code> square member variable - holds the completed (non-formatted) grid (square.hpp)
> - <code>Square::checkUserSquare</code> function - responsible for checking the grid that is currently being edited (<code>SUDK::grd grid</code>) against the completed and correct grid (<code>SUDK::grd compGrid</code>) (square.hpp/cpp)
- New file in sudoku/saves called "completegrid.sudk" which is the default save/load location for the <code>SUDK::grd compGrid</code> variable

### Updated
- Square class default constructor updated with support for new <code>SUDK::grd compGrid</code> variable (square.cpp)
- <code>Square::save()</code>, <code>Square::load()</code>, and <code>Square::init(int, string, string)</code> updated to support new <code>SUDK::grd compGrid</code> variable (square.cpp)
- <code>Square::create()</code> function will now also set the <code>SUDK::grd compGrid</code> variable at the end (square.cpp)
- <code>SUDK::settings</code> data type and ifstream >> operator overload for settings data type updated to support a filepath for the <code>SUDK::grd compGrid</code> variable (types.hpp/cpp)
- <code>Menu::doCommand(char)</code> updated to support new <code>Menu::editGrid()</code> commands (menu.cpp)


## [0.1.0] 2021-04-26 - ALPHA VERSION 1
### Changed
- <code>Menu::init(std::string, Square)</code> now requires a square as one of it's params (menu.hpp)
- Menu member display functions are no longer const member functions (menu.hpp)
- <code>Menu::getCommand()</code> is now a void function (menu.hpp)
- <code>Menu::doCommand()</code> param changed back to char (menu.hpp)
- <code>Menu::editGrid()</code> no longer requires a parameter (menu.hpp)
- <code>int main()</code> no longer takes arguments (this may change in the future) (driver.cpp)

### Fixed
- Bug caused by not passing by reference with overloaded ifstream >> operator and SUDK::settings data type (types.hpp/cpp)
- Bug that caused program to segfault when the new option was selected more than once in the main screen

### Added
- Partial/near full functionality for all currently existing Menu member functions (menu.cpp)
- Partially functioning early alpha binaries

## [0.0.4] 2021-04-26
### Changed
- Menu member functions no longer require an ostream parameter, all member functions will output via cout
- <code>Menu::getCommand()</code> now returns a string
- <code>Menu::doCommand(std::string)</code> now takes a string as it's parameter

## [0.0.3] 2021-04-20
### Fixed
- <code>Square::format()</code> function not correctly utilising the <code>int skill</code> member variable. (square.cpp)
- Missing "types.hpp" include in global headers file . (global.hpp)

### Changed
- <code>Menu::showMain(std::ostream&)</code>, <code>Menu::showSettings(std::ostream&)</code>, and <code>Menu::showCommands(std::ostream&)</code> are now const member functions. (menu.hpp)
- Documentation.md now up to date and has sections added for the Menu class and driver.cpp file (Documentation.md)

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

