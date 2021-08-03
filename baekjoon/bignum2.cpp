#include <iostream>
#include <string>

int main(){
    std::string str1, str2, result = "";
    std::cin >> str1 >> str2;
    char operand1, operand2;
    int which = 0;
    if(str1.size() <= str2.size()){
        which = 1;
    }
    else{
        which  = 2;
    }
}