#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Point {
    int x;
    int y;
};

class Node {
public:
    int dfsNum;
    int backNum;
    int chk;
    Point point;
    bool to_target;
    Node* next[4];
    Node() :dfsNum(-1), backNum(-1), chk(0), next{ nullptr }, to_target(false){}
};

class Graph {
public:
    Node* start;
    Node* target;
    std::vector <Node*> stack;
    Graph() :start(nullptr), target(nullptr) {}

    int Search(std::vector<Point>& ans);
};

int Graph::Search(std::vector<Point>& ans) {
    Node* temp = start;
    temp->dfsNum = 0;
    int count = 0;
    int dfs = 0;
    int lastbacknum = -1;
    int lastdfs = 0;
    target->to_target = true;
    bool reachtarget = false;
    while (true) {
        if (temp == target) {
            int a = 10;
        }
        if (temp == start) {
            if (start->chk == 4) {
                break;
            }
        }
        else {
            if (temp->to_target && temp->dfsNum != lastdfs && temp != target) {
                lastdfs = temp->dfsNum;
                if (temp->dfsNum == lastbacknum) {
                    ++count;
                    if (ans.empty()) {
                        ans.push_back(temp->point);
                    }
                    else {
                        bool change = false;
                        for (int i = 0; i < ans.size(); ++i) {
                            if (ans[i].x > temp->point.x) {
                                ans.insert(ans.begin() + i, temp->point);
                                change = true;
                                break;
                            }
                            else if (ans[i].x == temp->point.x) {
                                if (ans[i].y > temp->point.y) {
                                    ans.insert(ans.begin() + i, temp->point);
                                    change = true;
                                    break;
                                }
                            }
                        }
                        if (!change) {
                            ans.push_back(temp->point);
                        }
                    }
                }
                else if (temp->dfsNum < lastbacknum) {
                    ++count;
                    lastbacknum = temp->dfsNum;
                    if (ans.empty()) {
                        ans.push_back(temp->point);
                    }
                    else {
                        bool change = false;
                        for (int i = 0; i < ans.size(); ++i) {
                            if (ans[i].x > temp->point.x) {
                                ans.insert(ans.begin() + i, temp->point);
                                change = true;
                                break;
                            }
                            else if (ans[i].x == temp->point.x) {
                                if (ans[i].y > temp->point.y) {
                                    ans.insert(ans.begin() + i, temp->point);
                                    change = true;
                                    break;
                                }
                            }
                        }
                        if (!change) {
                            ans.push_back(temp->point);
                        }
                    }
                }
            }
        }
        if (temp->chk == 4) {
            int backnum = 9999;
            for (int i = 0; i < 4; ++i) {
                if (temp->next[i] != nullptr && temp->next[i] != stack.back()) {
                    if (temp->next[i]->dfsNum < backnum) {
                        if (temp->next[i]->backNum != -1 && temp->next[i]->backNum < backnum) {
                            backnum = temp->next[i]->backNum;
                        }
                        else {
                            backnum = temp->next[i]->dfsNum;
                        }
                    }
                    if (temp->next[i]->to_target) {
                        temp->to_target = true;
                    }
                }
            }
            if (backnum == 9999) {
                if (lastbacknum != -1 && lastbacknum < temp->dfsNum) {
                    temp->backNum = lastbacknum;
                }
                else {
                    temp->backNum = temp->dfsNum;
                    lastbacknum = temp->dfsNum;
                }
            }
            else {
                if (lastbacknum != -1 && lastbacknum < backnum) {
                    temp->backNum = lastbacknum;
                }
                else if (backnum < temp->dfsNum) {
                    temp->backNum = backnum;
                    lastbacknum = backnum;
                }
                else {
                    temp->backNum = temp->dfsNum;
                    lastbacknum = temp->dfsNum;
                }
            }
            if (temp->to_target) {
                stack.back()->to_target = true;
            }
            temp = stack.back();
            stack.pop_back();
            continue;
        }
        if (temp->next[temp->chk] != nullptr) {
            if (temp->next[temp->chk]->dfsNum == -1) {
                int to = temp->chk;
                ++temp->chk;
                stack.push_back(temp);
                temp = temp->next[to];
                temp->dfsNum = ++dfs;
                lastbacknum = -1;
                continue;
            }
        }
        ++temp->chk;
    }
    return count;
}

int main() {
    std::ifstream in("1.inp");
    std::ofstream out("lock.out");
    int row, col;
    in >> row >> col;
    std::string* starr = new std::string[row];
    Node** nodearr = new Node * [row];
    for (int i = 0; i < row; ++i) {
        in >> starr[i];
        nodearr[i] = new Node[col];
    }
    Graph graph;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (starr[i][j] != '#') {
                if (starr[i][j] == 'S') {
                    graph.start = &nodearr[i][j];
                }
                else if (starr[i][j] == 'T') {
                    graph.target = &nodearr[i][j];
                }
                if (i - 1 > -1 && starr[i - 1][j] != '#') {
                    nodearr[i][j].next[0] = &nodearr[i - 1][j];
                }
                if (i + 1 < row && starr[i + 1][j] != '#') {
                    nodearr[i][j].next[1] = &nodearr[i + 1][j];
                }
                if (j - 1 > -1 && starr[i][j - 1] != '#') {
                    nodearr[i][j].next[2] = &nodearr[i][j - 1];
                }
                if (j + 1 < col && starr[i][j + 1] != '#') {
                    nodearr[i][j].next[3] = &nodearr[i][j + 1];
                }
                nodearr[i][j].point.x =  j+1;
                nodearr[i][j].point.y = row - i;
            }
        }
    }
    std::vector<Point> ans;
    out << graph.Search(ans) << '\n';
    for (int i = 0; i < ans.size(); ++i) {
        out << ans[i].x << ' ' << ans[i].y << '\n';
    }
    in.close();
    out.close();


    delete []starr;
    for (int i = 0; i < row; ++i) {
        delete[] nodearr[i];
    }
    delete[] nodearr;
    return 0;
}   
