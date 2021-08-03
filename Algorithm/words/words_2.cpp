#include <iostream>
#include <fstream>
#include <string>

class Node {
    friend class Linkedlist;
    friend class AlphaHash;
private:
    std::string _str;
    int _numbers;
    Node* _next;
public:
    Node() :_str("\0"), _numbers(0), _next(nullptr) {}
};
class Linkedlist {
    friend class AlphaHash;
private:
    Node* _head;
public:
    Linkedlist() :_head(nullptr) {}
    ~Linkedlist()
    {
        if (_head != nullptr) {
            Node* temp;
            while (_head->_next != nullptr) {
                temp = _head->_next;
                delete _head;
                _head = temp;
            }
            delete _head;
        }
    }

    void Head(std::string& str);
    void Add(std::string& str, Node*& node);
    Node* Search(std::string& str, int& most);
};
void Linkedlist::Head(std::string& str) {
    _head = new Node;
    _head->_str = str;
    _head->_numbers = 1;
}
void Linkedlist::Add(std::string& str, Node*& node) {
    Node* newone = new Node;
    newone->_str = str;
    node->_next = newone;
    newone->_numbers = 1;
}
Node* Linkedlist::Search(std::string& str, int& most) {
    if (nullptr != _head) {
        bool found = false;
        Node* temp = _head;
        while (temp->_next != nullptr) {
            if (temp->_str == str) {
                temp->_numbers += 1;
                if(temp->_numbers > most){
                    return temp;
                }
                found = true;
                break;
            }
            temp = temp->_next;
        }
        if (!found) {
            if (temp->_str == str) {
                temp->_numbers += 1;
                if(temp->_numbers > most){
                    return temp;
                }
            }
            else {
                Add(str, temp);
            }
        }
    }
    else {
        Head(str);
    }
    return nullptr;
}
class AlphaHash {
private:
    Linkedlist _list[160];
    int _most;
    bool _found;
    Node* _mnode;
public:
    AlphaHash(int most) :_most(most), _found(false), _mnode(nullptr) {}
    bool Store(std::string& str);
    std::string Frequent();
};
bool AlphaHash::Store(std::string& str) {
    if(_mnode == nullptr){
        int size = str.size();
        int idx;
        if(size > 5){
            idx = ((int)str[0] - 97) + ((int)str[1] - 97) + ((int)str[2] - 97) + ((int)str[2] - 97)
            + ((int)str[3] - 97) + ((int)str[4] - 97);
        }
        else if(size > 4){
            idx = ((int)str[0] - 97) + ((int)str[1] - 97) + ((int)str[2] - 97) + ((int)str[2] - 97)
            + ((int)str[3] - 97);
        }
        else if(size > 3){
            idx = ((int)str[0] - 97) + ((int)str[1] - 97) + ((int)str[2] - 97) + ((int)str[2] - 97);
        }
        else if(size > 2){
            idx = ((int)str[0] - 97) + ((int)str[1] - 97) + ((int)str[2] - 97);
        }
        else if(size > 1){
            idx = ((int)str[0] - 97) + ((int)str[1] - 97);
        }
        else{
            idx = ((int)str[0] - 97);
        }

        _mnode = _list[idx].Search(str, _most);
        return false;
    }
    return true;
}
std::string AlphaHash::Frequent() {
    Node* temp;
    if (_mnode != nullptr) {
        return _mnode->_str;
    }
    return "NONE";
}
int main() {
    std::ifstream in("words.inp");
    std::ofstream out("words.out");

    int num_input;
    in >> num_input;
    std::string str;
    AlphaHash hash(num_input / 2);
    for (int i = 0; i < num_input; ++i)
    {
        in >> str;
        if(hash.Store(str)){
            break;
        }
    }
    out << hash.Frequent() << '\n';

    in.close();
    out.close();

    return 0;
}