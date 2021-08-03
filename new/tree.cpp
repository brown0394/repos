#include <iostream>

class TreeNode
{
    friend class BinaryTree;
private:
    TreeNode* _leftC;
    TreeNode* _rightC;
    int _data;
};

class BinaryTree
{
private:
    TreeNode* _root;

public:
    BinaryTree():_root(NULL){}
    ~BinaryTree();
    void BurnTree();
    bool IsEmpty(TreeNode* child);
    void AddNode(int data);

};

bool BinaryTree::isEmpty()
{
    if(NULL == _root)
    {
        return true;
    }
    return false;
}

BinaryTree::~BinaryTree()
{
    if(!isEmpty)
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

void BinaryTree::AddNode(int data)
{
    TreeNode* newone = new TreeNode;
    if(IsEmpty)
    {

    }
}

int main()
{


    return 0;
}