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
    bool ans;
    Point point;
    Node* next[4];
    Node() :dfsNum(-1), backNum(-1), chk(0), next{ nullptr }, ans(false){}
};

/*

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
}*/


int main() {
    std::ifstream in("lock.inp");
    std::ofstream out("lock.out");
    int row, col;
    in >> row >> col;
    std::string* starr = new std::string[row];
    Node** nodearr = new Node * [row];
    for (int i = 0; i < row; ++i) {
        in >> starr[i];
        nodearr[i] = new Node[col];
    }
    Node** nodearr2 = new Node * [row];
    for (int i = 0; i < row; ++i) {
        in >> starr[i];
        nodearr2[i] = new Node[col];
    }
    Node* start = nullptr;
    Node* target = nullptr;
    Node* start2 = nullptr;
    Node* target2 = nullptr;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (starr[i][j] != '#') {
                if (starr[i][j] == 'S') {
                    start = &nodearr[i][j];
                    start2 = &nodearr2[i][j];
                }
                else if (starr[i][j] == 'T') {
                    target = &nodearr[i][j];
                    target2 = &nodearr2[i][j];
                }
                if (i - 1 > -1 && starr[i - 1][j] != '#') {
                    nodearr[i][j].next[0] = &nodearr[i - 1][j];
                    nodearr2[i][j].next[0] = &nodearr2[i - 1][j];
                }
                if (i + 1 < row && starr[i + 1][j] != '#') {
                    nodearr[i][j].next[1] = &nodearr[i + 1][j];
                    nodearr2[i][j].next[1] = &nodearr2[i + 1][j];
                }
                if (j - 1 > -1 && starr[i][j - 1] != '#') {
                    nodearr[i][j].next[2] = &nodearr[i][j - 1];
                    nodearr2[i][j].next[2] = &nodearr2[i][j - 1];
                }
                if (j + 1 < col && starr[i][j + 1] != '#') {
                    nodearr[i][j].next[3] = &nodearr[i][j + 1];
                    nodearr2[i][j].next[3] = &nodearr2[i][j + 1];
                }
                nodearr[i][j].point.x = j + 1;
                nodearr[i][j].point.y = row - i;
                nodearr2[i][j].point.x = j + 1;
                nodearr2[i][j].point.y = row - i;
            }
        }
    }
    std::vector<Point> ans;
    std::vector <Node*> stack;
    std::vector <Node*> stack2;

    bool** nodvisitTable = new bool* [row];
    for (int i = 0; i < row; ++i) {
        in >> starr[i];
        nodvisitTable[i] = new bool[col];
        for (int j = 0; j < col; ++j) {
            nodvisitTable[i][j] = false;
        }
    }
    

    Node* temp = start2;
    int count = 0;
    int dfs = 0;
    int lastbacknum = -1;
    int lastdfs = 0;
    nodvisitTable[row - temp->point.y][temp->point.x - 1] = true;
    bool dvided = true;
    while (true) {
        if (temp == start2) {
            if (start2->chk == 4) {
                break;
            }
        }
        if (temp == target2) {
            dvided = false;
            break;
        }
        if (temp->chk == 4) {
            temp = stack2.back();
            stack2.pop_back();
            continue;
        }
        if (temp->next[temp->chk] != nullptr) {
            if (!nodvisitTable[row - temp->next[temp->chk]->point.y][temp->next[temp->chk]->point.x - 1]) {
                int to = temp->chk;
                ++temp->chk;
                stack2.push_back(temp);
                temp = temp->next[to];
                nodvisitTable[row - temp->point.y][temp->point.x - 1] = true;
                continue;
            }
        }
        ++temp->chk;
    }
    if (!dvided) {
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                nodearr2[i][j].chk = 0;
                nodvisitTable[i][j] = false;
            }
        }
        stack2.clear();
        temp = start;
        temp->dfsNum = 0;
        while (true) {
            if (temp == start) {
                if (start->chk == 4) {
                    break;
                }
            }
            if (temp->chk == 4) {
                int backnum = 9999;
                int doub = 0;
                bool anschk = false;
                for (int i = 0; i < 4; ++i) {
                    if (temp->next[i] != nullptr && temp->next[i] != stack.back()) {
                        if (temp->next[i]->dfsNum < backnum || temp->next[i]->backNum < backnum) {
                            if (temp->next[i]->backNum != -1 && temp->next[i]->backNum < backnum) {
                                backnum = temp->next[i]->backNum;
                            }
                            else {
                                backnum = temp->next[i]->dfsNum;
                            }
                        }
                        if (temp->next[i]->backNum == temp->dfsNum) {
                            ++doub;
                        }
                        if (temp->next[i]->ans) {
                            anschk = true;
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
                if (temp != start && temp != target) {
                    Node* curr = start2;
                    dvided = true;
                    nodvisitTable[row - temp->point.y][temp->point.x - 1] = true;
                    nodvisitTable[row - curr->point.y][curr->point.x - 1] = true;
                    while (true) {
                        if (curr == start2) {
                            if (start2->chk == 4) {
                                break;
                            }
                        }
                        if (curr == target2) {
                            dvided = false;
                            break;
                        }
                        if (curr->chk == 4) {
                            curr = stack2.back();
                            stack2.pop_back();
                            continue;
                        }
                        if (curr->next[curr->chk] != nullptr) {
                            if (!nodvisitTable[row - curr->next[curr->chk]->point.y][curr->next[curr->chk]->point.x - 1]) {
                                int to = curr->chk;
                                ++curr->chk;
                                stack2.push_back(curr);
                                curr = curr->next[to];
                                nodvisitTable[row - curr->point.y][curr->point.x - 1] = true;
                                continue;
                            }
                        }
                        ++curr->chk;
                    }
                    for (int i = 0; i < row; ++i) {
                        for (int j = 0; j < col; ++j) {
                            nodearr2[i][j].chk = 0;
                            nodvisitTable[i][j] = false;
                        }
                    }
                    stack2.clear();
                    if (dvided) {
                        ++count;
                        temp->ans = true;
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
    }





    out << count << '\n';
    for (int i = 0; i < ans.size(); ++i) {
        out << ans[i].x << ' ' << ans[i].y << '\n';
    }
    in.close();
    out.close();


    delete[]starr;
    for (int i = 0; i < row; ++i) {
        delete[] nodearr[i];
    }
    delete[] nodearr;
    return 0;
}