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
    string savePath;
    Menu myMenu;
    Square mySquare;


    if (argc >= 1){
        settingsPath = argv[0];
    }

    userSettings = GLOBAL::fetchSettings(settingsPath);

    skill = userSettings.skill;
    savePath = userSettings.savePath;
    myMenu.init(settingsPath);
    mySquare.init(skill, savePath);

}