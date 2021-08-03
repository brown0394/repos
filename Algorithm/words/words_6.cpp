#include <iostream>
#include <fstream>
#include <string>

int Divide(std::string*& str, int num, int uhalf){
    int temp = num / 2;
    if(temp < 1){
        return num;
    }
    else{
        if(str[uhalf] == str[temp]){
            return Divide(str, temp, uhalf);
        }
        else{
            return num;
        }
    }
}

int main() {
    std::ifstream in("words.inp");
    std::ofstream out("words.out");
    int inputnum, count = 0, count2, idx = 0, end, last=0;
    in >> inputnum;
    std::string* str[2];
    str[0] = new std::string[inputnum];
    str[1] = new std::string[inputnum];
    for(int i = 0; i < inputnum; ++i){
        in >> str[0][i];
    }
    int j = inputnum - 1;
    end = inputnum;
    bool first = true, twob = false;
    while(1){
        count2 = (count + 1) % 2;
        end = (end / 2) + (end % 2);
        for(int i = 0; i < end; ++i){
            if(i == j){
                if(idx == 0){
                    if((str[count][i] == str[count][i+1]) || (str[count][i] == str[count][i-1])){
                        out << str[count][i] << '\n';
                    }
                    else{
                        out << "NONE" << '\n';
                    }
                    ++idx;
                    break;
                }
                str[count2][idx++] = str[count][i];

            }
            else if(str[count][i] == str[count][j]){
                str[count2][idx++] = str[count][i];
                str[count2][idx++] = str[count][i];
                if((i+1 == j) && (idx == 2)){
                    if((str[count][i] == str[count][i-1]) || (str[count][j] == str[count][j+1])){
                        out << str[count][i] << '\n';
                    }
                    else{
                        out << "NONE" << '\n';
                    }
                    twob = true;
                    break;
                }
            }
            --j;
        }
        if(last == idx){
            out << str[count2][0] << '\n';
            break;
        }
        if(idx == 1){
            break;
        }
        if(idx == 3){
            bool found = false;
            for(int i = 1; i < 3; ++i){
                if(str[count2][0] == str[count2][i]){
                    out << str[count2][0] << '\n';
                    found = true;
                    break;
                }
            }
            if(!found){
                out << str[count2][1] << '\n';
                break;
            }
            break;
        }
        if(twob){
            break;
        }
        if(idx == 0){
            out << "NONE" << '\n';
            break;
        }
        count = count2;
        end = idx;
        last = idx;
        j = idx - 1;
        idx = 0;
        first = false;
    }
    in.close();
    out.close();

    delete[] str[0];
    delete[] str[1];
    return 0;
}