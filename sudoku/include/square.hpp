//square.hpp

#ifndef _SQUARE_H_
#define _SQUARE_H_

#include <types.hpp>

#include <vector>
#include <fstream>
#include <string>

class Square {
    private:
        //Class Variables
        SUDK::grd grid;
        SUDK::grd compGrid;
        int skill;
        SUDK::point p;
        std::string savePath;
        std::string compPath;

        //Loading/Saving Game
        SUDK::grd readSUDK(std::string);

        //Checking Functions
        bool checkCell(char num, int row, int col, SUDK::grd grid) const;
        bool checkCol(char num, int col, SUDK::grd grid) const;
        bool checkRow(char num, int row, SUDK::grd grid) const;
        bool check(char num, int row, int col, SUDK::grd grid) const;

        //Generation Functions
        void replenish(std::vector<char>&);

    public:
        //Constructors
        Square();
        void init(int, std::string, std::string);
        
        //Accessors
        SUDK::grd getGrid() const;
        SUDK::grd getCompGrid() const;

        //Mutators
        void setGrid(SUDK::grd);
        void setCompGrid(SUDK::grd);

        //Loading/Saving Game
        void load();
        void save();

        //Display Functions (Might Move this under menu class)
        void display() const;
        void display_noANSI() const;

        //Generation Functions
        void create();
        void format();

        //Checking Functions
        void checkUserSquare(bool);

};


#endif