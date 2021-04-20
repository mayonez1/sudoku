//types.cpp

#include <types.hpp>

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


ifstream& operator>>(ifstream& file, grd& g){ 
    string s;
    char val;
    int input;
    int which = 999;
    bool cont = true, blockEnd = false, end = false;
    grd g2;
    point p;
    string validMarkers[10] {"ROW", "COL", "COLUMN", "CANMOD", "CANMODIFY", "MODDED", "MODIFIED", "MOD", "VAL", "VALUE"};

    SUDK::init_point(p);

    SUDK::init_grd(g2);

    std::getline(file, s);

    for (unsigned int i = 0; i < s.length(); i++){
        s[i] = toupper(s[i]);
    }

    if (s != "#START"){
        cont = false;
        throw SUDK::bad_start();
    }

    while (!file.eof() && cont && !end && file >> s){

        if (cont){
            if (s != "{"){
                cont = false;
                throw SUDK::malformed_block();
            }
            else {
                blockEnd = false;
            }
        }

        while(cont && !blockEnd && file >> s && !file.eof()){

            if (s == "}"){
                blockEnd = true;
                cont = false;
            }

            if (cont){
                for (unsigned int i = 0; i < s.length(); i++){
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
                        file >> val;
                        p.val = val;
                        break;
                } 
            }
            if (blockEnd){
                cont = true;
            }
        }

        if (cont){
            g2[p.row][p.col].val = p.val;
            g2[p.row][p.col].row = p.row;
            g2[p.row][p.col].col = p.col;
            g2[p.row][p.col].canModify = p.canModify;
            g2[p.row][p.col].modified = p.modified;
        }

        SUDK::init_point(p);
    }

    g.clear();
    for (int i = 0; i < 9; i++){
        g.push_back(g2[i]);
    }
    return file;
}

ifstream& operator>>(ifstream& file, SUDK::settings set){
    string s;
    int sk;

    file >> s;
    file >> sk;

    set.savePath = s;
    set.skill = sk;

    return file;
}