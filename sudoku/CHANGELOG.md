# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/)

## [Unreleased]

- Menu class
- User Interaction (part of Menu class)

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

