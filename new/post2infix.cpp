#include <iostream>
#include <string>


typedef char DataType;

class Node
{
    friend class Stack;
public:
    Node():next(NULL), data(0){}
    Node(DataType p_data)
    {
        data = p_data;
    }
private:
    DataType data;
    Node *next;

};


class Stack
{
private:
    Node *top;
public:
    Stack(): top(NULL){}
    ~Stack();
    void push(DataType data);
    bool IsEmpty();
    DataType pop();
};
bool Stack::IsEmpty()
{
    if(top == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }

}
void Stack::push(DataType data)
{
    Node *newnode = new Node(data);
    newnode->next = top;
    top = newnode;
}

DataType Stack::pop()
{
    DataType temp = top->data;
    Node *removed = top;
    top = top->next;
    delete removed;
    return temp;
}

Stack::~Stack()
{
    if(top != NULL)
    {
        if(top->next != NULL)
        {
            Node* temp = top;
            while(top->next != NULL)
            {
                top = top->next;
                delete temp;
                temp = top;
            }
            delete top;
        }
    }

}



class BinaryTree
{
public:
    class TreeNode
    {
        friend class BinaryTree;
    private:
        TreeNode* _leftC;
        TreeNode* _rightC;
        DataType _data;
    public:
        TreeNode(DataType d, TreeNode* l = NULL, TreeNode* r = NULL):_leftC(l), _rightC(r), _data(d){}
    };

    BinaryTree():_root(NULL){}
    ~BinaryTree();
    void BurnTree(TreeNode* child);
    bool IsEmpty();
    TreeNode* AddNode(DataType data, Stack &st, TreeNode* l=NULL, TreeNode* r=NULL)
    {
        TreeNode* newone = new TreeNode(data);
        if(IsEmpty())
        {
            _root = newone;
        }

        if(CheckOp(data))
        {
            if(!st.IsEmpty())
            {
                char temp = st.pop();
                newone->_rightC = AddNode(temp, st);
                if(!st.IsEmpty())
                {
                    temp = st.pop();
                    newone->_leftC = AddNode(temp, st);
                }
            }
        }
        return newone;
    }
    void PlantTree(Stack &st);
    void Print();
    void PrintTree(TreeNode* node)
    {
        if(CheckOp(node->_data))
        {
            std::cout<<'(';
        }
        if(node->_leftC != NULL)
        {
            PrintTree(node->_leftC);
        }
        std::cout << node->_data;
        if(node->_rightC != NULL)
        {
            PrintTree(node->_rightC);
        }
        if(CheckOp(node->_data))
        {
            std::cout<<')';
        }
    }
    bool CheckOp(char val);
private:
    TreeNode* _root;
};

bool BinaryTree::IsEmpty()
{
    if(NULL == _root)
    {
        return true;
    }
    return false;
}

BinaryTree::~BinaryTree()
{
    if(!IsEmpty())
    {
        BurnTree(_root);
    }
}
void BinaryTree::BurnTree(TreeNode* child)
{
    if(child->_leftC != NULL)
    {
        BurnTree(child->_leftC);
    }
    if(child->_rightC != NULL)
    {
        BurnTree(child->_rightC);
    }
    delete child;
}

bool BinaryTree::CheckOp(char val)
{
    if(val == '+' || val == '-' || val == '*' || val == '/')
    {
        return true;
    }
    return false;
}

void BinaryTree::PlantTree(Stack &st)
{
    char temp = st.pop();
    AddNode(temp, st);
}

void BinaryTree::Print()
{
    PrintTree(_root);
}

int main()
{
    char input;
    int num = 0;
    Stack st;
    BinaryTree tree;
    std::cin >> num;

    for(int i = 0; i < num; ++i)
    {
        std::cin >> input;
        st.push(input);
    }
    tree.PlantTree(st);
    tree.Print();
}
