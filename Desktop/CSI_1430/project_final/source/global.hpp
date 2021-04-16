//global.hpp

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <exception>

namespace GLOBAL{

    //OS and Preprocessor Functions
    const char* getOS();

    //Random Functions
    void randomNum(unsigned int&);
    void randomNum(unsigned int&, unsigned int);
    void randomNum(unsigned int&, unsigned long, unsigned int);
    void _seed(unsigned int&);
    void _seed(unsigned int&, unsigned int);

    //Global Exceptions
    struct mod_by_0 : public std::exception{
        const char* what() const throw(){
            return "Attempted to modulus by zero";
        }
    };

}

#endif