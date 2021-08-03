#include <fstream>
#include <iostream>
#include <string>

class Node
{
public:
    std::string str;
    Node* next;
    Node() : next(nullptr) {}
};

class ArrNode
{
public:
    Node* next;
    Node* last;
    int amount;
    ArrNode() : amount(0), next(nullptr), last(nullptr) {}
    ~ArrNode();
    void AddNode(std::string& str);
    void AddNode(Node* node);
    void Nullfy();
};

ArrNode::~ArrNode()
{
    if (nullptr != next)
    {
        Node* temp = next->next;
        while (temp != nullptr)
        {
            delete next;
            next = temp;
            temp = temp->next;
        }
        delete next;
    }
}

void ArrNode::Nullfy()
{
    this->next = nullptr;
    this->last = nullptr;
    amount = 0;
}

void ArrNode::AddNode(std::string& str)
{
    Node* newone = new Node;
    newone->str = str;
    ++this->amount;
    if (nullptr == last)
    {

        this->next = newone;
        this->last = newone;
    }
    else
    {
        this->last->next = newone;
        this->last = newone;
    }
}

void ArrNode::AddNode(Node* node)
{
    ++this->amount;
    if (nullptr == last)
    {
        this->next = node;
        this->last = node;
    }
    else
    {
        this->last->next = node;
        this->last = node;
    }
}

