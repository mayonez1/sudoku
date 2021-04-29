//menu.hpp

//Project designed and developed by Bryson Weeks and Henry Sartor for Baylor CSI 1430

#ifndef _MENU_H_
#define _MENU_H_

#include <square.hpp>
#include <types.hpp>

#include <string>


//Normal, reccomended, ANSI-Enabled Menu class
class Menu{
    private:
        //Class Variables
        enum screen {none, main, settings, grid, difficulty};
        screen currentScreen; //Tells the program which screen it's currently on
        std::string settingsFilePath; //Filepath to the settings file, by default, it is settings/settings.txt, however, this can be changed with the -f command line arg
        Square mainSquare; //The main square that is being interacted with by the user
        bool hints; //Determines if hints are toggled on/off
        SUDK::settings newSettings; //Data for the settings that the user can set

        //Interaction Functions
        void getCommand(); //Gets command
        void getCommand(bool); //Gets command, boolean tells the function whether or not it should display the "Awaiting Command..." message
        void doCommand(char); //Does the command that is gotten by getCommand
        void editGrid(); //Allows the user to input a row, column, and value to edit the grid in mainSquare

    public:
        //Constructors
        Menu();
        void init(std::string, Square); //Not techinically a constructor, but in the same vein so I put it here

        //Display Functions     //The reason these are not constant memmber functions is because they are also resposible for setting the currentScreen variable
        void showMain(); //Responsible for showing the main menu
        void showSettings(); //Shows the settings menu
        void showDifficulty(); //Shows the difficulty menu
        void showGridScreen(); //Shows the grid screen. Originally, this and editGrid() were one in the same, however, were eventually seperated to make the source code look a bit nicer
};

//Menu class for compatibility with systems that do not support ANSI escape codes
class Menu_noANSI{
    private:
        //Class Variables
        enum screen {none, main, settings, grid, difficulty};
        screen currentScreen; //Tells the program which screen it's currently on
        std::string settingsFilePath; //Filepath to the settings file, by default, it is settings/settings.txt, however, this can be changed with the -f command line arg
        Square mainSquare; //The main square that is being interacted with by the user
        bool hints; //Determines if hints are toggled on/off
        SUDK::settings newSettings; //Data for the settings that the user can set

        //Interaction Functions
        void getCommand(); //Gets command
        void getCommand(bool); //Gets command, boolean tells the function whether or not it should display the "Awaiting Command..." message
        void doCommand(char); //Does the command that is gotten by getCommand
        void editGrid(); //Allows the user to input a row, column, and value to edit the grid in mainSquare

    public:
        //Constructors
        Menu_noANSI();
        void init(std::string, Square); //Not techinically a constructor, but in the same vein so I put it here

        //Display Functions     //The reason these are not constant memmber functions is because they are also resposible for setting the currentScreen variable
        void showMain(); //Responsible for showing the main menu
        void showSettings(); //Shows the settings menu
        void showDifficulty(); //Shows the difficulty menu
        void showGridScreen(); //Shows the grid screen. Originally, this and editGrid() were one in the same, however, were eventually seperated to make the source code look a bit nicer
};



#endif