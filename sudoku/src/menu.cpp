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
    hints = false;
}

void Menu::init(string s, Square sqr){
    settingsFilePath = s;
    mainSquare = sqr;
}

void Menu::getCommand(){
    char com;
    cout << '\n';
    cout << "\x1b[k";
    cout << "\x1b[5;2mAwaiting Command..." << "\x1b[0m";
    cin >> com;
    doCommand(com);
}

void Menu::getCommand(bool commandText){
    char com;
    if (commandText){
        cout << '\n';
        cout << "\x1b[k";
        cout << "\x1b[5;2mAwaiting Command..." << "\x1b[0m";
    }
    cin >> com;
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
                    cout << "\x1b[2J";
                    cout << "\x1b[H";
                    exit(0);
                    break;
                default:
                    cout << "Please try again and enter a valid command." << endl;
                    this->getCommand();
                    break;
            }
        case grid:
            switch(com){
                case 'e':
                    this->showMain();
                    break;
                case 'h':
                    hints = !hints;
                    this->showGridScreen();
                    break;
                case 'c':
                    showGridScreen();
                    mainSquare.checkUserSquare(hints);
                    break;
                default:
                    this->showGridScreen();
                    cout << "Please try again and enter a valid command." << endl;
                    this->getCommand();
                    break;
            }
    }
}

void Menu::showGridScreen(){
    cout << "\x1b[2J";
    cout << "\x1b[H";

    mainSquare.display();
    cout << "\n\n";
    cout << "To edit a point, type in the row, column, and value you wish to change the point to." << endl;
    cout << "For example, if you wanted to change the calue at row 1, column 3 to 6, you would type: 1 3 6" << endl;
    cout << endl;
    cout << "To Exit, simply type -e" << endl;
    cout << "To check your solved grid, type -c" << endl;
    cout << "To toggle hints, type -h" << endl;
    cout << "\n\n";

    if (hints){
        cout << "Hints: ON" << "\n\n";
    }
    else {
        cout << "Hints: OFF" << "\n\n";
    }
}

void Menu::editGrid(){
    grd g;
    char row, col, val;
    bool command = false;
    currentScreen = grid;
    g = mainSquare.getGrid();

    this->showGridScreen();
    
    do{
        cout << "\n\x1b[5;2mAwaiting Command..." << "\x1b[0m";
        cin >> row;

        if (row == '-'){
            getCommand(false);
            command = true;
        }
        else{
            cin >> col >> val;
            cout << row << " " << col << " " << val << endl;
            command = false;
        }

        if (!command){
            row -= 48;
            col -= 48;

            if (!g[row][col].canModify){
                cout << "Please enter the row and column of an editable value. Editable values are marked with the * character" << endl;
            }

            else {
                g[row][col].val = val;
                g[row][col].modified = true;
                mainSquare.setGrid(g);
                mainSquare.save();
                showGridScreen();
            }
        }
    } while (currentScreen == grid);
}

void Menu::showMain(){
    currentScreen = main;
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