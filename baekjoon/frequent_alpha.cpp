#include <iostream>
#include <string>

class Node
{
    friend class Linkedlist;
private:
    Node* _next;
    int _times;
    char _letter;
public:
    Node():_next(nullptr), _times(0), _letter('\0'){}
};

class Linkedlist
{
private:
    Node* _head;
public:
    Linkedlist()
    {
        _head = new Node;
    }
    ~Linkedlist()
    {
        Node* temp = _head->_next;

        while(temp != nullptr)
        {
            delete _head;
            _head = temp;
            temp = temp->_next;
        }
        delete _head;
    }
    void addNode(char letter, Node* node);
    void count(Node* node);
    void search(char letter);
};

void Linkedlist::search(char letter)
{
    Node* temp = _head->_next;

    while(temp != nullptr)
    {
        
    }
}

void Linkedlist::addNode(char letter, Node* node)
{
    Node* newone = new Node;
    newone->_letter = letter;
    Node* temp = node;
    while(temp->_next != nullptr)
    {
        temp = temp->_next;
    }

    temp->_next = newone;
}

void Linkedlist::count(Node* node)
{
    node->_times += 1;
}

int main()
{
    std::string str;
    std::cin >> str;


}