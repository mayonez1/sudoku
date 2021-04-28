//square.cpp

#include <square.hpp>
#include <global.hpp>
#include <types.hpp>

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace SUDK;
using namespace GLOBAL;

//Constructor definitions
Square::Square(){
    p.val = '0';
    p.canModify = false;
    p.modified = false;
    p.row = 0;
    p.col = 0;
    vector<point> holder;

    for (int i = 0; i < 9; i++){
        for (int n = 0; n < 9; n++){
            p.row = i;
            p.col = n;
            holder.push_back(p);
        }
        grid.push_back(holder);
        compGrid.push_back(holder);
        holder.clear();
    }
}

void Square::init(int sk, std::string path, std::string comppath){
    skill = sk;
    savePath = path;
    compPath = comppath;
}

//Accessor Definitions
grd Square::getGrid() const{
    return grid;
}

grd Square::getCompGrid() const{
    return compGrid;
}

//Mutator Definitions
void Square::setGrid(grd x){
    grid = x;
}

void Square::setCompGrid(grd x){
    compGrid = x;
}

//Loading/Saving definitions
grd Square::readSUDK(string filePath){
    grd ret;
    bool error = false;
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

    file.close();

    return ret;
}

void Square::load(){
    grd g, compG;
    bool error = false;

    try {
        g = readSUDK(savePath);
    } catch(SUDK::bad_file &e){
        cerr << e.what() << endl;
        error = true;
    } catch (SUDK::bad_read &e){
        cerr << e.what() << endl;
        error = true;
    }

    try {
        compG = readSUDK(compPath);
    } catch(SUDK::bad_file &e){
        cerr << e.what() << endl;
        error = true;
    } catch (SUDK::bad_read &e){
        cerr << e.what() << endl;
        error = true;
    }

    if (!error){
        grid = g;
        compGrid = compG;
    }
    else {
        cout << "Could not load SUDK file, please check save filepath in settings.txt file." << endl;
        cout << "Exiting Program..." << endl;
        exit(0);
    }
}

void Square::save(){
    ofstream ofile, compFile;
    ofile.open(savePath);
    compFile.open(compPath);
    int m, cm;
    grd g = getGrid();
    grd compG = getCompGrid();
    ofile << "#START" << '\n';
    compFile << "#START" << '\n';

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

    for (int i = 0; i < 9; i++){
        for (int n = 0; n < 9; n++){
            cm = (compGrid[i][n].canModify) ? 1 : 0;
            m = (compGrid[i][n].modified) ? 1 : 0;

            compFile << '{' << '\n';
            compFile << "ROW " << compG[i][n].row << '\n';
            compFile << "COL " << compG[i][n].col << '\n';
            compFile << "CANMOD " << cm << '\n';
            compFile << "MODDED " << m << '\n';
            compFile << "VAL " << compG[i][n].val << '\n';
            compFile << '}' << '\n' << '\n';
        }
    }
    ofile.close();
    compFile.close();
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
    unsigned int seed;
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
            _seed(seed);

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
                try{
                    randomNum(pos, availableNums[i][n].size(), seed);
                } catch (GLOBAL::mod_by_0 &e){
                    cerr << e.what() << '\n';
                }

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
                    availableNums[i][n].erase(availableNums[i][n].begin() + pos); //Error Here
                    n -= 1;
                }
            }
        }
    }
    setGrid(g);
    setCompGrid(g);
}

void Square::format(){
    grd g = getGrid();
    unsigned int seed1, seed2, row, col;

    _seed(seed1);
    _seed(seed2, seed1);

    //Default difficulty is 12
    for (int i = 0; i < skill; i++){
        randomNum(row, 9, seed1);
        randomNum(col, 9, seed2);

        g[row][col].val = '0';
        g[8-row][8-col].val = '0';
        g[row][col].canModify = true;
        g[8-row][8-col].canModify = true;

        _seed(seed1, seed2);
        _seed(seed2, seed1);
    }

    setGrid(g);
}

//Display Functions Definitions
void Square::display() const{
    char out;
    cout << "\x1b[1;36m";
    cout << "     0     1     2     3     4     5     6     7     8   " << endl;
    for (int i = 0; i < 9; i++){
        cout << "---------------------------------------------------------" << endl;
        cout << i << " |  ";
        for (int n = 0; n < 9; n++){
            if (grid[i][n].val == '0'){
                out = 32; //ASCII code for space so program doesn't mix it up with a NULL
            }
            else {
                out = grid[i][n].val;
            }
            if (grid[i][n].canModify){
                cout << out << "* |  "; //An asterisk next to the value in the output tells the user that this value can be modified
            }
            else {
                cout << out << "  |  ";
            }
        }
        cout << endl;
    }
    cout << "\x1b[0m";
}

//Public Checking Function Definitions
void Square::checkUserSquare(bool hints){
    vector<point> incorrectPoints;
    bool correct = true;
    for (int i = 0; i < 9; i++){
        for (int n = 0; n < 9; n++){
            if (this->getGrid()[i][n].val != this->getCompGrid()[i][n].val){
                correct = false;
                incorrectPoints.push_back(this->getGrid()[i][n]);
            }
        }
    }

    if (correct){
        cout << "You solved the puzzle!" << endl;
    }
    else {
        cout << "Puzzle is incorrect. Please try again." << endl;
    }

    if (hints && !correct){
        cout << "These are the points that are incorrect: " << endl;
        for (unsigned int i = 0; i < incorrectPoints.size(); i++){
            cout << '(' << incorrectPoints[i].row << ", " << incorrectPoints[i].col << ')' << " ";
        }
    }
}

//Wrappers/Executors Definitions

/*

void Square::testRun(){
    char ans;
    bool ld;
    cout << "Do you want to load?" << endl;
    cin >> ans;
    ld = (ans == 'y') ? true : false;
    if (ld){
        this->load();
        this->display();
    }
    else {
        this->create();
        this->format();
        this->display();
        this->save();
    }
}

*/