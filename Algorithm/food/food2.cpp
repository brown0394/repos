#include <iostream>
#include <fstream>


class Node {
public:
    int protein, fat, carbo, vitamin, price, num;
    float score;
    Node() :protein(0), fat(0),
        carbo(0), vitamin(0), price(0), score(0.0f), num(0) {}
    Node(Node& other) :protein(other.protein), fat(other.fat),
        carbo(other.carbo), vitamin(other.vitamin), price(other.price), score(other.score), num(other.num) {}
    void operator=(const Node& other);
};

void Node::operator=(const Node& other) {
    this->protein = other.protein;
    this->fat = other.fat;
    this->carbo = other.carbo;
    this->price = other.price;
    this->vitamin = other.vitamin;
    this->score = other.score;
    this->num = other.num;
}

Node* Sort(Node* arr, int last) {
    int idx = 0, now = 1;
    Node* arranged = new Node[last];
    arranged[idx++] = arr[1];
    arr[1] = arr[last--];
    while (true) {
        if (last == 1) {
            break;
        }
        if (now * 2 <= last && arr[now].score < arr[now * 2].score) {
            if (((now * 2) + 1) <= last && arr[now * 2].score < arr[(now * 2) + 1].score) {
                Node temp(arr[now]);
                arr[now] = arr[(now * 2) + 1];
                arr[(now * 2) + 1] = temp;
                now = (now * 2) + 1;
            }
            else {
                Node temp(arr[now]);
                arr[now] = arr[(now * 2)];
                arr[(now * 2)] = temp;
                now = (now * 2);
            }
        }
        else if ((now * 2) + 1 <= last && arr[now].score < arr[(now * 2) + 1].score) {
            Node temp(arr[now]);
            arr[now] = arr[(now * 2) + 1];
            arr[(now * 2) + 1] = temp;
            now = (now * 2) + 1;
        }
        else {
            arranged[idx++] = arr[1];
            arr[1] = arr[last--];
            now = 1;
            continue;
        }
        if (now >= last) {
            arranged[idx++] = arr[1];
            arr[1] = arr[last--];
            now = 1;
        }
    }
    arranged[idx] = arr[1];
    delete[] arr;
    return arranged;
}

int main() {
    std::ifstream in("food.inp");
    std::ofstream out("food.out");
    int numfood = 0, protein = 0, fat = 0, carbo = 0, vitamin = 0;
    Node* heap;
    in >> numfood;
    heap = new Node[numfood + 1];
    in >> protein >> fat >> carbo >> vitamin;
    int minprice = 99999;
    for (int i = 1; i < numfood + 1; ++i) {
        int hpidx = i;
        in >> heap[i].protein >> heap[i].fat >> heap[i].carbo >> heap[i].vitamin >> heap[i].price;
        heap[i].score = (heap[i].protein + heap[i].fat + heap[i].carbo +
            heap[i].vitamin) / static_cast<float>(heap[i].price);
        heap[i].num = i;
        while (true) {
            if (hpidx == 1) {
                break;
            }
            if (heap[hpidx / 2].score < heap[hpidx].score) {
                Node temp(heap[hpidx]);
                heap[hpidx] = heap[hpidx / 2];
                heap[hpidx / 2] = temp;
            }
            hpidx /= 2;
        }
        if (heap[i].price < minprice) {
            minprice = heap[i].price;
        }
    }
    heap = Sort(heap, numfood);
    int* anstable = new int[numfood];
    int* table = new int[numfood];
    bool* visitable = new bool[numfood] {false};
    int totalpro = 0, totalfat = 0, totalcarb = 0, totalvit = 0, totalpri = 0;
    int bestprice = 99999, bestep = 0;
    int step = 0, tableidx = 0, ansidx = 0;
    int nutscore = 0, nutemp;
    bool changed = false;
    for (int i = 0; i < numfood; ++i) {
        tableidx = 0;
        table[tableidx++] = i;
        visitable[i] = true;
        totalpro = heap[i].protein;
        totalfat = heap[i].fat;
        totalcarb = heap[i].carbo;
        totalvit = heap[i].vitamin;
        totalpri = heap[i].price;
        step = 1;
        changed = false;
        int j = 0;
        while (true) {
            if (totalpri > bestprice) {
                --tableidx;
                j = table[tableidx];
                visitable[j] = false;
                if (tableidx == 0) {
                    break;
                }
                --step;
                totalpro -= heap[j].protein;
                totalfat -= heap[j].fat;
                totalcarb -= heap[j].carbo;
                totalvit -= heap[j].vitamin;
                totalpri -= heap[j].price;
                ++j;
                continue;
            }
            else if (totalpro >= protein && totalfat >= fat && totalcarb >= carbo && totalvit >= vitamin) {
                if (bestprice > totalpri) {
                    bestprice = totalpri;
                    bestep = step;
                    for (int k = 0; k < tableidx; ++k) {
                        anstable[k] = table[k];
                    }
                    ansidx = tableidx;
                    changed = true;
                }
                else if (bestprice == totalpri) {
                    nutemp = heap[j].protein + heap[j].carbo + heap[j].fat + heap[j].vitamin;
                    if (nutemp > nutscore) {
                        bestep = step;
                        nutscore = nutemp;
                        for (int k = 0; k < tableidx; ++k) {
                            anstable[k] = table[k];
                        }
                        ansidx = tableidx;
                        changed = true;
                    }
                }
                --tableidx;
                j = table[tableidx];
                visitable[j] = false;
                if (tableidx == 0) {
                    break;
                }
                totalpro -= heap[j].protein;
                totalfat -= heap[j].fat;
                totalcarb -= heap[j].carbo;
                totalvit -= heap[j].vitamin;
                totalpri -= heap[j].price;
                --step;
                ++j;
                continue;
            }
            if (j < numfood && !visitable[j] && totalpri + heap[j].price <= bestprice) {
                visitable[j] = true;
                table[tableidx++] = j;
                totalpro += heap[j].protein;
                totalfat += heap[j].fat;
                totalcarb += heap[j].carbo;
                totalvit += heap[j].vitamin;
                totalpri += heap[j].price;
                ++step;
                ++j;
                continue;
            }
            if (j == numfood) {
                if (tableidx > 1) {
                    --tableidx;
                    j = table[tableidx];
                    visitable[j] = false;
                    if (tableidx == 0) {
                        break;
                    }
                    totalpro -= heap[j].protein;
                    totalfat -= heap[j].fat;
                    totalcarb -= heap[j].carbo;
                    totalvit -= heap[j].vitamin;
                    totalpri -= heap[j].price;
                    --step;
                }
                else {
                    --tableidx;
                    j = table[tableidx];
                    visitable[j] = false;
                    break;
                }
            }
            ++j;
        }
        if(!changed){
            visitable[i] = true;
        }
    }

    bool sortable[50]{ false };


    for (int i = 0; i < ansidx; ++i) {
        sortable[heap[anstable[i]].num] = true;
    }
    for (int i = 0; i < 50; ++i) {
        if (sortable[i]) {
            out << i << ' ';
        }
    }

    /*
        for(int i = 1; i < numfood+1; ++i){
            out << heap[i].protein << ' ' << heap[i].fat << ' ' <<  heap[i].carbo << ' ' <<
            heap[i].vitamin << ' '  << heap[i].price << ' ' << heap[i].score << '\n';
        }
    */
    in.close();
    out.close();

    delete[] visitable;
    delete[] heap;
    delete[] anstable;
    delete[] table;
    return 0;
}