#include <iostream>
#include <string>
#include <cctype>
int main(){
    std::string inpt;
    std::getline(std::cin, inpt);
    int count = 0;
    int i = 0;
    bool newworkd = true;
    while(inpt[i] != '\0'){
        if(inpt[i] == ' '){
            if(i != 0){
                newworkd = true;
            }
        }
        if(isalpha(inpt[i]) && newworkd){
            newworkd = false;
            ++count;
        }
        ++i;
    }
    std::cout << count;
}