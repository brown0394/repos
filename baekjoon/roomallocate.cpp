#include <iostream>

int main(){
    int testnum = 0, width = 0, height = 0, custnum = 0, count = 0, floor = 0, roomnum = 0;
    std::cin >> testnum;
    for(int i = 0; i < testnum; ++i){
        std::cin >> height >> width >> custnum;
        roomnum = 1 + (custnum / height);
        floor = custnum % height;
        if(floor == 0){
            floor = height;
            roomnum -= 1;
        }
        if(roomnum < 10){
            std::cout << floor << '0' << roomnum << '\n';
        }
        else{
            std::cout << floor << roomnum << '\n';
        }
    }

}