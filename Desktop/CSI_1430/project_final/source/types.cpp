//types.cpp

#include "types.hpp"

#include <string>

using namespace std;
using namespace SUDK;

void SUDK::init_point(point &p){
    p.val = '0';
    p.canModify = false;
    p.modified = false;
    p.row = 0;
    p.col = 0;
}

void SUDK::init_grd(grd &g){
    point p;
    init_point(p);
    vector<point> holder;
    for (int i = 0; i < 9; i++){
        for (int n = 0; n < 9; n++){
            p.row = i;
            p.col = n;
            holder.push_back(p);
        }
        g.push_back(holder);
        holder.clear();
    }
}


ifstream& operator>>(ifstream& file, grd& g){ //g is assumed to have been initialised
    string s;
    char c, val;
    int input;
    int count = 0;
    int which = 999;
    bool cont = true, blockEnd = false, end = false;
    point p;
    string validMarkers[11] {"ROW", "COL", "COLUMN", "CANMOD", "CANMODIFY", "MODDED", "MODIFIED", "MOD", "VAL", "VALUE", "}"};

    SUDK::init_point(p);

    std::getline(file, s);

    for (int i = 0; i < s.length(); i++){
        s[i] = toupper(s[i]);
    }

    if (s != "#START"){
        cont = false;
        throw SUDK::bad_start();
    }

    while (!file.eof() && cont && !end){

        if (cont){
            file.get(c);
            if (c != '{'){
                cont = false;
                throw SUDK::malformed_block();
            }
            else {
                blockEnd = false;
            }
        }

        while(cont && !blockEnd){

            if (count > 200){
                cont = false;
                throw SUDK::malformed_block();
            }

            if (cont){
                file >> s;
                for (int i = 0; i < s.length(); i++){
                    s[i] = toupper(s[i]);
                }
                for (int i = 0; i < 10; i++){
                    which = (s == validMarkers[i]) ? i : which;
                }
                if (which == 999){
                    cont = false;
                    throw SUDK::bad_marker();
                }
            }

            if (cont){
                switch (which){
                    case 0:
                        file >> input;
                        if (input > 9 || input < 0){
                            cont = false;
                            throw SUDK::out_of_range();
                        }
                        else {
                            p.row = input;
                        }
                        break;
                    
                    case 1:
                    case 2:
                        file >> input;
                        if (input > 9 || input < 0){
                            cont = false;
                            throw SUDK::out_of_range();
                        }
                        else {
                            p.col = input;
                        }
                        break;
                    
                    case 3:
                    case 4:
                        file >> input;
                        if (input != 0 && input != 1){
                            cont = false;
                            throw SUDK::invalid_bool();
                        }
                        else {
                            if (input == 1){
                                p.canModify = true;
                            }
                            else {
                                p.canModify = false;
                            }
                        }
                        break;
                    
                    case 5:
                    case 6:
                    case 7:
                        file >> input;
                        if (input != 0 && input != 1){
                            cont = false;
                            throw SUDK::invalid_bool();
                        }
                        else {
                            if (input == 1){
                                p.modified = true;
                            }
                            else {
                                p.modified = false;
                            }
                        }
                        break;
                    
                    case 8:
                    case 9:
                        file.get(val);
                        p.val = val;
                        break;
                    case 10:
                        blockEnd = true;
                        count = 0;
                        break;
                }
            }
            count++;
        }

        if (cont){
            g[p.row][p.col] = p;
        }

        SUDK::init_point(p);

        file >> s;

        for (int i = 0; i < s.length(); i++){
            s[i] = toupper(s[i]);
        }

        if (s == "#END"){
            end = true;
        }

        if (file.eof() && !end){
            cont = false;
            throw SUDK::bad_end();
        }

    }
}