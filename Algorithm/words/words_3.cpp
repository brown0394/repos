#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream in("words.inp");
    std::ofstream out("words.out");
    int inputnum, half = 0, roomnum = 0, count = 0;
    in >> inputnum;
    std::string* room = new std::string[inputnum];
    int* numcount = new int[inputnum];
    std::string str;
    half = inputnum / 2;
    bool found = false;
    bool finish = false;

    for(int i = 0; i < inputnum; ++i){
        in >> str;
        for(int j = 0; j < count; ++j){
            if(room[j] == str){
                numcount[j] += 1;
                if(numcount[j] > half){
                    out << room[j] <<'\n';
                    finish = true;
                    break;
                }
                found = true;
                break;
            }
        }
        if(finish){
            break;
        }
        if(!found){
            numcount[count] = 1;
            room[count++] = str;
        }
    }
    if(!finish){
        out << "NONE" << '\n';
    }
 
    
    in.close();
    out.close();

    delete [] room;
    delete [] numcount;
    return 0;
}