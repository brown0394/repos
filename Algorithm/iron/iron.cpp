#include <iostream>
#include <fstream>
#include <string>

class Weight {
public:

    class WeightStack {
    public:
        Weight* top;
        Weight* curr;

        WeightStack() :top(nullptr), curr(nullptr) {}
        int Push(int data);
        void Push(int data, int flag);
        int Get();
        int Pop();
        ~WeightStack();
    };
    int weight;
    Weight* down;
public:
    Weight() :weight(0), down(nullptr) {}
};


void Weight::WeightStack::Push(int data, int flag) {
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

int Weight::WeightStack::Push(int data) {
    Weight* newone = new Weight;
    newone->weight = data;
    int count = 0;
    if (top == nullptr) {
        top = newone;
    }
    else {
        if (top->weight < newone->weight) {
            newone->down = top;
            top = newone;
        }
        else {
            Weight* temp = top;
            count = 1;
            while (temp->down != nullptr) {
                if (temp->down->weight < newone->weight) {
                    break;
                }
                temp = temp->down;
                ++count;
            }
            newone->down = temp->down;
            temp->down = newone;
        }
    }
    curr = top;
    return count;
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

        NodeStack() :top(nullptr), curr(nullptr) {}
        void Push(Node* data, int count);
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

void Node::NodeStack::Push(Node* data, int count) {
    StackNode* newone = new StackNode;
    newone->loc = data;
    if (nullptr == top) {
        top = newone;
    }
    else {
        if (0 == count) {
            newone->down = top;
            top = newone;
        }
        else {
            Node::StackNode* temp = top;
            for (int i = 0; i < count - 1; ++i) {
                temp = temp->down;
            }
            newone->down = temp->down;
            temp->down = newone;
        }
    }
    curr = top;
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
    Node* alpharr[26];
    Node* apath[13];
    int  courselength;
    std::string course;
    int pathidx;

    Tree() :root(nullptr), alpharr{ nullptr }, apath{ nullptr }, course("\0"), courselength(0), pathidx(0){}
    void AddNode(char from, char to, int weight);
    void findCourse();
    void SettingCourse();
    std::string GetCourse();
    int GetCourseLength();
    void ArrangeData();
    ~Tree();
};

void Tree::ArrangeData() {

    root = alpharr[0];
    while (true) {
        if (root->children.curr == nullptr) {
            root->children.curr = root->children.top;
            break;
        }
        apath[pathidx++] = root->children.curr->loc;
        root->children.curr = root->children.curr->down;
    }
}

std::string Tree::GetCourse() {
    return course;
}
int Tree::GetCourseLength() {
    return courselength;
}

Tree::~Tree() {
    for (int i = 0; i < 26; ++i) {
        if (nullptr != alpharr[i]) {
            delete alpharr[i];
        }
    }
}

void Tree::AddNode(char from, char to, int weight) {
    int idx = 0;
    Node* parent;
    int idxfrom = (int)from - 97;
    int idxto = (int)to - 97;
    int count1 = 0, count2 = 0;
    if (nullptr == alpharr[idxfrom]) {
        Node* newone = new Node;
        newone->name = from;
        count1 = newone->weightStack.Push(weight);
        alpharr[idxfrom] = newone;
        parent = newone;
    }
    else {
        count1 = alpharr[idxfrom]->weightStack.Push(weight);
        parent = alpharr[idxfrom];
    }
    if (nullptr == alpharr[idxto]) {
        Node* newone = new Node;
        newone->name = to;
        count2 = newone->weightStack.Push(weight);
        alpharr[idxto] = newone;
    }
    else {
        count2 = alpharr[idxto]->weightStack.Push(weight);
    }
    parent->children.Push(alpharr[idxto], count1);
    alpharr[idxto]->children.Push(parent, count2);
}

void Tree::findCourse() {
    int total_length = 0, getnum = 0, length = 0;
    Node::NodeStack stack;
    Node* temp;
    bool visitTable[26]{ false };
    visitTable[0] = true;
    bool popped = false;
    Weight::WeightStack intstack;
    int linebest;
    char linebestchar = '\0';
    while (true) {
        if(root->children.curr != root->children.top){
            if(root->children.curr->down == nullptr || root->children.curr->down->down == nullptr){
                break;
            }
        }
        if (root->children.curr != nullptr && !course.empty() && course[course.size() - 1] == root->children.curr->loc->name) {
            root->children.Get();
            root->weightStack.Get();
        }
        total_length = root->weightStack.Get();
        if (total_length == -1) {
            break;
        }
        temp = root->children.Get();
        stack.Push(root);
        popped = false;
        linebest = total_length;
        linebestchar = '\0';
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
                else if (total_length >= courselength) {
                    std::string str = "";
                    Node* buf = stack.Get();
                    int count = 0;
                    bool first = true;
                    while (buf != nullptr) {
                        if (first) {
                            first = false;
                        }
                        else {
                            str = ' ' + str;
                        }
                        str = buf->name + str;
                        ++count;
                        buf = stack.Get();
                    }
                    if (total_length == courselength) {
                        if (count > length) {
                            length = count;
                            course = str;
                            linebestchar = str[str.size()-1];
                        }
                        else if (count == length && str < course) {
                            course = str;
                            linebestchar = str[str.size()-1];
                        }
                    }
                    else {
                        length = count;
                        course = str;
                        courselength = total_length;
                        linebestchar = str[str.size()-1];
                    }
                    linebest = total_length;
                    total_length -= intstack.Pop();
                    temp = stack.Pop();
                    popped = true;
                }
                else {
                    if(linebest < total_length){
                        linebestchar = stack.CheckName();
                        linebest = total_length;
                    }
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
            if (visitTable[apath[0]->name - 97] == true && temp->name != apath[0]->name) {
                int i = 1;
                for (; i < pathidx; ++i) {
                    if (visitTable[apath[i]->name - 97] == false || temp->name == apath[i]->name) {
                        break;
                    }
                }
                if (i == pathidx) {
                    visitTable[temp->name - 97] = false;
                    total_length -= intstack.Pop();
                    temp = stack.Pop();
                    popped = true;
                    continue;
                }
            }
            //check weights of children nodes
            if (temp->children.curr != nullptr) {
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
                total_length += getnum;
                stack.Push(temp);
                intstack.Push(getnum, 0);
                temp = temp->children.Get();
            }
        }
        if(root->children.curr != nullptr){
            Node::StackNode* searcher = root->children.curr;
            if(searcher->loc->name == linebestchar){
                root->children.curr = root->children.curr->down;
            }
            else{
                while(searcher->down != nullptr){
                    if(searcher->down->loc->name == linebestchar){
                         Node::StackNode* del = searcher->down;
                        searcher->down = searcher->down->down;
                        delete del;
                        break;
                    }
                    searcher = searcher->down;
                }
            }
        }
        if(root->children.curr == nullptr){
            break;
        }
    }
    if (course[course.size() - 1] < course[2]) {
        std::string str2 = "";
        for (int i = 2; i < course.size(); ++i) {
            str2 = course[i] + str2;
        }
        str2 = "a " + str2;
        course = str2;
    }
}

int main() {
    std::ifstream in("iron.inp");
    std::ofstream out("iron.out");
    int edge, vertex;
    char from, to;
    int weight;
    in >> vertex >> edge;
    Tree tree;
    for (int i = 0; i < edge; ++i) {
        in >> from >> to >> weight;
        tree.AddNode(from, to, weight);
    }

    if(edge < vertex){
        out << "NONE\n";
        return 0;
    }

    tree.ArrangeData();
    tree.findCourse();
    if (tree.courselength > 0) {
        out << tree.courselength << '\n' << tree.course << '\n';
    }
    else {
        out << "None\n";
    }

    in.close();
    out.close();

    return 0;
}