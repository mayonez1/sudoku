//global_functions.cpp

#include "global.hpp"

#include <iostream>

const char* GLOBAL::getOS(){
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

void GLOBAL::randomNum(unsigned int &num){
    srand(time(0));
    num = rand();
}

void GLOBAL::randomNum(unsigned int &num, unsigned int amount){
    if (amount == 0){
        throw GLOBAL::mod_by_0();
    }
    else{
        srand(time(0));
        num = (rand() % amount);
    }
}

void GLOBAL::randomNum(unsigned int &num, unsigned long amount, unsigned int seed){
    unsigned int am = (unsigned int) amount;
    if (am == 0){
        throw GLOBAL::mod_by_0();
    }
    else{
        srand(seed);
        num = (rand() % am);
    }
}

void GLOBAL::_seed(unsigned int& num){
    srand(time(0));
    num = rand();
}

void GLOBAL::_seed(unsigned int& num, unsigned int seed){
    srand(seed);
    num = rand();
}

