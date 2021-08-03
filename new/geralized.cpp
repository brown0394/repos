#include <iostream>



class GenListNode
{
    friend class GenList;
private:
    bool _flag;
    GenListNode* _next;
    union{
        DataType _data;
        GenListNode* _dlink;
    };
};

class GenList
{
private:
    GenListNode* _head;

public:
    GenList():_head(NULL){}
    void AddNode(int data, bool flag);
};

void GenList::AddNode(int data, bool flag)
{
    GenListNode* newone = new GenListNode;
    if(flag == true)
    {
        
    }
}

int main()
{


}