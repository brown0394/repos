#include <iostream>
#include <fstream>
#include <string>

static const int FULLKM = 42;

class Weight {
public:

    class WeightStack {
    public:
        Weight* top;
        Weight* curr;

        WeightStack() :top(nullptr), curr(nullptr) {}
        void Push(int data);
        int Get();
        int Pop();
        ~WeightStack();
    };
    int weight;
    Weight* down;
public:
    Weight() :weight(0), down(nullptr) {}
};

void Weight::WeightStack::Push(int data) {
    Weight* newone = new Weight;
    newone->weight = data;
    if (top == nullptr) {
        top = newone;
    }
    else {
        newone->down = top;
        top = newone;
    }
    curr = top;
}

int Weight::WeightStack::Get() {
    if (top != nullptr) {
        if (curr == nullptr) {
            curr = top;
            return -1;
        }
        int ret = curr->weight;
        curr = curr->down;
        return ret;
    }
    return -1;
}

int Weight::WeightStack::Pop() {
    if (top != nullptr) {
        int ret = top->weight;
        Weight* temp = top;
        top = top->down;
        delete temp;
        return ret;
    }
    return -1;
}

Weight::WeightStack::~WeightStack() {
    if (nullptr != top) {
        Weight* temp = top->down;
        while (temp != nullptr) {
            delete top;
            top = temp;
            temp = temp->down;
        }
        delete top;
    }
}

class Node {
public:

    class StackNode {
    public:
        Node* loc;
        StackNode* down;
        StackNode() :loc(nullptr), down(nullptr) {}
    };
    class NodeStack {
    public:
        StackNode* top;
        StackNode* curr;

        NodeStack() :top(nullptr) {}
        void Push(Node* data);
        Node* Pop();
        Node* Get();
        char CheckName();
        ~NodeStack();
    };

    char name;
    NodeStack children;
    Weight::WeightStack weightStack;
    Node() :name('\0') {}
};

char Node::NodeStack::CheckName() {
    return curr->loc->name;
}

Node::NodeStack::~NodeStack() {
    if (nullptr != top) {
        StackNode* temp = top->down;
        while (temp != nullptr) {
            delete top;
            top = temp;
            temp = temp->down;
        }
        delete top;
    }
}

void Node::NodeStack::Push(Node* data) {
    StackNode* newone = new StackNode;
    newone->loc = data;
    if (nullptr == top) {
        top = newone;
    }
    else {
        newone->down = top;
        top = newone;
    }
    curr = top;
}

Node* Node::NodeStack::Pop() {
    if (top != nullptr) {
        Node* ret = top->loc;
        StackNode* temp = top;
        top = top->down;
        curr = curr->down;
        delete temp;
        return ret;
    }
    return nullptr;
}

Node* Node::NodeStack::Get() {
    if (top != nullptr) {
        if (curr == nullptr) {
            curr = top;
            return nullptr;
        }
        Node* ret = curr->loc;
        curr = curr->down;
        return ret;
    }
    return nullptr;
}

class Tree {
public:
    Node* root;
    Node* temporal;
    Node* alpharr[26];
    int max_weight, length;
    std::string course;

    Tree() :root(nullptr), temporal(nullptr), alpharr{ nullptr }, max_weight(0), course("\0"), length(0){}
    void SetmWeight(int weight) {
        max_weight = weight;
    }
    void AddNode(char from, char to, int weight);
    void findCourse();
    std::string GetCourse();
    int GetCourseLength();
    ~Tree();
};

std::string Tree::GetCourse() {
    return course;
}
int Tree::GetCourseLength() {
    return length;
}

Tree::~Tree() {
    for (int i = 0; i < 26; ++i) {
        if (nullptr != alpharr[i]) {
            delete alpharr[i];
        }
    }
}

void Tree::AddNode(char from, char to, int weight) {
    Node* parent;
    int idxfrom = (int)from - 97;
    int idxto = (int)to - 97;

    if (nullptr == alpharr[idxfrom]) {
        Node* newone = new Node;
        newone->name = from;
        newone->weightStack.Push(weight);
        alpharr[idxfrom] = newone;
        parent = newone;
    }
    else {
        alpharr[idxfrom]->weightStack.Push(weight);
        parent = alpharr[idxfrom];
    }
    if (nullptr == alpharr[idxto]) {
        Node* newone = new Node;
        newone->name = to;
        newone->weightStack.Push(weight);
        alpharr[idxto] = newone;
    }
    else {
        alpharr[idxto]->weightStack.Push(weight);
    }
    parent->children.Push(alpharr[idxto]);
    alpharr[idxto]->children.Push(parent);
    if ('a' == from) {
        root = alpharr[idxfrom];
    }

}

