//menu.cpp
#include <menu.hpp>
#include <types.hpp>
#include <square.hpp>
#include <global.hpp>

#include <string>
#include <iostream>
#include <fstream>

using namespace std;
using namespace SUDK;

Menu::Menu(){
    currentScreen = none;
    hints = false;
}

void Menu::init(string s, Square sqr){
    settingsFilePath = s;
    mainSquare = sqr;
    newSettings = GLOBAL::fetchSettings(settingsFilePath);
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
    string fileloc;
    srand(time(0));
    int sk;
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
                    this->showDifficulty();
                    break;
                case 'e':
                    cout << "\x1b[2J";
                    cout << "\x1b[H";
                    exit(0);
                    break;
                default:
                    this->showMain();
                    cout << "Please try again and enter a valid command." << endl;
                    break;
            }
            break;
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
                    break;
            }
            break;
        case settings:
            switch (com){
                case 'e':
                    this->showMain();
                    break;
                case '1':
                    cout << "\x1b[2J";
                    cout << "\x1b[H";
                    cout << "Enter the location of the file you would like to use as a save file for the editable grid (No Spaces): " << endl;
                    cout << "\n\x1b[5;2mAwaiting Command..." << "\x1b[0m";
                    cin >> fileloc;
                    newSettings.savePath = fileloc;
                    GLOBAL::writeSettings(settingsFilePath, newSettings);
                    mainSquare.init(newSettings.skill, newSettings.savePath, newSettings.completePath);
                    this->showSettings();
                    break;
                case '2':
                    cout << "\x1b[2J";
                    cout << "\x1b[H";
                    cout << "Enter the location of the file you would like to use as a save file for the complete grid (No Spaces): " << endl;
                    cout << "\n\x1b[5;2mAwaiting Command..." << "\x1b[0m";
                    cin >> fileloc;
                    newSettings.completePath = fileloc;
                    GLOBAL::writeSettings(settingsFilePath, newSettings);
                    mainSquare.init(newSettings.skill, newSettings.savePath, newSettings.completePath);
                    this->showSettings();
                    break;
                default:
                    this->showSettings();
                    cout << "Please try again and enter a valid command." << endl;
                    break;
            }
            break;
        case difficulty:
            switch (com){
                case 'e':
                    this->showMain();
                    break;
                case '1':
                    sk = (rand() % 12) + 2;
                    newSettings.skill = sk;
                    GLOBAL::writeSettings(settingsFilePath, newSettings);
                    mainSquare.init(newSettings.skill, newSettings.savePath, newSettings.completePath);
                    this->showMain();
                    break;
                case '2':
                    sk = (rand() % 12) + 12;
                    newSettings.skill = sk;
                    GLOBAL::writeSettings(settingsFilePath, newSettings);
                    mainSquare.init(newSettings.skill, newSettings.savePath, newSettings.completePath);
                    this->showMain();
                    break;
                case '3':
                    sk = (rand() % 12) + 24;
                    newSettings.skill = sk;
                    GLOBAL::writeSettings(settingsFilePath, newSettings);
                    mainSquare.init(newSettings.skill, newSettings.savePath, newSettings.completePath);
                    this->showMain();
                    break;
                case '4':
                    sk = (rand() % 12) + 36;
                    newSettings.skill = sk;
                    GLOBAL::writeSettings(settingsFilePath, newSettings);
                    mainSquare.init(newSettings.skill, newSettings.savePath, newSettings.completePath);
                    this->showMain();
                    break;
                case '5':
                    sk = (rand() % 12) + 48;
                    newSettings.skill = sk;
                    GLOBAL::writeSettings(settingsFilePath, newSettings);
                    mainSquare.init(newSettings.skill, newSettings.savePath, newSettings.completePath);
                    this->showMain();
                    break;
                default:
                    this->showMain();
                    cout << "Please try again and enter a valid command." << endl;
                    break;
            }
            break;
    default:
        this->showMain();
        break;
    }
}

