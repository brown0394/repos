#include <iostream>

int main(){
    int cases = 0, from = 0, to = 0;
    std::cin >> cases;
    for(int i = 0; i < cases; ++i){
        std::cin >> from >> to;
        int distance = to - from;
        int factor = 1;
        if(distance == 1){
            std::cout << 1 << '\n';
        }
        else{
            while(factor * factor < distance){
                ++factor;
            }
            if(factor * factor - factor < distance){
                std::cout << 2 * factor - 1 << '\n';
            }
            else{
                std::cout << 2 * factor - 2 << '\n';
            }
        }
    }
}