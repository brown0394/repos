#include <iostream>
#include <string>

typedef std::string element;

class BST
{
    element data;
    BST *ltree, *rtree;
    bool _isfirst;
    static BST *root;
    static int curloc;
    static int depth;
    int _level;
public:
    BST(){}
    BST(const element d, BST *l=NULL, BST *r=NULL, const int lev=0, const bool is=true): data(d), ltree(l), rtree(r), _level(lev), _isfirst(is){}
    static void Insert(element d)
    {
        root = root->Insert(root, d);
    }
    BST* Insert(BST *tree, element d);
    static std::ostream& Print(int level, std::ostream &out=std::cout)
    {
        if(level < 2)
        {
            out << root->data;
            return out;
        }
        return root->Print(root, level, out);
    }

    std::ostream& Space(std::ostream &out)
    {
        if(_isfirst)
            _isfirst = false;
        else
        {
            out << ' ';
        }    
        return out; 
    }

    std::ostream& PrintLeaves(BST *tree, int level, std::ostream &out)
    {
        if(level > depth)
        {
            if(tree->ltree == NULL && tree->rtree == NULL)
            {
                Space(out);
                out << tree->data;
            }
        }
        return out;
    }

    std::ostream& Print(BST *tree, int level, std::ostream &out)
    {
        if(level < 2)
            level = 1;
        ++_level;
        if(tree)
        {
            if(_level == level)
            {
                Space(out);
                out << tree->data;
            }
            else
            {
                PrintLeaves(tree, level, out);
                Print(tree->ltree, level, out);
                Print(tree->rtree, level, out);
            }           
        }
        --_level;
        return out;
    }
};

BST* BST::Insert(BST *tree, const element d)
{
    ++curloc;
    if(tree == NULL)
    {
        if(depth < curloc)
        {
            depth = curloc;
        }
        --curloc;
        return new BST(d);
    }
    if(d > tree->data)
    {
        tree->rtree = Insert(tree->rtree, d);
    }
    else
    {
        tree->ltree = Insert(tree->ltree, d);
    }
    --curloc;
    return tree;
}

BST *BST::root = nullptr;
int BST::curloc = 0;
int BST::depth = 0;
int main(void)
{
    int num, level;
    BST tree;
    std::cin >> num;
    element* input = new element[num];
    for(int i = 0; i < num; ++i)
    {
        std::cin >> input[i];
        tree.Insert(input[i]);
    }
    std::cin >> level;
    tree.Print(level);

    delete[] input;
    return 0;
}
