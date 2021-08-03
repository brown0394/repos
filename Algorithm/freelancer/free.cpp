#include <fstream>
#include <iostream>

class Data {
public:
    int begin;
    int end;
    int cost;
    Data() :begin(0), end(0), cost(0) {}
    void operator=(const Data& other) {
        this->begin = other.begin;
        this->end = other.end;
        this->cost = other.cost;
    }
};

class Schedule {
public:
    Data data;
    Schedule* next;
    Schedule() :next(nullptr) {}
};

class TreeNode {
public:
    TreeNode* child;
    TreeNode* brother;
    Data data;
    int days;
    TreeNode() :child(nullptr), brother(nullptr), days(0) {}
};

class Tree {
public:
    TreeNode root;
    int maxday;
    int maxcost;
    Tree() :maxday(0), maxcost(0) {}
    ~Tree();
public:
    void AddNode(Data& newdata);
    void TraverseAdd(Data& newdata, TreeNode*& curr, int& precost, int& predate);
    void DeleteAll(TreeNode*& curr);
};

void Tree::DeleteAll(TreeNode*& curr) {
    if (curr->child == nullptr) {
        if (curr->brother == nullptr) {
            delete curr;
            return;
        }
        else {
            DeleteAll(curr->brother);
        }
    }
    else {
        if (curr->brother != nullptr) {
            DeleteAll(curr->brother);
            DeleteAll(curr->child);
        }
        else {
            DeleteAll(curr->child);
        }
    }
    delete curr;
}

Tree::~Tree() {
    if (root.child != nullptr) {
        DeleteAll(root.child);
    }
    if (root.brother != nullptr) {
        DeleteAll(root.brother);
    }
}

void Tree::TraverseAdd(Data& newdata, TreeNode*& curr, int& precost, int& predate) {
    if (curr->data.end < newdata.begin) {
        if (curr->child == nullptr) {
            TreeNode* newone = new TreeNode;
            newone->data.begin = newdata.begin;
            newone->data.end = newdata.end;
            newone->data.cost = curr->data.cost + newdata.cost - 10;
            newone->days = newone->data.end - newone->data.begin + 1 + curr->days;
            curr->child = newone;
            if (maxcost < newone->data.cost) {
                maxcost = newone->data.cost;
                maxday = newone->days;
            }
            else if(maxcost == newone->data.cost){
                if(maxday > newone->days){
                    maxday = newone->days;
                }
            }
        }
        else {
            TraverseAdd(newdata, curr->child, curr->data.cost, curr->days);
        }
        if (curr->brother != nullptr) {
            TraverseAdd(newdata, curr->brother, precost, predate);
        }
        else {
            return;
        }
    }
    else if (curr->data.begin <= newdata.begin && curr->data.end >= newdata.begin) {
        if (curr->brother == nullptr) {
            TreeNode* newone = new TreeNode;
            newone->data.begin = newdata.begin;
            newone->data.end = newdata.end;
            newone->data.cost = precost + newdata.cost - 10;
            newone->days = newone->data.end - newone->data.begin + 1 + predate;
            curr->brother = newone;
            if (maxcost < newone->data.cost) {
                maxcost = newone->data.cost;
                maxday = newone->days;
            }
            else if(maxcost == newone->data.cost){
                if(maxday > newone->days){
                    maxday = newone->days;
                }
            }
            return;
        }
        else {
            TraverseAdd(newdata, curr->brother, precost, predate);
        }
    }
}

