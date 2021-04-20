//menu.cpp
#include <menu.hpp>

#include <string>

using namespace std;

Menu::Menu(){
    currentScreen = none;
}

void Menu::init(string s){
    settingsFilePath = s;
}