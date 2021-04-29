//driver.cpp

//Project designed and developed by Bryson Weeks and Henry Sartor for Baylor CSI 1430

#include <square.hpp>
#include <menu.hpp>
#include <types.hpp>
#include <global.hpp>

#include <string>

using namespace std;

int main(int argc, const char **argv){
    string settingsPath = "settings/settings.txt"; //Default filepath for the settings.txt file, the / is (probably) changed to a \ if the user is on a Windows machine
    SUDK::settings userSettings; //the settings data type that the data from settings.txt will be put into
    int skill; //The skill value that is retrieved from the settings.txt file
    string savePath, compPath, osName; //Names are basically self-explanatory here
    string argArr[argc]; //Chages the const char **argc into an array of strings so that they can be compared
    Menu myMenu; //Uses this menu if ANSI = true
    Menu_noANSI menu_no_ansi; //Uses this menu if ANSI = false 
    Square mySquare; //Square that is being initialised and copied into the mainSquare variable in one of the Menu classes
    bool ANSI = true; //Boolean that determines if ANSI should be enabled or not. Set to true by default, because if the OS likely supports ANSI, I would prefer if it was used

    osName = GLOBAL::getOS();

    if (osName == "WIN64" || osName == "WIN32" || osName == "WIN16" || osName == "WIN_OTHER" || osName == "DOS" || osName == "OTHER"){ //Turns off ANSI escape code usage if one of these operating systems are being used
        ANSI = false;
    }

    if (osName == "WIN64" || osName == "WIN32" || osName == "WIN16" || osName == "WIN_OTHER"){ //Changes the settingsPath to use a backslash instead of a forward slash if being run on a windows machine
        settingsPath = "settings\\settingsWIN.txt";                                            //Note: I do not currently have a way to compile and test this on a Windows machine, so I'm just assuming here
    }

    for (int i = 0; i < argc; i++){ //Puts the arguments into the argArr so that they can be compared
        argArr[i] = argv[i];
    }

    if (argc > 1){ //Determines the argument being used and acts accordingly
        for (int i = 1; i < argc; i++){
            if (argArr[i] == "-f" && (i+1 < argc)){ //For the -f argument, anything that comes after it will be attempted to be used as a filepath
                settingsPath = argArr[i+1];         //This includes the -a argument delimiter, and non-valid filepaths
                                                    //If the program does run into this issue of attempting to use a non-valid filepath, it will throw an error and not start
            }
            else if (argArr[i] == "-a" && (i+1 < argc)){ //Note that for the -a argument, using anything other than 0 or 1 after -a will cause the ANSI boolean to stay as it's default
                if (argArr[i+1] == "1"){                 //(As determinded by your OS)
                    ANSI = true;
                }
                else if (argArr[i+1] == "0"){
                    ANSI = false;
                }
            }
        }
    }

    userSettings = GLOBAL::fetchSettings(settingsPath); //Getting the settings data

    //Splitting up the settings data into various variables so that they can be used for initialisation
    skill = userSettings.skill;
    savePath = userSettings.savePath;
    compPath = userSettings.completePath;

    //Initialises the Square using the skill, savePath, and compPath variables
    mySquare.init(skill, savePath, compPath);

    if (ANSI){ //If the user is running an OS that supports likely ANSI or has enabled it manually using the -a 1 argument
        myMenu.init(settingsPath, mySquare); //Initialises the regular, ANSI-enabled menu with the settingsPath and mySquare variables
        myMenu.showMain(); //Shows the main menu, which is sort of like calling a run() function
    }

    else{ //If the user is using an OS that likely does not support ANSI or it has been disabled manually using the -a 0 argument
        menu_no_ansi.init(settingsPath, mySquare);
        menu_no_ansi.showMain();
    }

    return 0;
}