int main()
{
    std::ifstream inFile;
    inFile.open("1.inp");
    if (!inFile.is_open())
        exit(1);
   // char buf[1024];
    std::ofstream out("read.out");
    std::string st1;
    ArrNode node1[6], nodearr[2][6];
/*
    while (!inFile.getline(buf, sizeof(buf)).eof())
    {
        st1 = buf;
        switch (buf[0]) {
        case 'a': {node1[1].AddNode(st1); break; }
        case 'c': {node1[2].AddNode(st1); break; }
        case 'g': {node1[3].AddNode(st1); break; }
        case 'n': {node1[5].AddNode(st1); break; }
        case 't': {node1[4].AddNode(st1); break; }
        }
    }
    st1 = buf;
    switch (buf[0]) {
    case 'a': {node1[1].AddNode(st1); break; }
    case 'c': {node1[2].AddNode(st1); break; }
    case 'g': {node1[3].AddNode(st1); break; }
    case 'n': {node1[5].AddNode(st1); break; }
    case 't': {node1[4].AddNode(st1); break; }
    }*/
    while (!inFile.eof())
    {
        inFile >> st1;
        switch (st1[0]) {
        case 'a': {node1[1].AddNode(st1); break; }
        case 'c': {node1[2].AddNode(st1); break; }
        case 'g': {node1[3].AddNode(st1); break; }
        case 'n': {node1[5].AddNode(st1); break; }
        case 't': {node1[4].AddNode(st1); break; }
        }
    }
    inFile.close();
    int num[5]{ node1[0].amount + node1[1].amount + node1[2].amount + node1[3].amount + node1[4].amount + node1[5].amount, num[0] / 5, num[1] * 2, num[1] * 3, num[1] * 4 };
    int base = 0;
    int nthstep = 1;
    int nodeidx = 0, arrturn = 0;
    Node* temp = nullptr, * lastnode = nullptr, * nextnode = nullptr;
    ArrNode* arrtemp = nullptr, * lastemp = nullptr;
    for (int step = 1; step < 5; ++step)
    {
        lastnode = nullptr;
        nextnode = nullptr;
        nthstep = 1;
        if (node1[1].amount > num[step])
        {
            base = -1;
            nodeidx = 1;
        }
        else if (node1[1].amount + node1[2].amount > num[step]) {
            base = node1[1].amount - 1;
            nodeidx = 2;
        }
        else if (node1[1].amount + node1[2].amount + node1[3].amount > num[step])
        {
            base = node1[1].amount + node1[2].amount - 1;
            nodeidx = 3;
        }
        else if(node1[1].amount + node1[2].amount + node1[3].amount + node1[4].amount > num[step])
        {
            base = node1[1].amount + node1[2].amount + node1[3].amount - 1;
            nodeidx = 4;
        }
        else {
            base = node1[1].amount + node1[2].amount + node1[3].amount + node1[4].amount - 1;
            nodeidx = 5;
        }
        temp = node1[nodeidx].next;

        while (temp != nullptr) {
            if (temp->str.size() - 1 >= 1)
            {
                switch (temp->str[nthstep]) {
                case 'a': {nodearr[arrturn][1].AddNode(temp); break; }
                case 'c': {nodearr[arrturn][2].AddNode(temp); break; }
                case 'g': {nodearr[arrturn][3].AddNode(temp); break; }
                case 'n': {nodearr[arrturn][5].AddNode(temp); break; }
                case 't': {nodearr[arrturn][4].AddNode(temp); break; }
                }
            }
            else
            {
                nodearr[arrturn][0].AddNode(temp);
            }
            temp = temp->next;
        }
        int a = 1;
        arrtemp = &nodearr[arrturn][0];
        while (arrtemp->next == nullptr) {
            arrtemp = &nodearr[arrturn][a++];
        }
        node1[nodeidx].next = arrtemp->next;
        node1[nodeidx].last = arrtemp->last;
        for (; a < 6; ++a) {
            if (nodearr[arrturn][a].next != nullptr) {
                node1[nodeidx].last->next = nodearr[arrturn][a].next;
                node1[nodeidx].last = nodearr[arrturn][a].last;
            }
        }
        node1[nodeidx].last->next = nullptr;
        arrtemp = nullptr;
        ++nthstep;
        lastemp = &node1[nodeidx];

        while (true)
        {
            if (base + nodearr[arrturn][0].amount >= num[step]) {
                nodeidx = 0;
                Node* temp = nodearr[arrturn][0].next;
                for (int i = 0; i < nodearr[arrturn][0].amount; ++i) {
                    if (i + base + 1 == num[step]) {
                        out << temp->str << '\n';
                        break;
                    }
                    temp = temp->next;
                }
                for (int i = 0; i < 6; ++i) {
                    nodearr[arrturn][i].Nullfy();
                }
                break;
            }
            else if (base + nodearr[arrturn][0].amount + nodearr[arrturn][1].amount >= num[step]) {
                nodeidx = 1;
                base += nodearr[arrturn][0].amount;
            }
            else if (base + nodearr[arrturn][0].amount + nodearr[arrturn][1].amount + nodearr[arrturn][2].amount >= num[step]) {
                nodeidx = 2;
                base += nodearr[arrturn][0].amount + nodearr[arrturn][1].amount;
            }
            else if (base + nodearr[arrturn][0].amount + nodearr[arrturn][1].amount + nodearr[arrturn][2].amount + nodearr[arrturn][3].amount >= num[step]) {
                nodeidx = 3;
                base += nodearr[arrturn][0].amount + nodearr[arrturn][1].amount + nodearr[arrturn][2].amount;
            }
            else if (base + nodearr[arrturn][0].amount + nodearr[arrturn][1].amount + nodearr[arrturn][2].amount + nodearr[arrturn][3].amount + nodearr[arrturn][4].amount>= num[step]) {
                nodeidx = 4;
                base += nodearr[arrturn][0].amount + nodearr[arrturn][1].amount + nodearr[arrturn][2].amount + nodearr[arrturn][3].amount;
            }
            else {
                nodeidx = 5;
                base += nodearr[arrturn][0].amount + nodearr[arrturn][1].amount + nodearr[arrturn][2].amount + nodearr[arrturn][3].amount + nodearr[arrturn][4].amount;
            }
            for (int j = nodeidx - 1; j > -1; --j) {
                if (nodearr[arrturn][j].next != nullptr) {
                    lastnode = nodearr[arrturn][j].last;
                    break;
                }
            }
            temp = nodearr[arrturn][nodeidx].next;
            int lasturn = arrturn;
            for (int j = nodeidx + 1; j < 6; ++j) {
                if (nodearr[arrturn][j].next != nullptr) {
                    nextnode = nodearr[arrturn][j].next;
                    break;
                }
            }
            arrturn = (arrturn + 1) % 2;
            for (int i = 0; i < nodearr[lasturn][nodeidx].amount; ++i) {
                if (temp->str.size() - 1 >= nthstep)
                {
                    switch (temp->str[nthstep]) {
                    case 'a': {nodearr[arrturn][1].AddNode(temp); break; }
                    case 'c': {nodearr[arrturn][2].AddNode(temp); break; }
                    case 'g': {nodearr[arrturn][3].AddNode(temp); break; }
                    case 'n': {nodearr[arrturn][5].AddNode(temp); break; }
                    case 't': {nodearr[arrturn][4].AddNode(temp); break; }
                    }
                }
                else
                {
                    nodearr[arrturn][0].AddNode(temp);
                }
                temp = temp->next;
            }
            int a = 1;//연결 재정리 작업 필요.
            arrtemp = &nodearr[arrturn][0];
            while (arrtemp->next == nullptr) {
                arrtemp = &nodearr[arrturn][a++];
            }
            if (lastnode != nullptr) {
                lastnode->next = arrtemp->next;
            }
            else {
                lastemp->next = arrtemp->next;
                lastemp = nullptr;
            }
            nodearr[lasturn][nodeidx].next = arrtemp->next;//////
            nodearr[lasturn][nodeidx].last = arrtemp->last;
            for (; a < 6; ++a) {
                if (nodearr[arrturn][a].next != nullptr) {
                    nodearr[lasturn][nodeidx].last->next = nodearr[arrturn][a].next;
                    nodearr[lasturn][nodeidx].last = nodearr[arrturn][a].last;
                }
            }
            nodearr[lasturn][nodeidx].last->next = nextnode;
            arrtemp = nullptr;
            ++nthstep;
            for (int i = 0; i < 6; ++i) {
                nodearr[lasturn][i].Nullfy();
            }
        }
    }

    out.close();
}