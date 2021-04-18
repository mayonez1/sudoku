//types.hpp

//Includes all types, operators, and exceptions for the sudoku project

#ifndef _TYPES_H_
#define _TYPES_H_

#include <vector>
#include <fstream>


namespace SUDK{

    typedef struct Point{
        char val;
        bool canModify, modified;
        int row, col;
    } point;

    typedef std::vector<std::vector<point>> grd;

    void init_point(point&);
    void init_grd(grd&);

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
            return "Invalid filepath or incorrect file type, please ensure the existence of the .SUDK file";
        }
    };
}


std::ifstream& operator>>(std::ifstream& file, SUDK::grd& g);

#endif