void Tree::findCourse() {
    int total_length = 0, getnum = 0;
    Node::NodeStack stack;
    Node* temp;
    bool visitTable[26]{ false };
    visitTable[0] = true;
    bool popped = false;
    Weight::WeightStack intstack;
    while (true) {
        total_length = root->weightStack.Get();
        if (total_length == -1) {
            break;
        }
        temp = root->children.Get();
        stack.Push(root);
        popped = false;
        while (true) {
            if (temp == nullptr) {
                total_length -= intstack.Pop();
                temp = stack.Pop();
                popped = true;
                continue;
            }
            if (temp->name == 'a') {
                if (popped) {
                    break;
                }
                else if (total_length == FULLKM) {
                    std::string str = "";
                    Node* buf = stack.Get();
                    int count = 0;
                    bool first = true;
                    while (buf != nullptr) {
                        if(first){
                            first = false;
                        }
                        else{
                            str = ' ' + str;
                        }
                        str = buf->name + str;
                        ++count;
                        buf = stack.Get();
                    }
                    if (count > length) {
                        length = count;
                        course = str;
                    }
                    else if (count == length && str < course) {
                        course = str;
                    }
                    total_length -= intstack.Pop();
                    temp = stack.Pop();
                    popped = true;
                }
                else {
                    total_length -= intstack.Pop();
                    temp = stack.Pop();
                    popped = true;
                }
            }
            if (visitTable[temp->name - 97] && !popped) {
                total_length -= intstack.Pop();
                temp = stack.Pop();
                popped = true;
                continue;
            }
            else {
                visitTable[temp->name - 97] = true;
                popped = false;
            }
            //check weights of children nodes
            if (temp->children.curr != nullptr){
                if (temp->children.CheckName() == stack.CheckName()) {
                    temp->children.Get();
                    temp->weightStack.Get();
                }
            }
            else {
                temp->children.Get();
            }
            getnum = temp->weightStack.Get();
            if (getnum == -1) {//means have no child left. so go back.
                visitTable[temp->name - 97] = false;
                temp = stack.Pop();
                popped = true;
                total_length -= intstack.Pop();
                continue;
            }
            else {//means it have child node.
                bool nochild = false;
                while (true) {
                    total_length += getnum;
                    if (total_length > FULLKM ||total_length + max_weight > FULLKM) {
                        if ((total_length == 42 && temp->children.CheckName() == 'a')) {
                            break;
                        }
                        temp->children.Get();
                        total_length -= getnum;
                        if (temp->children.curr != nullptr) {
                            if (temp->children.CheckName() == stack.CheckName()) {
                                temp->children.Get();
                                temp->weightStack.Get();
                            }
                        }
                        getnum = temp->weightStack.Get();
                        if (getnum == -1) {
                            nochild = true;
                            temp->children.Get();
                            break;
                        }
                    }
                    else {
                        break;
                    }
                }
                if (nochild) {
                    visitTable[temp->name - 97] = false;
                    temp = stack.Pop();
                    popped = true;
                    total_length -= intstack.Pop();
                    continue;
                }
                stack.Push(temp);
                intstack.Push(getnum);
                temp = temp->children.Get();
            }
        }
    }
}

int main() {
    std::ifstream in("marathon.inp");
    std::ofstream out("marathon.out");
    int edge, vertex;
    char from, to;
    int weight;
    in >> vertex >> edge;

    Tree tree;
    for (int i = 0; i < edge; ++i) {
        in >> from >> to >> weight;
        if (i == 0) {
            tree.SetmWeight(weight);
        }
        else {
            if (weight < tree.max_weight) {
                tree.SetmWeight(weight);
            }
        }
        tree.AddNode(from, to, weight);
    }
    tree.findCourse();
    out << tree.length << std::endl << tree.course << std::endl;
    in.close();
    out.close();

    return 0;
}