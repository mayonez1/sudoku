//driver.cpp

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
    string savePath, compPath;
    Menu myMenu;
    Square mySquare;

    if (argc > 1){
        settingsPath = argv[1];
    }

    userSettings = GLOBAL::fetchSettings(settingsPath);

    skill = userSettings.skill;
    savePath = userSettings.savePath;
    compPath = userSettings.completePath;
    mySquare.init(skill, savePath, compPath);
    myMenu.init(settingsPath, mySquare);

    myMenu.showMain();

    return 0;
}