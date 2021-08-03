#include <iostream>
#include <vector>

int main(){
    int* i = new int;
    int t = 3;

    i = &t;

    std::vector<int*> num;
    num.push_back(i);

    int* temp = num.back();
    num.pop_back();

    std::cout << *temp;

}