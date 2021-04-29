//square.hpp

//Project designed and developed by Bryson Weeks and Henry Sartor for Baylor CSI 1430

#ifndef _SQUARE_H_
#define _SQUARE_H_

#include <types.hpp>

#include <vector>
#include <fstream>
#include <string>

class Square {
    private:
        //Class Variables
        SUDK::grd grid; //The main, user-editable grid
        SUDK::grd compGrid; //The complete, filled in grid that the main grid (grid) is being checked against
        int skill; //Determines how many values will be removed when the format() function is called
        SUDK::point p; //Dummy point used in construction
        std::string savePath; //The path to save/load the user editable function to/from
        std::string compPath; //The path to save/load the complete grid to/from

        //Loading/Saving Game
        SUDK::grd readSUDK(std::string); //Responsible for reading the SUDK file and handling errors

        //Checking Functions
        bool checkCell(char num, int row, int col, SUDK::grd grid) const; //Responsible for checking if a value (num) is unique in the given cell
        bool checkCol(char num, int col, SUDK::grd grid) const; //Responsible for checking if a value is unique in the given column
        bool checkRow(char num, int row, SUDK::grd grid) const; //Reponsible for checking if a value is unique in a given row
        bool check(char num, int row, int col, SUDK::grd grid) const; //Calls checkCell, checkRow, and checkCol, returns true if they are all true, returns false if any one is false

        //Generation Functions
        void replenish(std::vector<char>&); //Function responsible for "replensihing" the available nums vector

    public:
        //Constructors
        Square(); //Default constructor
        void init(int, std::string, std::string); //Not technically a constructor, but still necessary that this is called so that the Square can function correctly
        
        //Accessors
        SUDK::grd getGrid() const; //Returns the grid variable
        SUDK::grd getCompGrid() const; //Returns the compGrid variable

        //Mutators
        void setGrid(SUDK::grd); //Sets the grid variable
        void setCompGrid(SUDK::grd); //Sets the compGrid variable

        //Loading/Saving Game
        void load(); //Responsible for loading the two grids from the specified .sudk files at savePath and compPath, respectively
        void save(); //Responsible for saving the two grids to a .sudk file at the specified savePath and compPath, respectively

        //Display Functions
        void display() const; //Displays the grid variable with ANSI
        void display_noANSI() const; //Displays the grid variable without ANSI

        //Generation Functions
        void create(); //Responsible for generating both grids, for more information, see sudoku/extras/generation_algorithm.txt
        void format(); //Resplonsible for formatting (removing values) from the grid variable

        //Checking Functions
        void checkUserSquare(bool); //Checks grid against compGrid, and tells the user if they are correct or not

};


#endif