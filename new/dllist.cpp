#include <iostream>

typedef char element;

class TreeNode
{
    friend class Tree;
private:
    element _data;
    TreeNode* _leftc;
    TreeNode* _rightc;

public:
    TreeNode():_data(0), _leftc(NULL), _rightc(NULL){}
};

class Tree
{
private:
    TreeNode* _root;

public:
    Tree():_root(NULL){}

    
};