void Menu::showGridScreen(){
    cout << "\x1b[2J";
    cout << "\x1b[H";

    cout << "\x1b[1;4;36mGrid Editor\n\n" << "\x1b[0m";
    mainSquare.display();
    cout << "\n\n";
    cout << "To edit a point, type in the row, column, and value you wish to change the point to." << endl;
    cout << "For example, if you wanted to change the value at row 0, column 3 to 6, you would type: 0 3 6" << endl;
    cout << "Additionally, note that you are only able to edit spaces marked with a * character." << endl;
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
    bool error = false;
    currentScreen = grid;
    g = mainSquare.getGrid();

    this->showGridScreen();
    
    do{
        error = false;
        cout << "\n\x1b[5;2mAwaiting Command..." << "\x1b[0m";
        cin >> row;

        if (row == '-'){
            getCommand(false);
            command = true;
        }

        else if (row >= 48 && row <= 56){
            cin >> col;
            if (col >= 48 && col <= 56){
                cin >> val;
                command = false;
            }
            else {
                command = true;
                error = true;
            }
        }

        else {
            command = true;
            error = true;
        }

        if (error){
            cout << "Please enter a valid command, or proper combination of row, column, and value" << endl;
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
    char cmd;
    int currentSk = (newSettings.skill / 12);
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
    cout << "1. New\n2. Load\n3. Settings\n4. Change Difficulty" << endl;
    cout << "\nCurrent Difficulty Level: ";

    switch (currentSk){
        case 0:
            cout << "Baby" << endl;
            break;
        case 1:
            cout << "Easy" << endl;
            break;
        case 2:
            cout << "Medium" << endl;
            break;
        case 3:
            cout << "Hard" << endl;
            break;
        case 4:
            cout << "Nightmare" << endl;
            break;
        case 5:
            cout << "Nightmare" << endl;
            break;
        default:
            cout << "None???" << endl;
            break;
    }

    cout << "\nType -e to quit the program" << endl;
    cout << "\nIf this screen looks strange or broken, type -e to exit, and re-run the program using the argument \'-a 0\'." << endl;
    cout << "\nANSI = ON" << endl;
    cout << "\n\x1b[5;2mAwaiting Command..." << "\x1b[0m";
    cin >> cmd;
    if (cmd == '-'){
        getCommand(false);
    }
    else {
        doCommand(cmd);
    }
    
}

void Menu::showDifficulty(){
    currentScreen = difficulty;
    char cmd;
    bool cont = true;
    cout << "\x1b[2J";
    cout << "\x1b[H";
    cout << "\x1b[1;4;36mChange Difficulty\n\n" << "\x1b[0m";
    cout << "1. I'm too young to die" << endl;
    cout << "2. Hey, not too rough" << endl;
    cout << "3. Hurt me plenty" << endl;
    cout << "4. Ultra Violence" << endl;
    cout << "5. Nightmare!" << endl;
    cout << "\nType -e to exit" << endl;

    do{
        cout << "\n\x1b[5;2mAwaiting Command..." << "\x1b[0m";
        cin >> cmd;
        
        switch (cmd){
            case '-':
                getCommand(false);
                cont = false;
                break;
            case '1':
                doCommand(cmd);
                cont = false;
                break;
            case '2':
                doCommand(cmd);
                cont = false;
                break;
            case '3':
                doCommand(cmd);
                cont = false;
                break;
            case '4':
                doCommand(cmd);
                cont = false;
                break;
            case '5':
                doCommand(cmd);
                cont = false;
                break;
            default:
                cout << "\nPlease enter a valid command." << endl;
                break; 
        }
    } while(cont);

}

void Menu::showSettings(){
    currentScreen = settings;
    char cmd;
    bool cont = true;
    cout << "\x1b[2J";
    cout << "\x1b[H";
    cout << "\x1b[1;4;36mSettings\n\n" << "\x1b[0m";
    cout << "1. Edit user puzzle save location\n2. Edit complete puzzle save location\n";
    cout << "Type -e to exit" << endl;
    
    do {
        cout << "\n\x1b[5;2mAwaiting Command..." << "\x1b[0m";
        cin >> cmd;
        
        switch (cmd){
            case '-':
                getCommand(false);
                cont = false;
                break;
            case '1':
                doCommand(cmd);
                cont = false;
                break;
            case '2':
                doCommand(cmd);
                cont = false;
                break;
            default:
                cout << "\nPlease enter a valid command." << endl;
                break;
        }
    } while (cont);
}

Menu_noANSI::Menu_noANSI(){
    currentScreen = none;
    hints = false;
}

void Menu_noANSI::init(string s, Square sqr){
    settingsFilePath = s;
    mainSquare = sqr;
    newSettings = GLOBAL::fetchSettings(settingsFilePath);
}

void Menu_noANSI::getCommand(){
    char com;
    cout << '\n';
    cout << "\nAwaiting Command...";
    cin >> com;
    doCommand(com);
}

void Menu_noANSI::getCommand(bool commandText){
    char com;
    if (commandText){
        cout << '\n';
        cout << "\nAwaiting Command...";
    }
    cin >> com;
    doCommand(com);
}

void Menu_noANSI::doCommand(char com){
    grd empty;
    init_grd(empty);
    string fileloc;
    srand(time(0));
    int sk;
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
                    this->showDifficulty();
                    break;
                case 'e':
                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                    exit(0);
                    break;
                default:
                    this->showMain();
                    cout << "Please try again and enter a valid command." << endl;
                    break;
            }
            break;
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
                    break;
            }
            break;
        case settings:
            switch (com){
                case 'e':
                    this->showMain();
                    break;
                case '1':
                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                    cout << "Enter the location of the file you would like to use as a save file for the editable grid (No Spaces): " << endl;
                    cout << "\n\nAwaiting Command...";
                    cin >> fileloc;
                    newSettings.savePath = fileloc;
                    GLOBAL::writeSettings(settingsFilePath, newSettings);
                    mainSquare.init(newSettings.skill, newSettings.savePath, newSettings.completePath);
                    this->showSettings();
                    break;
                case '2':
                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                    cout << "Enter the location of the file you would like to use as a save file for the complete grid (No Spaces): " << endl;
                    cout << "\n\nAwaiting Command...";
                    cin >> fileloc;
                    newSettings.completePath = fileloc;
                    GLOBAL::writeSettings(settingsFilePath, newSettings);
                    mainSquare.init(newSettings.skill, newSettings.savePath, newSettings.completePath);
                    this->showSettings();
                    break;
                default:
                    this->showSettings();
                    cout << "Please try again and enter a valid command." << endl;
                    break;
            }
            break;
        case difficulty:
            switch (com){
                case 'e':
                    this->showMain();
                    break;
                case '1':
                    sk = (rand() % 12) + 2;
                    newSettings.skill = sk;
                    GLOBAL::writeSettings(settingsFilePath, newSettings);
                    mainSquare.init(newSettings.skill, newSettings.savePath, newSettings.completePath);
                    this->showMain();
                    break;
                case '2':
                    sk = (rand() % 12) + 12;
                    newSettings.skill = sk;
                    GLOBAL::writeSettings(settingsFilePath, newSettings);
                    mainSquare.init(newSettings.skill, newSettings.savePath, newSettings.completePath);
                    this->showMain();
                    break;
                case '3':
                    sk = (rand() % 12) + 24;
                    newSettings.skill = sk;
                    GLOBAL::writeSettings(settingsFilePath, newSettings);
                    mainSquare.init(newSettings.skill, newSettings.savePath, newSettings.completePath);
                    this->showMain();
                    break;
                case '4':
                    sk = (rand() % 12) + 36;
                    newSettings.skill = sk;
                    GLOBAL::writeSettings(settingsFilePath, newSettings);
                    mainSquare.init(newSettings.skill, newSettings.savePath, newSettings.completePath);
                    this->showMain();
                    break;
                case '5':
                    sk = (rand() % 12) + 48;
                    newSettings.skill = sk;
                    GLOBAL::writeSettings(settingsFilePath, newSettings);
                    mainSquare.init(newSettings.skill, newSettings.savePath, newSettings.completePath);
                    this->showMain();
                    break;
                default:
                    this->showMain();
                    cout << "Please try again and enter a valid command." << endl;
                    break;
            }
            break;
    default:
        this->showMain();
        break;
    }
}

