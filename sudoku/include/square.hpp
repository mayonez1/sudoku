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
        int skill;
        SUDK::point p;
        std::string savePath;

        //Loading/Saving Game
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

        //Display Functions (Might Move this under menu class)
        void display() const;

    public:
        //Constructors
        Square();
        void init(int, std::string);
        
        //Accessors
        SUDK::grd getGrid() const;

        //Mutators
        void setGrid(SUDK::grd);

        //Loading/Saving Game
        void load();
        void save();

        //Wrappers/Executors
        //void testRun();


};


#endif