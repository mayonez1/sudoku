//menu.hpp

#ifndef _MENU_H_
#define _MENU_H_

#include <square.hpp>
#include <types.hpp>

#include <string>

class Menu{
    private:
        //Class Variables
        enum screen {none, main, settings, grid, commands};
        screen currentScreen;
        std::string settingsFilePath;
        Square mainSquare;
        bool hints = false;

        //Interaction Functions
        void getCommand();
        void getCommand(bool);
        void doCommand(char);

    public:
        //Constructors
        Menu();
        void init(std::string, Square);

        //Display Functions
        void showMain();
        void showSettings();
        void showCommands();
        void showGridScreen();

        //Interaction functions
        void editGrid();
};



#endif