//global_functions.cpp

//Project designed and developed by Bryson Weeks and Henry Sartor for Baylor CSI 1430

#include <global.hpp>
#include <types.hpp>

#include <iostream>
#include <string>
#include <fstream>

const char* GLOBAL::getOS(){
    const char* OS;

    #ifdef __linux__
    OS = "LINUX";
    #elif __APPLE__ || __MACH__
    OS = "MACOSX";
    #elif __CYGWIN__
    OS = "CYGWIN";
    #elif _WIN32
    OS = "WIN32";
    #elif _WIN64
    OS = "WIN64";
    #elif _WIN16
    OS = "WIN16";
    #elif __WIN32__ || __TOS_WIN__ || __WINDOWS__ || _WIN32_WCE
    OS = "WIN_OTHER";
    #elif MSDOS || __MSDOS__ || _MSDOS || __DOS__
    OS = "DOS";
    #elif __FreeBSD__ || __NetBSD__ || __OpenBSD__ || __bsdi__ || __DragonFly__
    OS = "BSD";
    #elif __unix || __unix__
    OS = "UNIX";
    #else
    OS = "OTHER";
    #endif

    return OS;
}


void GLOBAL::randomNum(unsigned int &num, unsigned int amount){
    if (amount <= 0){
        throw GLOBAL::mod_by_0();
    }
    else{
        srand(time(0));
        num = (rand() % amount);
    }
}

void GLOBAL::randomNum(unsigned int &num, unsigned long amount, unsigned int seed){
    unsigned int am = (unsigned int) amount;
    if (am <= 0){
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

void GLOBAL::writeSettings(std::string filepath, SUDK::settings set){
    std::ofstream of;
    of.open(filepath);
    if (!of.is_open()){
        throw SUDK::bad_file();
    }
    else {
        of << set;
    }
    of.close();
}

SUDK::settings GLOBAL::fetchSettings(std::string filepath){
    SUDK::settings ret;
    std::ifstream f;
    f.open(filepath);

    if(!f.is_open()){
        throw SUDK::bad_file();
    }
    else{
        f >> ret;
    }

    f.close();

    return ret;
}

