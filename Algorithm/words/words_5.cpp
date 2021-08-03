#include <algorithm>
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
    int inputnum, uhalf, bhalf, temp;
    in >> inputnum;
    uhalf = inputnum / 2;
    bhalf = (inputnum / 2) - !(inputnum % 2);
    
    std::string* str = new std::string[inputnum];

    for(int i = 0; i < inputnum; ++i){
        in >> str[i];
    }
    std::sort(str, str+inputnum);
    temp = Divide(str, uhalf, uhalf);
    for(; temp > -1; --temp){
        if(str[uhalf] != str[temp]){
            break;
        }
    }
    ++temp;
    if(str[temp] == str[temp + uhalf]){
        out << str[temp] << '\n';
    }
    else{
        out << "NONE\n";
    }






    in.close();
    out.close();

    delete[] str;
    return 0;
}