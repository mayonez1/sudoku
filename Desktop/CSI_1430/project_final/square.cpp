//square_functions.cpp

#include "square.hpp"
#include "global.hpp"
#include "types.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace SUDK;

//Constructor definitions
Square::Square(){
    loadGame = false;
    init_grd(grid);
    difficulty = 12;
}

Square::Square(bool load){
    loadGame = load;
    init_grd(grid);
    difficulty = 12;
}

//Accessor Definitions
grd Square::getGrid() const{
    return grid;
}

//Mutator Definitions
void Square::setGrid(grd x){
    grid = x;
}

//Loading/Saving definitions
grd Square::readSUDK(string filePath){
    grd ret;
    bool error;
    ifstream file;
    string extension = ".SUDK";
    for (int i = 0; i < 5; i++){
        extension[i] = toupper(filePath[(filePath.length()-1) - (4 - i)]);
    }

    file.open(filePath);

    if (!file.is_open() || extension != ".SUDK"){
        throw SUDK::bad_file();
    }
    
    try{
        file >> ret;
        //Unfortunately there is no elegant way to catch all custom exceptions
        //So I have to catch each one manually
    } catch (SUDK::bad_marker &e){
        cerr << e.what() << endl;
        error = true;
    } catch (SUDK::malformed_block &e){
        cerr << e.what() << endl;
        error = true;
    } catch (SUDK::bad_start &e){
        cerr << e.what() << endl;
        error = true;
    } catch (SUDK::bad_end &e){
        cerr << e.what() << endl;
        error = true;
    } catch (SUDK::out_of_range &e){
        cerr << e.what() << endl;
        error = true;
    } catch (SUDK::invalid_bool &e){
        cerr << e.what() << endl;
        error = true;
    }

    if (error){
        throw SUDK::bad_read();
    }

    return ret;
}

void Square::load(string filePath){
    grd g;
    ifstream file;
    bool error = false;

    try {
        g = readSUDK(filePath);
    } catch(SUDK::bad_file &e){
        cerr << e.what() << endl;
        error = true;
    } catch (SUDK::bad_read &e){
        cerr << e.what() << endl;
        error = true;
    }

    if (!error){
        setGrid(g);
    }

}

void Square::save(){
    ofstream ofile("sudoku.sudk");
    int m, cm;
    grd g = getGrid();
    ofile << "#START" << '\n';

    for (int i = 0; i < 9; i++){
        for (int n = 0; n < 9; n++){
            cm = (g[i][n].canModify) ? 1 : 0;
            m = (g[i][n].modified) ? 1 : 0;

            ofile << '{' << '\n';
            ofile << "ROW " << g[i][n].row << '\n';
            ofile << "COL " << g[i][n].col << '\n';
            ofile << "CANMOD " << cm << '\n';
            ofile << "MODDED " << m << '\n';
            ofile << "VAL " << g[i][n].val << '\n';
            ofile << '}' << '\n' << '\n';
        }
    }
    ofile << "#END" << '\n';
    ofile.close();
}

void Square::save(string filePath){
    ofstream ofile(filePath);
    int m, cm;
    grd g = getGrid();
    ofile << "#START" << '\n';

    for (int i = 0; i < 9; i++){
        for (int n = 0; n < 9; n++){
            cm = (grid[i][n].canModify) ? 1 : 0;
            m = (grid[i][n].modified) ? 1 : 0;

            ofile << '{' << '\n';
            ofile << "ROW " << g[i][n].row << '\n';
            ofile << "COL " << g[i][n].col << '\n';
            ofile << "CANMOD " << cm << '\n';
            ofile << "MODDED " << m << '\n';
            ofile << "VAL " << g[i][n].val << '\n';
            ofile << '}' << '\n' << '\n';
        }
    }
    ofile << "#END" << '\n';
    ofile.close();
}


//Checking Function Definitions
bool Square::checkCell(char num, int row, int col, grd grid) const{
    int a, b, x, y;

    int cellNum;

    bool unique = true;

    bool arr[9] {false, false, false, false, false, false, false, false, false};
    arr[0] = (row < 3 && col < 3);
    arr[1] = (row < 3 && (col >= 3 && col < 6));
    arr[2] = (row < 3 && col >= 6);
    arr[3] = ((row >= 3 && row < 6) && col < 3);
    arr[4] = ((row >= 3 && row < 6) && (col >= 3 && col < 6));
    arr[5] = ((row >= 3 && row < 6) && col >= 6);
    arr[6] = (row >= 6 && col < 3);
    arr[7] = (row >= 6 && (col >= 3 && col < 6));
    arr[8] = (row >= 6 && col >= 6);


    for (int i = 0; i < 9; i++){
        if (arr[i] == true){
            cellNum = i;
        }
    }

    switch (cellNum){
        case 0:
            a = 0;
            b = 3;
            x = 0;
            y = 3;
            break;
        case 1:
            a = 0;
            b = 3;
            x = 3;
            y = 6;
            break;
        case 2:
            a = 0;
            b = 3;
            x = 6;
            y = 9;
            break;
        case 3:
            a = 3;
            b = 6;
            x = 0;
            y = 3;
            break;
        case 4:
            a = 3;
            b = 6;
            x = 3;
            y = 6;
            break;
        case 5:
            a = 3;
            b = 6;
            x = 6;
            y = 9;
            break;
        case 6:
            a = 6;
            b = 9;
            x = 0;
            y = 3;
            break;
        case 7:
            a = 6;
            b = 9;
            x = 3;
            y = 6;
            break;
        case 8:
            a = 6;
            b = 9;
            x = 6;
            y = 9;
            break;
    }

    for (int i = a; i < b; i++){
        for (int n = x; n < y; n++){
            unique = (num == grid[i][n].val) ? false : unique;
        }
    }
    return unique;
}

