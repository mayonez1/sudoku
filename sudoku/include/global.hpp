//global.hpp

//Project designed and developed by Bryson Weeks and Henry Sartor for Baylor CSI 1430

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <types.hpp>

#include <exception>
#include <string>

namespace GLOBAL{

    //OS and Preprocessor Functions
    const char* getOS(); //Reports the User's OS, note that the OS is actually determined at compile time, not runtime

    //Random Functions
    void randomNum(unsigned int&, unsigned int); //Makes the first param into a random number from 0->(1 - 2nd param)
    void randomNum(unsigned int&, unsigned long, unsigned int); //Same as other randomNum function except it takes a seed as it's third param
    void _seed(unsigned int&); //Responsible for making a number into a random, usable seed
    void _seed(unsigned int&, unsigned int); //Same as other _seed function, except it takes a seed as it's second param

    //Fetching functions
    SUDK::settings fetchSettings(std::string); //Fetches the settings from the settings.txt file and returns it as an SUDK::settings data type

    //Writing functions
    void writeSettings(std::string, SUDK::settings); //Writes an SUDK::settings file to a file (presumabley the settings.txt file) at the first std::string param

    //Global Exceptions
    struct mod_by_0 : public std::exception{ //Throws if the program attempts to modulus by 0 in a randomNum call
        const char* what() const throw(){
            return "Attempted to modulus by zero or a negative";
        }
    };

}

#endif