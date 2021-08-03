#include <iostream>

int main(){
    int numb = 0, count = 0;
    std::cin >> numb;


    for(int i = 0; i < numb; ++i){
        int num = i+1;
        if(num > 99){
            int one = num / 100;
            int two = (num / 10) % 10;
            int three = num % 10;
            if((one - two == two - three) || (three - two == two - one)){
                ++count;
            }
        }
        else if(num < 100){
            ++count;
        }
    }
    std::cout << count;
    
}