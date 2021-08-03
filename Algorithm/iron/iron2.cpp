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
        void Push(int data);
        int Get();
        int Pop();
        void Push(int data, bool sh);
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

        NodeStack() :top(nullptr), curr(nullptr) {}
        void Push(Node* data);
        Node* Pop();
        Node* Get();
        char CheckName();
        ~NodeStack();
    };
    class ShorteNode {
    public:
        std::string name;
        char to;
        ShorteNode* next;
        ShorteNode() :to('\0'), next(nullptr), name("") {}
    };
    class NodeShort {
    public:
        ShorteNode* top;
        NodeShort() :top(nullptr) {}
        int Push(char from, char to, char tobedel, Node* mid);
        void Pop();
        ~NodeShort();
    };

    char name;
    int shorten;
    NodeStack children;
    Weight::WeightStack weightStack;
    NodeShort nodeshort;
    Node() :name('\0'), shorten(0) {}
    void DecShort();
};

void Node::NodeShort::Pop() {
    if (nullptr != top) {
        ShorteNode* temp = top;
        top = top->next;
        delete temp;
    }
}

int Node::NodeShort::Push(char from, char to, char tobedel, Node* mid) {
    ShorteNode* newone = new ShorteNode;
    newone->to = to;
    if (nullptr == top) {
        if (mid->shorten > 0) {
            ShorteNode* temp = mid->nodeshort.top;
            for (int i = 0; i < mid->shorten; ++i) {
                if (temp->to == to) {
                    newone->name = temp->name;
                    newone->name = from + newone->name;
                    break;
                }
                temp = temp->next;
            }
            top = newone;
        }
        else {
            newone->name += from;
            newone->name += tobedel;
            newone->name += to;
            top = newone;
        }
    }
    else {
        ShorteNode* temp = top;
        if (temp->name[0] == from && temp->name[temp->name.size() - 1] == tobedel) {
            top = top->next;
            newone->name = temp->name;
            bool check = false;
            if (mid->shorten > 0) {
                ShorteNode* stemp = mid->nodeshort.top;
                for (int i = 0; i < mid->shorten; ++i) {
                    if (stemp->to == to) {
                        stemp->name.erase(0, 1);
                        newone->name += stemp->name;
                        check = true;
                        break;
                    }
                    stemp = stemp->next;
                }
            }
            if (!check) {
                newone->name += to;
            }
            delete temp;
            newone->next = top;
            top = newone;
            return 0;
        }
        else {
            while (temp->next != nullptr) {
                if (temp->next->name[0] == from && temp->next->name[temp->name.size()] == tobedel) {
                    break;
                }
                temp = temp->next;
            }
            if (nullptr == temp->next) {
                newone->name += from;
                newone->name += tobedel;
                newone->name += to;
                newone->next = top;
                top = newone;
            }
            else {
                newone->name = temp->next->name;
                bool check = false;
                if (mid->shorten > 0) {
                    ShorteNode* stemp = mid->nodeshort.top;
                    for (int i = 0; i < mid->shorten; ++i) {
                        if (stemp->to == to) {
                            stemp->name.erase(stemp->name[0]);
                            newone->name += stemp->name;
                            check = true;
                            break;
                        }
                        stemp = stemp->next;
                    }
                }
                if (!check) {
                    newone->name += to;
                }
                newone->next = temp->next->next;
                delete temp->next;
                temp->next = newone;
                return 0;
            }
        }
    }
    return 1;
}

Node::NodeShort::~NodeShort() {
    if (nullptr != top) {
        ShorteNode* temp = top->next;
        while (temp != nullptr) {
            delete top;
            top = temp;
            temp = temp->next;
        }
        delete top;
    }
}

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
    int max_weight, courselength;
    std::string course;

    Tree() :root(nullptr), temporal(nullptr), alpharr{ nullptr }, max_weight(0), course("\0"), courselength(0){}
    void SetmWeight(int weight) {
        max_weight = weight;
    }
    void AddNode(char from, char to, int weight);
    void findCourse();
    std::string GetCourse();
    int GetCourseLength();
    void ArrangeData();
    ~Tree();
};

