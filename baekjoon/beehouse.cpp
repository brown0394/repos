#include<iostream>

int main(){
    int target = 0;
    std::cin >> target;

    int level = 1, curr = 1, mult = 6;
    while(true){
        if(target <= curr){
            break;
        }
        curr += mult;
        mult += 6;
        ++level;
    }
    std::cout << level << '\n';
}