void Tree::AddNode(Data& newdata) {
    if (root.data.begin == 0) {
        root.data = newdata;
        root.days = newdata.end - newdata.begin + 1;
        maxcost = newdata.cost;
        maxday = root.days;
    }
    else {
        bool child = false;
        if (root.brother != nullptr) {
            if (root.data.end < newdata.begin) {
                child = true;
                if (root.child == nullptr) {
                    TreeNode* newone = new TreeNode;
                    newone->data = newdata;
                    newone->days = newone->data.end - newone->data.begin + 1;
                    root.child = newone;
                    root.child->days += root.days;
                    root.child->data.cost += root.data.cost - 10;
                    if (maxcost < root.child->data.cost) {
                        maxcost = root.child->data.cost;
                        maxday = root.child->days;
                    }
                    else if(maxcost == root.child->data.cost){
                        if(maxday > root.child->days){
                            maxday = root.child->days;
                        }
                    }
                }
                else {
                    TraverseAdd(newdata, root.child, root.data.cost, root.days);
                }
            }
            TreeNode* temp = root.brother;
            while (true) {
                if (newdata.begin > temp->data.end) {
                    if (temp->child == nullptr) {
                        TreeNode* newone = new TreeNode;
                        newone->data = newdata;
                        newone->days = newone->data.end - newone->data.begin + 1;
                        temp->child = newone;
                        temp->child->days += temp->days;
                        temp->child->data.cost += temp->data.cost - 10;
                        if (maxcost < temp->child->data.cost) {
                            maxcost = temp->child->data.cost;
                            maxday = temp->child->days;
                        }
                        else if(maxcost == temp->child->data.cost){
                            if(maxday > temp->child->days){
                                maxday = temp->child->days;
                            }
                        }
                    }
                    else {
                        TraverseAdd(newdata, temp->child, temp->data.cost, temp->days);
                    }
                    child = true;
                }
                if (temp->brother == nullptr) {
                    break;
                }
                temp = temp->brother;
            }
            if (!child) {
                TreeNode* newone = new TreeNode;
                newone->data = newdata;
                newone->days = newone->data.end - newone->data.begin + 1;
                temp->brother = newone;
                if (maxcost < newone->data.cost) {
                    maxcost = newone->data.cost;
                    maxday = newone->days;
                }
                else if(maxcost == newone->data.cost){
                    if(maxday > newone->days){
                        maxday = newone->days;
                    }
                }                
            }
        }
        else {
            if (root.data.end < newdata.begin) {
                if (root.child == nullptr) {
                    TreeNode* newone = new TreeNode;
                    newone->data = newdata;
                    newone->days = newone->data.end - newone->data.begin + 1;
                    root.child = newone;
                    root.child->days += root.days;
                    root.child->data.cost += root.data.cost - 10;
                    if (maxcost < root.child->data.cost) {
                        maxcost = root.child->data.cost;
                        maxday = root.child->days;
                    }
                    else if(maxcost == root.child->data.cost){
                        if(maxday > root.child->days){
                            maxday = root.child->days;
                        }
                    }
                }
                else {
                    TraverseAdd(newdata, root.child, root.data.cost, root.days);
                }
            }
            else {
                TreeNode* newone = new TreeNode;
                newone->data = newdata;
                newone->days = newone->data.end - newone->data.begin + 1;
                root.brother = newone;
                if (newone->data.cost >= maxcost) {
                    maxcost = newone->data.cost;
                    maxday = newone->days;
                }
                else if(maxcost == newone->data.cost){
                    if(maxday > newone->days){
                        maxday = newone->days;
                    }
                }
            }
        }
    }
}

class ScHead {
public:
    Schedule* next;
    ScHead* down;
    int idx;
    ScHead() :next(nullptr), down(nullptr), idx(0) {}
};

class CalcJob {
public:
    ScHead head;
    Tree tree;

    void addSchedule(int begin, int end, int cost);
    void MakeTree();
    ~CalcJob();
};



void CalcJob::addSchedule(int begin, int end, int cost) {
    Schedule* newone = new Schedule;
    newone->data.begin = begin;
    newone->data.end = end;
    newone->data.cost = cost;
    if (head.down == nullptr)
    {
        ScHead* newhead = new ScHead;
        newhead->idx = begin;
        newhead->next = newone;
        head.down = newhead;
    }
    else
    {
        ScHead* temp = head.down;
        bool same = false, mid = false;
        while (temp->down != nullptr)
        {
            if (temp->idx == begin)
            {
                same = true;
                break;
            }
            else if (temp->down->idx > begin)
            {
                mid = true;
                break;
            }
            temp = temp->down;
        }
        if (same)
        {
            if (temp->next != nullptr)
            {
                Schedule* sctemp = temp->next;
                while (sctemp->next != nullptr)
                {
                    sctemp = sctemp->next;
                }
                sctemp->next = newone;
            }
            else {
                temp->next = newone;
            }
        }
        else if (mid)
        {
            ScHead* newhead = new ScHead;
            newhead->idx = begin;
            ScHead* tempdown = temp->down;
            temp->down = newhead;
            newhead->down = tempdown;
            newhead->next = newone;
        }
        else
        {
            ScHead* newhead = new ScHead;
            newhead->idx = begin;
            temp->down = newhead;
            newhead->next = newone;
        }
    }
}


CalcJob::~CalcJob() {
    if (head.down != nullptr) {
        ScHead* headtemp = head.down;
        ScHead* downtemp = nullptr;
        Schedule* nexttemp, * aftertemp;
        while (headtemp != nullptr) {
            downtemp = headtemp->down;
            nexttemp = headtemp->next;
            if (nexttemp->next != nullptr) {
                aftertemp = nexttemp->next;
                while (aftertemp != nullptr) {
                    delete nexttemp;
                    nexttemp = aftertemp;
                    aftertemp = aftertemp->next;
                }
            }
            delete nexttemp;
            delete headtemp;
            headtemp = downtemp;
            if (headtemp != nullptr) {
                headtemp = headtemp->down;
            }
        }
    }
}

void CalcJob::MakeTree() {
    if (head.down != nullptr) {
        ScHead* headtemp = head.down;
        Schedule* tempnext;
        while (headtemp != nullptr) {
            tempnext = headtemp->next;
            while (tempnext != nullptr) {
                tree.AddNode(tempnext->data);
                tempnext = tempnext->next;
            }
            headtemp = headtemp->down;
        }
    }
}

int main() {
    std::ifstream in("free.inp");
    std::ofstream out("free.out");
    int num;
    in >> num;
    Data schedulelist;
    CalcJob calc;

    for (int i = 0; i < num; ++i) {
        in >> schedulelist.begin >> schedulelist.end >> schedulelist.cost;
        calc.addSchedule(schedulelist.begin, schedulelist.end, schedulelist.cost);
    }

    calc.MakeTree();
    out << calc.tree.maxcost << ' ' << calc.tree.maxday << '\n';

    in.close();
    out.close();

    return 0;
}