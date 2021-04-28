//driver.cpp

//Project designed and developed by Bryson Weeks and Henry Sartor for Baylor CSI 1430

#include <square.hpp>
#include <menu.hpp>
#include <types.hpp>
#include <global.hpp>

#include <string>

using namespace std;

int main(int argc, const char **argv){
    string settingsPath = "settings/settings.txt";
    SUDK::settings userSettings;
    int skill;
    string savePath, compPath, osName;
    string argArr[argc];
    Menu myMenu;
    Menu_noANSI menu_no_ansi;
    Square mySquare;
    bool ANSI = true;

    osName = GLOBAL::getOS();

    if (osName == "WIN64" || osName == "WIN32" || osName == "WIN16" || osName == "WIN_OTHER" || osName == "DOS" || osName == "OTHER"){
        ANSI = false;
    }

    for (int i = 0; i < argc; i++){
        argArr[i] = argv[i];
    }

    if (argc > 1){
        for (int i = 1; i < argc; i++){
            if (argArr[i] == "-f" && (i+1 < argc)){
                settingsPath = argArr[i+1];
            }
            else if (argArr[i] == "-a" && (i+1 < argc)){
                if (argArr[i+1] == "1"){
                    ANSI = true;
                }
                else if (argArr[i+1] == "0"){
                    ANSI = false;
                }
            }
        }
    }

    userSettings = GLOBAL::fetchSettings(settingsPath);

    skill = userSettings.skill;
    savePath = userSettings.savePath;
    compPath = userSettings.completePath;
    mySquare.init(skill, savePath, compPath);

    if (ANSI){
        myMenu.init(settingsPath, mySquare);
        myMenu.showMain();
    }

    else{
        menu_no_ansi.init(settingsPath, mySquare);
        menu_no_ansi.showMain();
    }

    return 0;
}