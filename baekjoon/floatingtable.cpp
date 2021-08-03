#include <iostream>

int main(){
    int target = 0;
    std::cin >> target;

    int cur = 1, base = 1, count = 1;
    while(true){
        if(target <= cur){
            if(target == cur){
                break;
            }
            else if(cur - base < target){
                int diffrence = cur - target;
                base -= diffrence;
                count += diffrence;
            }
            else{
                --base;
                if(base % 2 == 1){
                    --cur;
                }
                else{
                    cur -= (base*2);
                }
                int diffrence = target - cur;
                base -= diffrence;
                count += diffrence;
            }
            break;
        }
        if(base % 2 == 1){
            ++cur;
        }
        else{
            cur += (base*2);
        }
        ++base;
    }
    std::cout << count << '/' << base << '\n';
}