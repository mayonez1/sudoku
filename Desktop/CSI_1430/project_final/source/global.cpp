//global_functions.cpp

#include "global.hpp"

#include <iostream>

const char* getOS(){
    const char* OS;

    #ifdef __linux__
    OS = "LINUX";
    #elif __APPLE__ || __MACH__
    OS = "MACOSX";
    #elif _WIN32
    OS = "WIN32";
    #elif _WIN64
    OS = "WIN64"
    #elif __unix || __unix__
    OS = "UNIX"
    #else
    OS = "OTHER"
    #endif

    return OS;
}

void randomNum(unsigned int &num){
    srand(time(0));
    num = rand();
}

void randomNum(unsigned int &num, unsigned int amount){
    srand(time(0));
    num = (rand() % amount);
}

void randomNum(unsigned int &num, unsigned int amount, unsigned int seed){
    srand(seed);
    num = (rand() % amount);
}

void randomNum(unsigned int &num, unsigned long amount, unsigned int seed){
    unsigned int am = (unsigned int) amount;
    srand(seed);
    num = (rand() % am);
}

