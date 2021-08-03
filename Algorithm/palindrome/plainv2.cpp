#include <iostream>
#include <fstream>
#include <string>

int main(){
    //std::ifstream in("palin.inp");
    //std::ofstream out("palin.out");

    int inputnum, begining, end, is_pal;
    bool change;
    std::cin >> inputnum;
    std::string str;
    for(int i = 0; i < inputnum; ++i){
        std::cin >> str;
        begining = 0;
        is_pal = 1;
        change = false;
        end = (str.size()) - 1;

        while(begining < end){
            if(str[begining] != str[end]){
                if(!change){
                    if(str[begining + 1] == str[end]){
                        ++begining;
                        change = true;
                    }
                    else if(str[begining] == str[end - 1]){
                        --end;
                        change = true;
                    }
                    else{
                        is_pal = 3;
                        break;
                    }
                }
                else{
                    is_pal = 3;
                    break;
                }
            }
            ++begining;
            --end;
        }
        if((is_pal == 1) && (change == true)){
            is_pal = 2;
        }
        std::cout << is_pal << std::endl;
    }
}