void Menu_noANSI::showGridScreen(){
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

    cout << "Grid Editor\n\n";
    mainSquare.display_noANSI();
    cout << "\n\n";
    cout << "To edit a point, type in the row, column, and value you wish to change the point to." << endl;
    cout << "For example, if you wanted to change the value at row 0, column 3 to 6, you would type: 0 3 6" << endl;
    cout << "Additionally, note that you are only able to edit spaces marked with a * character." << endl;
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

void Menu_noANSI::editGrid(){
    grd g;
    char row, col, val;
    bool command = false;
    bool error = false;
    currentScreen = grid;
    g = mainSquare.getGrid();

    this->showGridScreen();
    
    do{
        error = false;
        cout << "\n\nAwaiting Command...";
        cin >> row;

        if (row == '-'){
            getCommand(false);
            command = true;
        }

        else if (row >= 48 && row <= 56){
            cin >> col;
            if (col >= 48 && col <= 56){
                cin >> val;
                command = false;
            }
            else {
                command = true;
                error = true;
            }
        }

        else {
            command = true;
            error = true;
        }

        if (error){
            cout << "Please enter a valid command, or proper combination of row, column, and value" << endl;
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

void Menu_noANSI::showMain(){
    char cmd;
    int currentSk = (newSettings.skill / 12);
    currentScreen = main;
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "                                                                              " << endl;
    cout << "     *******                       **                 *                       " << endl;
    cout << "    *       ***                      **              **                       " << endl;
    cout << "   *         **                      **              **                       " << endl;
    cout << "   **        *                       **              **                       " << endl;
    cout << "    ***          **   ****           **      ****    **         **   ****     " << endl;
    cout << "   ** ***         **    ***  *   *** **     * ***  * **  ***     **    ***  * " << endl;
    cout << "    *** ***       **     ****   *********  *   ****  ** * ***    **     ****  " << endl;
    cout << "      *** ***     **      **   **   ****  **    **   ***   *     **      **   " << endl;
    cout << "        *** ***   **      **   **    **   **    **   **   *      **      **   " << endl;
    cout << "          ** ***  **      **   **    **   **    **   **  *       **      **   " << endl;
    cout << "           ** **  **      **   **    **   **    **   ** **       **      **   " << endl;
    cout << "            * *   **      **   **    **   **    **   ******      **      **   " << endl;
    cout << "  ***        *     ******* **  **    **    ******    **  ***      ******* **  " << endl;
    cout << " *  *********       *****   **  *****       ****     **   *** *    *****   ** " << endl;
    cout << "*     *****                      ***                  **   ***                " << endl;
    cout << "*                                                                             " << endl;
    cout << " **                                                                           " << endl;
    cout << endl;
    cout << "A Game By Bryson Weeks and Henry Sartor" << endl;
    cout << endl;
    cout << endl;
    cout << "1. New\n2. Load\n3. Settings\n4. Change Difficulty" << endl;
    cout << "\nCurrent Difficulty Level: ";

    switch (currentSk){
        case 0:
            cout << "Baby" << endl;
            break;
        case 1:
            cout << "Easy" << endl;
            break;
        case 2:
            cout << "Medium" << endl;
            break;
        case 3:
            cout << "Hard" << endl;
            break;
        case 4:
            cout << "Nightmare" << endl;
            break;
        case 5:
            cout << "Nightmare" << endl;
            break;
        default:
            cout << "None???" << endl;
            break;
    }

    cout << "\nType -e to quit the program" << endl;
    cout << "\nANSI = OFF";
    cout << "\n\nAwaiting Command...";
    cin >> cmd;
    if (cmd == '-'){
        getCommand(false);
    }
    else {
        doCommand(cmd);
    }
    
}

void Menu_noANSI::showDifficulty(){
    currentScreen = difficulty;
    char cmd;
    bool cont = true;
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "Change Difficulty\n\n";
    cout << "1. I'm too young to die" << endl;
    cout << "2. Hey, not too rough" << endl;
    cout << "3. Hurt me plenty" << endl;
    cout << "4. Ultra Violence" << endl;
    cout << "5. Nightmare!" << endl;
    cout << "\nType -e to exit" << endl;

    do{
        cout << "\n\nAwaiting Command...";
        cin >> cmd;
        
        switch (cmd){
            case '-':
                getCommand(false);
                cont = false;
                break;
            case '1':
                doCommand(cmd);
                cont = false;
                break;
            case '2':
                doCommand(cmd);
                cont = false;
                break;
            case '3':
                doCommand(cmd);
                cont = false;
                break;
            case '4':
                doCommand(cmd);
                cont = false;
                break;
            case '5':
                doCommand(cmd);
                cont = false;
                break;
            default:
                cout << "\nPlease enter a valid command." << endl;
                break; 
        }
    } while(cont);

}

void Menu_noANSI::showSettings(){
    currentScreen = settings;
    char cmd;
    bool cont = true;
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "Settings\n\n";
    cout << "1. Edit user puzzle save location\n2. Edit complete puzzle save location\n";
    cout << "Type -e to exit" << endl;
    
    do {
        cout << "\n\nAwaiting Command...";
        cin >> cmd;
        
        switch (cmd){
            case '-':
                getCommand(false);
                cont = false;
                break;
            case '1':
                doCommand(cmd);
                cont = false;
                break;
            case '2':
                doCommand(cmd);
                cont = false;
                break;
            default:
                cout << "\nPlease enter a valid command." << endl;
                break;
        }
    } while (cont);
}

