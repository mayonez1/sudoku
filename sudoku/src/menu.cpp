//menu.cpp
#include <menu.hpp>
#include <types.hpp>
#include <square.hpp>
#include <global.hpp>

#include <string>
#include <iostream>

using namespace std;
using namespace SUDK;

Menu::Menu(){
    currentScreen = none;
}

void Menu::init(string s, Square sqr){
    settingsFilePath = s;
    mainSquare = sqr;
}

void Menu::getCommand(){
    char com;
    cout << "\n\x1b[5;2mAwaiting Command..." << "\x1b[0m";
    cin >> com;
    cout << com << endl;
    doCommand(com);
}

void Menu::doCommand(char com){
    grd empty;
    init_grd(empty);
    switch (currentScreen){
        case main:
            switch (com){
                case '1':
                    mainSquare.setGrid(empty);
                    mainSquare.create();
                    mainSquare.format();
                    this->editGrid();
                    break;
                case '2':
                    mainSquare.load();
                    this->editGrid();
                    break;
                case '3':
                    this->showSettings();
                    break;
                case '4':
                    this->showCommands();
                    break;
                case '5':
                    exit(0);
                    break;
                default:
                    cout << "Please try again and enter a valid command." << endl;
                    this->getCommand();
                    break;
            }
    }
}

void Menu::editGrid(){
    grd g;
    char row, col, val;
    bool exit = false;
    currentScreen = grid;
    g = mainSquare.getGrid();

    cout << "\x1b[2J";
    cout << "\x1b[H";

    mainSquare.display();
    cout << "\n\n";
    cout << "To edit a point, type in the row, column, and value you wish to change the point to." << endl;
    cout << "For example, if you wanted to change the calue at row 1, column 3 to 6, you would type: 1 3 6" << endl;
    cout << "To Exit, simply type 9 9 9" << endl;
    
    do{
        cout << "\n\x1b[5;2mAwaiting Command..." << "\x1b[0m";
        cin >> row >> col >> val;
        cout << row << " " << col << " " << val << endl;

        if (row == '9' || col == '9'){
            exit = true;
        }

        if (!exit){
            row -= 48;
            col -= 48;

            if (!g[row][col].canModify){
                cout << "Please enter the row and column of an editable value. Editable values are marked with the * character" << endl;
            }

            else {
                g[row][col].val = val;
                g[row][col].modified = true;
                cout << "\x1b[2J";
                cout << "\x1b[H";
                mainSquare.setGrid(g);
                mainSquare.display();
            }
        }

    } while (!exit);

    mainSquare.save();
    this->showMain();
}

void Menu::showMain(){
    cout << "\x1b[2J";
    cout << "\x1b[H";
    cout << "\x1b[1;36m                                                                              " << "\x1b[0m" << endl;
    cout << "\x1b[1;36m     *******                       **                 *                       " << "\x1b[0m" << endl;
    cout << "\x1b[1;36m    *       ***                      **              **                       " << "\x1b[0m" << endl;
    cout << "\x1b[1;36m   *         **                      **              **                       " << "\x1b[0m" << endl;
    cout << "\x1b[1;36m   **        *                       **              **                       " << "\x1b[0m" << endl;
    cout << "\x1b[1;36m    ***          **   ****           **      ****    **         **   ****     " << "\x1b[0m" << endl;
    cout << "\x1b[1;36m   ** ***         **    ***  *   *** **     * ***  * **  ***     **    ***  * " << "\x1b[0m" << endl;
    cout << "\x1b[1;36m    *** ***       **     ****   *********  *   ****  ** * ***    **     ****  " << "\x1b[0m" << endl;
    cout << "\x1b[1;36m      *** ***     **      **   **   ****  **    **   ***   *     **      **   " << "\x1b[0m" << endl;
    cout << "\x1b[1;36m        *** ***   **      **   **    **   **    **   **   *      **      **   " << "\x1b[0m" << endl;
    cout << "\x1b[1;36m          ** ***  **      **   **    **   **    **   **  *       **      **   " << "\x1b[0m" << endl;
    cout << "\x1b[1;36m           ** **  **      **   **    **   **    **   ** **       **      **   " << "\x1b[0m" << endl;
    cout << "\x1b[1;36m            * *   **      **   **    **   **    **   ******      **      **   " << "\x1b[0m" << endl;
    cout << "\x1b[1;36m  ***        *     ******* **  **    **    ******    **  ***      ******* **  " << "\x1b[0m" << endl;
    cout << "\x1b[1;36m *  *********       *****   **  *****       ****     **   *** *    *****   ** " << "\x1b[0m" << endl;
    cout << "\x1b[1;36m*     *****                      ***                  **   ***                " << "\x1b[0m" << endl;
    cout << "\x1b[1;36m*                                                                             " << "\x1b[0m" << endl;
    cout << "\x1b[1;36m **                                                                           " << "\x1b[0m" << endl;
    cout << endl;
    cout << "\x1b[3mA Game By Bryson Weeks and Henry Sartor" << "\x1b[0m" << endl;
    cout << endl;
    cout << endl;
    cout << "1. New\n2. Load\n3. Settings\n4. Help\n5. Exit" << endl;
    currentScreen = main;
    getCommand();
}

void Menu::showCommands(){
    cout << "\x1b[2J";
    cout << "\x1b[H";
    cout << "sample text" << endl;
    this->getCommand();
}

void Menu::showSettings(){
    cout << "\x1b[2J";
    cout << "\x1b[H";
    cout << "sample text" << endl;
    this->getCommand();
}