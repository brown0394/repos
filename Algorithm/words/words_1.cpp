#include <iostream>
#include <fstream>
#include <string>

class Node{
    friend class Linkedlist;
    friend class AlphaHash;
private:
    std::string _str;
    int _numbers;
    Node* _next;
public:
    Node():_str("\0"), _numbers(0), _next(nullptr){}
};
class Linkedlist{
private:
    Node* _head;
public:
    Linkedlist():_head(nullptr){}
    ~Linkedlist()
    {
        if(_head != nullptr){
            Node* temp;
            while(_head->_next != nullptr){
                temp = _head->_next;
                free(_head);
                _head = temp;
            }
            free(_head);
        }
    }

    void Head(std::string &str);
    void Add(std::string &str, Node*& node);
    void Search(std::string &str, int& most, Node*& mnode);
};
void Linkedlist::Head(std::string &str){
    _head = (Node*)malloc(sizeof(Node));
    _head->_str = str;
}
void Linkedlist::Add(std::string &str, Node*& node){
    Node* newone = (Node*)malloc(sizeof(Node));
    newone->_str = str;
    node->_next = newone;
}
void Linkedlist::Search(std::string &str, int& most, Node*& mnode){
    if(nullptr != _head){
        bool found = false;
        Node* temp = _head;
        while(temp->_next != nullptr){
            if(temp->_str == str){
                temp->_numbers += 1;
                if(temp->_numbers > most){
                    most = temp->_numbers;
                    mnode = temp;
                }
                found = true;
                break;
            }
            temp = temp->_next;
        }
        if(!found){
            if(temp->_str == str){
                temp->_numbers += 1;
                if(temp->_numbers > most){
                    most = temp->_numbers;
                    mnode = temp;
                }
                found = true;
            }
            else{
                Add(str, temp);
            }
        }
    }
    else{
        Head(str);
        _head->_numbers += 1;
    }
}
class AlphaHash{
private:
    Linkedlist _list[27];
    int _most;
    Node* _mnode;
public:
    AlphaHash():_most(0), _mnode(nullptr){}
    void Store(std::string str);
    std::string Frequent(int& n);
};
void AlphaHash::Store(std::string str){
    _list[str[0] - 97].Search(str, _most, _mnode);
}
std::string AlphaHash::Frequent(int& n){
    if(_most > (n/2)){
        return _mnode->_str;
    }
    return "NONE";
}
int main(){
    std::ifstream in("words.inp");
    std::ofstream out("words.out");

    int num_input;
    in >> num_input;
    std::string str;
    AlphaHash hash;
    for(int i = 0; i < num_input; ++i)
    {
        in >> str;
        hash.Store(str);
    }
    out << hash.Frequent(num_input) << '\n';

    in.close();
    out.close();

    return 0;
}