void Tree::ArrangeData() {
    Node::StackNode* temp;
    Weight* wtemp;
    Node* ntemp;
    int idx;
    for (int i = 1; i < 26; ++i) {
        if (alpharr[i] != nullptr) {
            idx = i;
            while (true) {
                if (alpharr[idx]->children.top != nullptr && alpharr[idx]->children.top->down == nullptr) {
                    ntemp = alpharr[idx]->children.Get();
                    temp = ntemp->children.top;
                    wtemp = ntemp->weightStack.top;
                    Node::StackNode* a;
                    Weight* b;
                    if (temp->loc == alpharr[idx]) {
                        a = temp;
                        ntemp->children.top = temp->down;
                        b = wtemp;
                        ntemp->weightStack.top = wtemp->down;
                        delete a;
                        delete b;
                    }
                    else {
                        while (temp->down->loc != alpharr[idx]) {
                            temp = temp->down;
                            wtemp = wtemp->down;
                        }
                        a = temp->down;
                        b = wtemp->down;
                        temp->down = a->down;
                        wtemp->down = b->down;
                        delete b;
                        delete a;
                    }
                    delete alpharr[idx];
                    alpharr[idx] = nullptr;
                    ntemp->children.curr = ntemp->children.top;
                    ntemp->weightStack.curr = ntemp->weightStack.top;
                    if (ntemp->name == 'a') {
                        break;
                    }
                    idx = ntemp->name - 97;
                }
                else {
                    break;
                }
            }
        }
    }//이까지 끝.
    int weight1, weight2;
    for (int i = 1; i < 26; ++i) {
        if (alpharr[i] != nullptr && alpharr[i]->children.top != nullptr && alpharr[i]->children.top->down != nullptr) {
            if ((alpharr[i]->children.top->down->down == nullptr) && (alpharr[i]->children.top->loc->name != 'a') && (alpharr[i]->children.top->down->loc->name != 'a')) {
                ntemp = alpharr[i]->children.top->loc;
                Node* atemp = alpharr[i]->children.top->down->loc;
                Node::StackNode* search1 = ntemp->children.top;

                weight1 = alpharr[i]->weightStack.Pop();
                weight2 = alpharr[i]->weightStack.Pop();
                wtemp = ntemp->weightStack.top;
                if (search1->loc == alpharr[i]) {
                    ntemp->children.top = ntemp->children.top->down;
                    ntemp->children.curr = ntemp->children.top;
                    ntemp->weightStack.top = ntemp->weightStack.top->down;
                    ntemp->weightStack.curr = ntemp->weightStack.top;
                    delete search1;
                    weight2 += wtemp->weight;
                    delete wtemp;
                }
                else {
                    while (search1->down->loc != alpharr[i]) {//////////////////////////////////////////////////////////////////////
                        search1 = search1->down;
                        wtemp = wtemp->down;
                    }
                    Node::StackNode* del = search1->down;
                    search1->down = search1->down->down;
                    Weight* delw = wtemp->down;
                    wtemp->down = wtemp->down->down;
                    delete del;
                    weight2 += delw->weight;
                    delete delw;
                }
                search1 = atemp->children.top;
                wtemp = atemp->weightStack.top;
                if (search1->loc == alpharr[i]) {
                    atemp->children.top = atemp->children.top->down;
                    atemp->children.curr = atemp->children.top;
                    atemp->weightStack.top = atemp->weightStack.top->down;
                    atemp->weightStack.curr = atemp->weightStack.top;
                    delete search1;
                    weight1 += wtemp->weight;
                    delete wtemp;
                }
                else {
                    while (search1->down->loc != alpharr[i]) {
                        search1 = search1->down;
                        wtemp = wtemp->down;
                    }
                    Node::StackNode* del = search1->down;
                    search1->down = search1->down->down;
                    Weight* delw = wtemp->down;
                    wtemp->down = wtemp->down->down;
                    delete del;
                    weight1 += delw->weight;
                    delete delw;
                }

                atemp->shorten += atemp->nodeshort.Push(atemp->name, ntemp->name, alpharr[i]->name, alpharr[i]);
                ntemp->shorten += ntemp->nodeshort.Push(ntemp->name, atemp->name, alpharr[i]->name, alpharr[i]);


                atemp->children.Push(ntemp);
                atemp->weightStack.Push(weight2);
                ntemp->children.Push(atemp);
                ntemp->weightStack.Push(weight1);
                if (atemp->name != 'a' && ntemp->name != 'a') {
                    search1 = atemp->children.top;
                    wtemp = atemp->weightStack.top;
                    while (search1->down != nullptr) {
                        if (search1->down->loc->name == ntemp->name && wtemp->down->weight != weight2) {
                            if (wtemp->down->weight <= weight2) {
                                Node::StackNode* del = search1->down;
                                search1->down = search1->down->down;
                                delete del;
                                Weight* del2 = wtemp->down;
                                wtemp->down = wtemp->down->down;
                                delete del2;
                            }
                            else {
                                atemp->children.Pop();
                                atemp->weightStack.Pop();
                                if (atemp->shorten > 0) {
                                    --atemp->shorten;
                                }
                                atemp->nodeshort.Pop();
                            }
                            break;
                        }
                        search1 = search1->down;
                        wtemp = wtemp->down;
                    }
                    search1 = ntemp->children.top;
                    wtemp = ntemp->weightStack.top;

                    while (search1->down != nullptr) {
                        if (search1->down->loc->name == atemp->name && atemp->name != 'a' && wtemp->down->weight != weight1) {
                            if (wtemp->down->weight <= weight1) {
                                Node::StackNode* del = search1->down;
                                search1->down = search1->down->down;
                                delete del;
                                Weight* del2 = wtemp->down;
                                wtemp->down = wtemp->down->down;
                                delete del2;
                            }
                            else {
                                ntemp->children.Pop();
                                ntemp->weightStack.Pop();
                                if (ntemp->shorten > 0) {
                                    --ntemp->shorten;
                                }
                                ntemp->nodeshort.Pop();
                            }
                            break;
                        }
                        search1 = search1->down;
                        wtemp = wtemp->down;
                    }

                }
                delete alpharr[i];
                alpharr[i] = nullptr;
                i = 1;
            }
        }
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
    int total_length = 0, getnum = 0, length = 0;
    Node::NodeStack stack;
    Node* temp;
    bool visitTable[26]{ false };
    visitTable[0] = true;
    bool popped = false;
    Weight::WeightStack intstack;

    int checkcount = 0;
    if (alpharr[0] == nullptr) {
        return;
    }
    else if (alpharr[0]->children.top == nullptr) {
        return;
    }
    Node::StackNode* check = alpharr[0]->children.top;
    while (check != nullptr) {
        ++checkcount;
        check = check->down;
    }
    if (checkcount == 2) {
        check = alpharr[0]->children.top;
        if (check->loc->name < check->down->loc->name) {
            delete check->down;
            check->down = nullptr;
        }
        else {
            alpharr[0]->children.top = check->down;
            alpharr[0]->children.curr = alpharr[0]->children.top;
            delete check;
        }
    }

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
                else if (total_length >= courselength) {
                    std::string str = "";
                    Node* buf = stack.Get();
                    int count = 0;
                    bool first = true;
                    char lastchar = '\0';
                    bool got = false;
                    while (buf != nullptr) {
                        if (first) {
                            first = false;
                        }
                        else {
                            str = ' ' + str;
                        }
                        if (buf->shorten > 0) {
                            Node::ShorteNode* search = buf->nodeshort.top;
                            for (int i = 0; i < buf->shorten; ++i) {
                                if (search->to == lastchar) {
                                    bool f = true;
                                    for (int j = search->name.size() - 2; j >= 0; --j) {
                                        if (f) {
                                            f = false;
                                            str = search->name[j] + str;
                                            got = true;
                                        }
                                        else {
                                            str = ' ' + str;
                                            str = search->name[j] + str;
                                            got = true;
                                        }
                                    }
                                }
                                search = search->next;
                            }
                        }
                        if (!got) {
                            str = buf->name + str;
                        }
                        lastchar = buf->name;
                        ++count;
                        buf = stack.Get();
                        got = false;
                    }
                    if (total_length == courselength) {
                        if (count > length) {
                            length = count;
                            course = str;
                        }
                        else if (count == length && str < course) {
                            course = str;
                        }

                    }
                    else {
                        length = count;
                        course = str;
                        courselength = total_length;
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
            else {
                total_length += getnum;//temproaty
                stack.Push(temp);
                intstack.Push(getnum);
                temp = temp->children.Get();
            }
        }
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
        if (i == 0) {
            tree.SetmWeight(weight);
        }
        else {
            if (weight > tree.max_weight) {
                tree.SetmWeight(weight);
            }
        }
        tree.AddNode(from, to, weight);
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