#include <iostream>

class Schedule{
public:
    int begin;
    int end;
    int cost;
    Schedule():begin(0), end(0), cost(0){}
    void operator=(const Schedule& other){
        this->begin = other.begin;
        this->end = other.end;
        this->cost = other.cost;
    }
};

int main(){
    int num, maxcost=0, maxdays=0, lastend, fday, eday, calcost;
    std::cin >> num;
    Schedule* schedulelist = new Schedule[num];
    int* idxlist = new int[num];
    int idxidx;
    for(int i = 0; i < num; ++i){
        std::cin >> schedulelist[i].begin >> schedulelist[i].end >> schedulelist[i].cost;

        if(i == 0){
            maxcost = schedulelist[i].cost;
            maxdays = schedulelist[i].end - schedulelist[i].begin + 1;
            lastend = schedulelist[i].end;
        }
        else{
            if(schedulelist[i].end > lastend){
                maxcost += schedulelist[i].cost - 10;
                lastend = schedulelist[i].end;
            }
            else{
                fday = schedulelist[i].begin;
                eday = schedulelist[i].end;
                calcost = schedulelist[i].cost;
                idxidx = 0;
                for(int j = 0; j < i; ++i){
                    if(schedulelist[j].end < fday){

                        idxlist[idxidx] = j;
                        calcost += schedulelist[j].cost;
                    }
                }
            }

        }
    }

    delete[] schedulelist;
    delete[]idxlist;
    return 0;
}