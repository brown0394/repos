#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Node {
public:
    std::string _str;
    int _numbers;

    Node() :_numbers(0) {}
};


int main() {
    std::ifstream in("words.inp");
    std::ofstream out("words.out");
    std::string* str;
    Node* node;
    int inputnum, idx1, idx2, stcount = 0, count = 0, size = 0;
    in >> inputnum;
    idx1 = (inputnum / 2) + (inputnum % 2);
    idx2 = inputnum / 2;
    str = new std::string[inputnum];
    node = new Node[idx1];
    std::vector<std::string> store;
    store.resize(idx1);
    int l = 0;
    for (; l < idx1; ++l) {
        in >> str[l];
    }
    for (; l < inputnum; ++l) {
        in >> str[l];
    }

    for (int i = 0; i < idx2; ++i) {
        if (str[i] == str[idx2 + i]) {
            store[stcount++] = str[i];
        }
    }
    if (idx1 > idx2) {
        store[stcount++] = str[inputnum - 1];
    }
    size = stcount;

    if (stcount == 1) {
        for (int i = 0; i < inputnum; ++i) {
            if (store[0] == str[i]) {
                ++count;
                if (count > idx2) {
                    break;
                }
            }
        }
        if (count > idx2) {
            out << store[0] << '\n';
        }
        else {
            out << "NONE" << '\n';
        }
    }
    else {
        int nodecnt = 0;
        for (int i = 0; i < size; ++i) {
            if(store[i] != ""){
                node[nodecnt]._str = store[i];
                for (int j = i + 1; j < size; ++j) {
                    if(store[j] != ""){
                        if (store[i] == store[j]) {
                            node[nodecnt]._numbers += 1;
                            store[j].erase();
                        }
                    }
                }
                ++nodecnt;
            }
        }

        std::string* temp = &node[0]._str;
        int max = node[0]._numbers;
        for (int i = 1; i < nodecnt; ++i) {
            if (node[i]._numbers > max) {
                max = node[i]._numbers;
                temp = &node[i]._str;
            }
        }
        for (int i = 0; i < inputnum; ++i) {
            if (str[i] == *temp) {
                ++count;
            }
        }
        if (count > idx2) {
            out << *temp << '\n';
        }
        else if (nodecnt == 2 && (node[0]._numbers == node[1]._numbers) && node[1]._numbers > 1) {
            out << node[1]._str << '\n';
        }
        else {
            out << "NONE" << '\n';
        }
    }



    in.close();
    out.close();
    delete[] str;
    delete[] node;
    return 0;
}
