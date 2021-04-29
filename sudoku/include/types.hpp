//types.hpp

//Includes all types, operators, and exceptions for the sudoku project

//Project designed and developed by Bryson Weeks and Henry Sartor for Baylor CSI 1430

#ifndef _TYPES_H_
#define _TYPES_H_

#include <vector>
#include <fstream>
#include <string>


namespace SUDK{ //Namespace for all of the custom types, and most of the custom exceptions in the program

    //point data type
    typedef struct{ //Holds the value as character data, the row and column as int data, and if the point has been modified/if it can be modified as boolean data
        char val;
        bool canModify, modified;
        int row, col;
    } point;

    //grd data type
    typedef std::vector<std::vector<point>> grd; //2d vector of a point

    //Settings data type
    typedef struct{ //Holds the savePath (where the editable grid will be saved) as a string, the compPath (where the complete/filled inf grid will be saved) as a string
        std::string savePath; //and the difficulty/skill value that the user has set
        std::string completePath;
        int skill;
    } settings;

    //Initialisation functions for the data types
    void init_point(point&); //Initialises the point data type
    void init_grd(grd&); //Initialises the grd data type

    //Incorrect Marker type, refer to SUDK_Documentation for details
    struct bad_marker : public std::exception{
        const char* what() const throw(){
            return "Invalid Marker Error";
        }
    };

    //Incorrect or malformed block, means block did not start with '{' or end with '}'
    struct malformed_block : public std::exception{
        const char* what() const throw(){
            return "Malformed Block Error";
        }
    };

    //No #START found in file
    struct bad_start : public std::exception{
        const char* what() const throw(){
            return "Malformed or Missing #START statement";
        }
    };

    //Row or column out of range
    struct out_of_range : public std::exception{
        const char* what() const throw(){
            return "Row or Column out of range";
        }
    };

    //Boolean value for CANMOD or MODDED is invalid
    struct invalid_bool : public std::exception{
        const char* what() const throw(){
            return "Invalid boolean value";
        }
    };

    //Some error was thrown and readSUDK was not valid
    struct bad_read : public std::exception{
        const char* what() const throw(){
            return "SUDK File Could not be read correctly";
        }
    };

    //Incorrect filetype or location
    struct bad_file : public std::exception{
        const char* what() const throw(){
            return "Invalid filepath or incorrect file type";
        }
    };
}

//Overloaded operator responsible for making sense of data in .sudk files
std::ifstream& operator>>(std::ifstream& file, SUDK::grd& g);

//Responsible for getting data from settings.txt file
std::ifstream& operator>>(std::ifstream& file, SUDK::settings& set);

//Responsible for writing data to the settings.txt file
std::ofstream& operator<<(std::ofstream& file, SUDK::settings& set);

#endif