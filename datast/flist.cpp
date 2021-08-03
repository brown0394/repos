#include <iostream>
#include <cstring>

class Node
{
    friend class Que;
public:
    Node():_next(NULL), _data(0){}
    void *operator new(size_t size);
    void operator delete(void* p);
private:
    Node* _next;
    int _data;
    static Node* _avail;
    static Node* _avlast;
};

class Que
{
private:
    Node* _head;
    Node* _last;

public:
    Que()
    {
        _head = new Node;
        _head->_next = _head;
        _last = _head;
    }
    void Enque(int data);
    int Deque();
    bool IsEmpty();
    bool IsAvail();
    void destroy_avail();
    void print();
    ~Que();
};

    Node* Node:: _avail = NULL;
    Node* Node:: _avlast = NULL;

    void Que::Enque(int data)
    {
        Node* newone = new Node;
        if(IsEmpty())
        {
            _head->_next = newone;
            _last = newone;
        }
        else
        {
            _last->_next = newone;
            _last = newone;
          
        }
        _last->_data = data;
        _last->_next = _head;
        
    }
    int Que::Deque()
    {
        int ret = 0;
        if(IsEmpty())
        {
           std::cout << "Que is Empty" << std::endl;
        }
        else
        {
            Node* temp = _head->_next;
            _head->_next = temp->_next;
            ret = temp->_data;
            temp->_next = NULL;
            delete temp;         
        }
        return ret;
    }
    bool Que::IsEmpty()
    {
        if(_head->_next == _head)
        {
            return true;
        }
        return false;
    }
    bool Que::IsAvail()
    {
        if(Node::_avail != NULL)
        {
            return true;
        }
        return false;
    }
    Que::~Que()
    {
        if(!IsEmpty())
        {
            _last->_next = Node::_avail;
            Node::_avail = _head->_next;
        }
        delete _head;
    }

    void Que::destroy_avail()
    {
        if(IsAvail())
        {
            Node* temp1 = Node::_avail;
            Node* temp2 = Node::_avail->_next;
            while(temp2 != NULL)
            {
                free(temp1);
                temp1 = temp2;
                temp2 = temp2->_next;
            }
            free(temp1);
        }
        
    }
    void Que::print()
    {
        std::cout << "[queue:";
        if(!IsEmpty())
        {
            Node* temp = _head->_next;
            while(temp != _head)
            {
                std::cout << ' ' <<temp->_data;
                temp = temp->_next;
            }
        }
        std::cout << ']' << std::endl;
        std::cout << "[flist:";
        if(IsAvail())
        {
            Node* temp = Node::_avail;
            while(temp != NULL)
            {
                std::cout << ' ' <<temp->_data;
                temp = temp->_next;
            }
        }
        std::cout << ']' << std::endl;
    }
    void* Node::operator new(size_t size)
    {
        if(_avail != NULL)
        {
            Node* temp = _avail;
            _avail = _avail->_next;
            return temp;
        }
        else
        {
            Node* temp = (Node*)malloc(size);
            return temp;
        }
    }
    void Node::operator delete(void* p)
    {
        Node* temp = (Node*)p;
        if(_avail == NULL)
        {
            _avail = temp;
            _avlast = _avail;
        }
        else
        {
            _avlast->_next = temp;
            _avlast = temp;
        }
    }

void whichque(char *p, Que& que)
{  
    if(strcmp(p, "enqueue") == 0)
    {
        int number = 0; 
        std::cin >> number;
        que.Enque(number);
    }
    else
    {
        que.Deque();
    }
    
}

int main()
{
    Que list;
    int input = 0;
    char check[10] = {"\0"};
    std::cin >> input;

    for(int i = 0; i < input; ++i)
    {
        std::cin >> check;
        whichque(check, list);
        list.print();
    }
    list.destroy_avail();
}