bool Square::checkCol(char num, int col, grd grid) const{
    bool unique = true;

    for (int i = 0; i < 9; i++){
        unique = (grid[i][col].val == num) ? false : unique;
    }
    return unique;
}

bool Square::checkRow(char num, int row, grd grid) const{
    bool unique = true;
    for (int i = 0; i < 9; i++){
        unique = (grid[row][i].val == num) ? false : unique;
    }
    return unique;
}

bool Square::check(char num, int row, int col, grd grid) const{
    bool alles;
    bool a, b, c;

    a = checkCell(num, row, col, grid);
    b = checkCol(num, col, grid);
    c = checkRow(num, row, grid);

    if ((b && c) && a){
        alles = true;
    }

    else{
        alles = false;
    }

    return alles;
}

//Generation Functions Definitions
void Square::replenish(vector<char> &d){
    d.clear();
    char c[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for (int i = 0; i < 9; i++){
        d.push_back(c[i]);
    }
}

void Square::create(){
    grd g = getGrid();
    //Initializing/seeding rand for the first time
    srand(time(0));
    //availableNums holds all the unused numbers for each point in the grid
    vector<vector<vector<char>>> availableNums;
    //dummyRow and dummyPoint are two dummy vectors that will be used exclusively to populate availableNums
    vector<vector<char>> dummyRow;
    vector<char> dummyPoint;
    //seed will be used as the random seed
    unsigned int seed = rand();
    //pos will be randomized and will tell the program which value it should pick from availableNums
    unsigned int pos;
    //num is the number that is being guessed
    char num;
    //unique and empty tell us if num has passed all the checks and is unique, and if availableNums is empty
    bool unique, empty;

    //Populating availableNums
    for (int i = 0; i < 9; i++){
        for (int n = 0; n < 9; n++){
            replenish(dummyPoint);
            dummyRow.push_back(dummyPoint);
        }
        availableNums.push_back(dummyRow);
        dummyRow.clear();
    }

    for (int i = 0; i < 9; i++){
        for (int n = 0; n < 9; n++){
            //Randomizing the seed
            randomNum(seed);

            //Checks if all available numbers for this point have been used
            //Technically the bool isn't necessary, but it makes the code a bit more readable
            empty = (availableNums[i][n].empty());

            if (empty){
                //Replenish the available numbers
                replenish(availableNums[i][n]);

                //Set the grid at this position to the placeholder value, I chose '0'
                g[i][n].val = '0';

                //If it's on the first column of the row, backtrack to the previous row
                if (n == 0){
                    i -= 1;
                    n = 7;
                }
                //Otherwise, go back one place in the row
                else{
                    n -= 2;
                }
            }
            else{
                //Get a random position in the array
                randomNum(pos, availableNums.size(), seed);

                //Use that position to get a random number out of those available
                num = availableNums[i][n][pos];

                //See if that number is unique
                unique = check(num, i, n, g);

                //If it is unique put it in the grid
                if (unique){
                    g[i][n].val = num;
                }

                //Otherwise, erase that number from the availableNums vector and try again
                else{
                    availableNums[i][n].erase(availableNums[i][n].begin() + pos);
                    n -= 1;
                }
            }
        }
    }
    setGrid(g);
}

void Square::format(int sk){
    grd g = getGrid();
    unsigned int seed1, seed2, row, col;

    randomNum(seed1, time(0));
    randomNum(seed2, seed1);

    for (int i = 0; i < sk; i++){
        randomNum(row, 9, seed1);
        randomNum(row, 9, seed2);

        g[row][col].val = ' ';
        g[8-row][8-col].val = ' ';

        randomNum(seed1, seed2);
        randomNum(seed2, seed1);
    }

    setGrid(g);
}

void Square::format(){
    //Default difficulty is 12
    grd g = getGrid();
    unsigned int seed1, seed2, row, col;

    randomNum(seed1, time(0));
    randomNum(seed2, seed1);

    for (int i = 0; i < 12; i++){
        randomNum(row, 9, seed1);
        randomNum(row, 9, seed2);

        g[row][col].val = ' ';
        g[8-row][8-col].val = ' ';

        randomNum(seed1, seed2);
        randomNum(seed2, seed1);
    }

    setGrid(g);
}

//Display Functions Definitions
void Square::display() const{
    grd g = getGrid();
    for (int i = 0; i < 9; i++){
        for (int n = 0; n < 9; n++){
            cout << g[i][n].val << "   ";
        }
        cout << endl;
    }
}

//Wrappers/Executors Definitions

void Square::testRun(){
    char ans;
    bool load;
    cout << "Do you want to load?" << endl;
    cin >> ans;
    load = (ans == 'y');
    if (load){
        this->load("./Desktop/CSI_1430/project_final/sudkTest.sudk");
        this->display();
    }
    else {
        this->create();
        this->format();
        this->display();
        this->save("./Desktop/CSI_1430/project_final/sudkTest.sudk");
    }
}













