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
        bool loadGame;
        int difficulty;
        SUDK::point p;

        //Loading/Saving Game
        void load();
        void load(std::string);
        void save();
        void save(std::string);
        SUDK::grd readSUDK(std::string);

        //Checking Functions
        bool checkCell(char num, int row, int col, SUDK::grd grid) const;
        bool checkCol(char num, int col, SUDK::grd grid) const;
        bool checkRow(char num, int row, SUDK::grd grid) const;
        bool check(char num, int row, int col, SUDK::grd grid) const;

        //Generation Functions
        void replenish(std::vector<char>&);
        void create();
        void format();
        void format(int);

        //Display Functions (Might Move this under menu class)
        void display() const;

    public:
        //Constructors
        Square();
        
        //Accessors
        SUDK::grd getGrid() const;

        //Mutators
        void setGrid(SUDK::grd);

        //Wrappers/Executors
        void testRun();


};


#endif