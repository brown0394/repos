#include <iostream>
#include <string>

int main(){
    int inputnum, halfb, halfu, is_pal = 1;
    std::cin >> inputnum;
    std::string str;
    for(int i = 0; i < inputnum; ++i){
        std::cin >> str;
        halfb = (str.size() / 2) - 1;
        if(str.size() % 2 == 0){
            halfu = halfb + 1;
        }
        else{
            halfu = halfb + 2;
        }
        while(halfb > -1)
        {
            if(str[halfb] != str[halfu]){
                is_pal = 3;
                break;
            }
            --halfb;
            ++halfu;
        }
        std::cout << is_pal << std::endl;
        is_pal = 1;
    }
}