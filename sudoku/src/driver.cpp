//driver.cpp

#include <square.hpp>
#include <menu.hpp>
#include <types.hpp>
#include <global.hpp>

#include <string>

using namespace std;

int main(){
    string settingsPath = "settings/settings.txt";
    SUDK::settings userSettings;
    int skill;
    string savePath, compPath;
    Menu myMenu;
    Square mySquare;

    userSettings = GLOBAL::fetchSettings(settingsPath);

    skill = userSettings.skill;
    savePath = userSettings.savePath;
    compPath = userSettings.completePath;
    mySquare.init(skill, savePath, compPath);
    myMenu.init(settingsPath, mySquare);

    myMenu.showMain();

    return 0;
}