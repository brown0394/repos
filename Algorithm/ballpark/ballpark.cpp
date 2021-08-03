#include <iostream>
#include <fstream>

class Coord {
public:
    int _x;
    int _y;
    Coord() {};
    Coord(int x, int y) :_x(x), _y(y) {}
    void const operator=(const Coord& other) {
        this->_x = other._x;
        this->_y = other._y;
    }
};

class ParkPlan {
public:
    int N, M;
    int idx, square, rescount;
    Coord* coord, * result;
    ParkPlan(int n, int m) :N(n), M(m), rescount(0), idx(0), square(5) {
        coord = new Coord[N * M];
        result = new Coord[N * M];
    }
    ~ParkPlan() {
        delete[] coord;
        delete[] result;
    }
    void Search();
    void BiggerSearch(int bigger);
    void InputData(std::ifstream& in);
};

void ParkPlan::Search() {
    Coord leftlow(1, N - square +1), lefthigh(1, N);
    Coord rightlow(square, N - square+1), righthigh(square, N);
    int count = 0, nextl, nextr, last = 0;
    bool over = false, avail = true;

    while (rightlow._y > 0) {
        while(coord[last]._y > righthigh._y){
            ++last;
        }
        while (rightlow._x <= M) {
            while (count < idx) {
                if(coord[count]._y < rightlow._y){
                    break;
                }
                else if (coord[count]._x >= leftlow._x && coord[count]._x <= rightlow._x
                    && coord[count]._y >= leftlow._y && coord[count]._y <= righthigh._y) {
                    nextl = coord[count]._x + 1;
                    nextr = nextl + (square - 1);
                    if (nextr > M) {
                        over = true;
                        break;
                    }
                    leftlow._x = nextl;
                    lefthigh._x = nextl;
                    righthigh._x = nextr;
                    rightlow._x = nextr;
                    count = last;
                }
                else {
                    ++count;
                }
            }
            count = last;
            if (over) {
                over = false;
                break;
            }
            result[rescount++] = leftlow;
            while(1){
                if(rightlow._x + 1 > M || rightlow._y - 1 < 1){
                    break;
                }
                rightlow._x += 1;
                rightlow._y -= 1;
                leftlow._y -= 1;

                while (count < idx) {
                    if(coord[count]._y < rightlow._y){
                        break;
                    }
                    else if (coord[count]._x >= leftlow._x && coord[count]._x <= rightlow._x
                        && coord[count]._y >= leftlow._y && coord[count]._y <= righthigh._y) {
                        rightlow._x -= 1;
                        rightlow._y += 1;
                        leftlow._y += 1;
                        avail = false;
                        break;
                    }
                    else {
                        ++count;
                    }
                }
                count = last;
                if(avail){
                    square += 1;
                    rescount = 0;
                    result[rescount++] = leftlow;
                }
                else
                {
                    avail = true;
                    break;
                }
                
            }

            leftlow._x += 1;
            lefthigh._x += 1;
            rightlow._x += 1;
            righthigh._x += 1;
        }
        leftlow._x = 1;
        lefthigh._x = 1;
        rightlow._x = square;
        righthigh._x = square;
        leftlow._y -= 1;
        lefthigh._y -= 1;
        rightlow._y -= 1;
        righthigh._y -= 1;
    }
}



void ParkPlan::InputData(std::ifstream& in) {
    char num;
    for (int i = 0; i < N * M; ++i) {
        in >> num;
        if (num == '1') {
            coord[idx]._x = (i % M) + 1;
            coord[idx++]._y = N - (i / M);
        }
    }
}

int main() {
    std::ifstream in("ballpark.inp");
    std::ofstream out("ballpark.out");
    int N, M, idx = 0;
    in >> N >> M;
    ParkPlan plan(N, M);
    plan.InputData(in);
    plan.Search();
    out << plan.square << ' ' << plan.rescount << '\n';

    Coord temp;
    for(int i = 0; i < plan.rescount; ++i){
        for(int j = i+1; j < plan.rescount; ++j){
            if(plan.result[i]._x > plan.result[j]._x){
                temp = plan.result[j];
                plan.result[j] = plan.result[i];
                plan.result[i] = temp; 
            }

        }
    }
    for(int i = 0; i < plan.rescount; ++i){
        for(int j = i+1; j < plan.rescount; ++j){
            if(plan.result[i]._x == plan.result[j]._x){
                if(plan.result[i]._y > plan.result[j]._y){
                    temp = plan.result[j];
                    plan.result[j] = plan.result[i];
                    plan.result[i] = temp; 
                }                
            }
        }
    }



    for (int i = 0; i < plan.rescount; ++i) {
        out << plan.result[i]._x << ' ' << plan.result[i]._y << '\n';
    }

    in.close();
    out.close();

    return 0;
}