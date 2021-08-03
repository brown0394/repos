#include <iostream>

int main(){
    int numbers = 0, primes = 0;
    std::cin >> numbers;

    for(int i = 0; i < numbers; ++i){
        int input;
        std::cin >> input;
        int num = 2;
        bool is_prime = true;
        if(input > 1){
            while(num <= input / 2){
                if(num % input == 0){
                    is_prime = false;
                    break;
                }
                ++num;
            }
            if(is_prime){
                ++primes;
            }
        }
    }
    std::cout << primes << '\n';
}