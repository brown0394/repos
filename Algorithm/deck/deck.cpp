#include <iostream>
#include <fstream>



int main() {
    std::ifstream in("deck.inp");
    std::ofstream out("deck.out");
    int num, sum = 0, sqsum = 0, intcnt = 0, sqcnt = 0, i, diff, sqdiff;
    in >> num;

    for(i = 1; i <= num; ++i){
        sum += i;
        sqsum += (i*i);
    }
    --i;
    while(in >> num){
        intcnt += num;
        sqcnt += (num * num);
        --i;
    }
    diff = sum - intcnt;
    if(i == 1){
        out << diff << '\n';
    }
    else{
        sqdiff = sqsum - sqcnt;
        int big = diff - 1, small = 1;
        while(big > small){
            if(((big*big) + (small * small)) == sqdiff){
                out << small << '\n' << big << '\n';
                break;
            }


            --big;
            ++small;
        }
    }


    in.close();
    out.close();
    return 0;
}
