//menu.hpp

#ifndef _MENU_H_
#define _MENU_H_

#include <square.hpp>
#include <types.hpp>

#include <string>
#include <iostream>

class Menu{
    private:
        //Class Variables
        enum screen {none, main, settings, grid, commands};
        screen currentScreen;
        std::string settingsFilePath;

        //Interaction Functions
        char getCommand(std::ostream&);
        void doCommand(char);

    public:
        //Constructors
        Menu();
        void init(std::string);

        //Display Functions
        void showMain(std::ostream&);
        void showSettings(std::ostream&);
        void showCommands(std::ostream&);
        
        //Interaction functions
        void editGrid(SUDK::grd&);
};



#endif