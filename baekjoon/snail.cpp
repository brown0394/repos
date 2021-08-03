#include <iostream>

int main(){
    unsigned int climb = 0, slip = 0, target = 0;
    std::cin >> climb >> slip >> target;
    unsigned int days = 0, mult = 1, loc = 0;
    while(true){
        loc += (climb * mult) - (slip * mult) + slip;
        days += mult;
        if(loc >= target){
            if(mult == 1){
                break;
            }
            loc -= (climb * mult) - (slip * mult) + slip;
            days -= mult;
            mult = 1;
            continue;
        }
        mult *= 2;
        loc -= slip;
    }

    std::cout << days;
}