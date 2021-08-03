#include <iostream>

int main(){
    int kg;
    std::cin >> kg;
    if(kg / 5 == 0){
        if(kg % 3){
            std::cout << -1 << '\n';
        }
        else{
            std::cout << kg / 3 << '\n';
        }
    }
    else{
        if(kg % 5 == 0){
            std::cout << kg / 5 << '\n';
        }
        else if((kg % 5) % 3 == 0){
            std::cout << ((kg % 5) / 3) + ((kg - ((kg % 5) / 3)) / 5) << '\n';
        }//
        else{
            bool poss = false;
            int count = kg / 5;
            while(count != 0){
                if((kg - (5 * count)) % 3 == 0){
                    poss = true;
                    break;
                }
                --count;
            }
            if(poss){
                std::cout << count + ((kg - (5 * count)) / 3) << '\n';
            }
            else if(kg % 3 == 0){
                std::cout << kg / 3 << '\n';
            }
            else{
                std::cout << -1 << '\n';
            }
            
        }
    }
}