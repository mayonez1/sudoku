//menu.hpp

#ifndef _MENU_H_
#define _MENU_H_

#include <square.hpp>
#include <types.hpp>

#include <string>

class Menu{
    private:
        //Class Variables
        enum screen {none, main, settings, grid, difficulty};
        screen currentScreen;
        std::string settingsFilePath;
        Square mainSquare;
        bool hints;
        SUDK::settings newSettings;

        //Interaction Functions
        void getCommand();
        void getCommand(bool);
        void doCommand(char);
        void editGrid();

    public:
        //Constructors
        Menu();
        void init(std::string, Square);

        //Display Functions
        void showMain();
        void showSettings();
        void showDifficulty();
        void showGridScreen();
};

class Menu_noANSI{
    private:
        //Class Variables
        enum screen {none, main, settings, grid, difficulty};
        screen currentScreen;
        std::string settingsFilePath;
        Square mainSquare;
        bool hints;
        SUDK::settings newSettings;

        //Interaction Functions
        void getCommand();
        void getCommand(bool);
        void doCommand(char);
        void editGrid();

    public:
        //Constructors
        Menu_noANSI();
        void init(std::string, Square);

        //Display Functions
        void showMain();
        void showSettings();
        void showDifficulty();
        void showGridScreen();
};



#endif