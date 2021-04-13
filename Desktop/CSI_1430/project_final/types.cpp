//types.cpp

#include "types.hpp"

#include <string>

using namespace std;
using namespace SUDK;

void SUDK::init_point(point &p){
    p.val = '0';
    p.canModify = false;
    p.modified = false;
}

void SUDK::init_grd(grd &g){
    point p;
    init_point(p);
    for (int i = 0; i < 9; i++){
        for (int n = 0; n < 9; n++){
            p.row = i;
            p.col = n;
            g[i].push_back(p);
        }
    }
}


ifstream& operator>>(ifstream& file, grd& g){

    char ch;
    bool beginBlock, endBlock = false, exit = false, error = false, comment = false;
    string s;
    int r, c, h;
    char v;
    point p;
    grd g2;

    init_point(p);

    init_grd(g2);

    file >> s;

    for (string::size_type i = 0; i < s.length(); i++){
        s[i] = toupper(s[i]);
    }
    if (s != "#START"){
        exit = true;
        throw SUDK::bad_start();
        error = true;
    }

    while (!exit){
    
        do{
            file.get(ch);
            if (ch == '{'){
                beginBlock = true;
            }
            else {
                beginBlock = false;
            }
            if (file.eof()){
                throw SUDK::malformed_block();
                beginBlock = true;
                exit = true;
                error = true;
            }
        } while(!beginBlock);

        if (!exit){
            do {
                file >> s;
                for (string::size_type i = 0; i < s.length(); i++){
                    s[i] = toupper(s[i]);
                }
                if (s[0] == '*' && !comment){
                    comment = true;
                }

                if (s[s.length() - 1] == '*' && comment){
                    comment = false;
                }
                else if ((s == "ROW") && !comment){
                    file >> r;
                    if (r > 8 || r < 0){
                        throw SUDK::out_of_range();
                        error = true;
                        endBlock = true;
                        exit = true;
                    }
                    else{
                        p.row = r;
                    }
                }
                else if ((s == "COL" || s == "COLUMN") && !comment){
                    file >> c;
                    if (c > 8 || c < 0){
                        throw SUDK::out_of_range();
                        error = true;
                        endBlock = true;
                        exit = true;
                    }
                    else{
                        p.col = c;
                    }
                }
                else if ((s == "CANMOD" || s == "CANMODIFY") && !comment){
                    file >> h;
                    if (h != 0 && h != 1){
                        throw SUDK::invalid_bool();
                        error = true;
                        endBlock = true;
                        exit = true;
                    }
                    else {
                        p.canModify = (h == 1);
                    }
                }
                else if ((s == "MODDED" || s == "MODIFIED" || s == "MOD") && !comment){
                    file >> h;
                    if (h != 0 && h != 1){
                        throw SUDK::invalid_bool();
                        error = true;
                        endBlock = true;
                        exit = true;
                    }
                    else {
                        p.modified = (h == 1);
                    }
                }
                else if ((s == "VAL" || s == "VALUE") && !comment){
                    file >> v;
                    p.val = v;
                }
                else if ((s == "}") && !comment){
                    endBlock = true;
                }
                else if ((s == "#END") && !comment){
                    endBlock = true;
                    exit = true;
                }
                else if (!comment) {
                    throw SUDK::bad_marker();
                    exit = true;
                    endBlock = true;
                    error = true;
                }
                if (file.eof() && !exit){
                    exit = true;
                    endBlock = true;
                    throw SUDK::bad_end();
                    error = true;
                }
            } while (!endBlock);

            if (!error && !exit){
                g2[p.row][p.col] = p;
                init_point(p);
            }
        }
        if (!error){
            g = g2;
        }
    }
    return file;
}