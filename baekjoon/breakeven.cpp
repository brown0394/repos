#include <iostream>

int main(){
    unsigned int infra = 0, productfee = 0, cost = 0;
    std::cin >> infra >> productfee >> cost;
    
    if(productfee >= cost){
        std::cout << -1 << std::endl;
    }
    else{
        unsigned int count = 0;
        unsigned int profit = 0, charge = 0;
        unsigned int last1 = 0, last2 = 0;
        while(true){
            profit += cost*1000;
            charge += productfee*1000;
            count += 1000;
            if(profit - charge > infra){
                profit -= cost*1000;
                charge -= productfee*1000;
                count -= 1000;                
                while(true){
                    profit += cost;
                    charge += productfee;
                    ++count;
                    if(profit - charge > infra){
                        break;
                    }
                }
                break;
            }
        }
        std::cout << count << '\n';
    }
}