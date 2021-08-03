#include<iostream>

int main(){
    float one = 14.0923;
    int two = one;
    std::cout << one << "  " << two << "  " << one - two;

    if(one - two > 0){
        std::cout <<" " << two + 1;
    }
    else{
        std::cout << " "<<two;
    }
}