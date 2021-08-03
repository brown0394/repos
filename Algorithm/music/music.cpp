#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Alignment {
private:
    int _match, _mismatch, _gap, _idx, _max;
    int _st1, _end1, _st2, _end2;
    std::string _str;
    std::string _str1, _str2;
    int** table;
public:
    Alignment(int match, int mismatch, int gap, int idx, std::string& str) :_match(match), _mismatch(mismatch), _gap(gap), _idx(idx), _str(str),
        _max(0), _st1(0), _end1(0), _st2(0), _end2(0){
        table = new int* [_idx];
        for (int i = 0; i < _idx; ++i) {
            table[i] = new int[_idx];
        }
    }
    ~Alignment() {
        delete[] table;
    }

    void GlCalcScore(int str1begin, int str2begin);
    void CalcScore(int str1begin, int str2begin);
    int Max();
    void GetString(std::string& str1, std::string& str2);
    void TraceBack(int str1begin, int str2begin, int st1end, int st2end, bool change);
    void DrawTable(int str1begin, int str2begin, int st1end, int st2end);
};

void Alignment::DrawTable(int str1begin, int str2begin, int st1end, int st2end) {
    std::cout << '\t';
    for (int i = str2begin; i <= st2end; ++i) {
        std::cout << '\t' << _str[i];
    }
    std::cout << '\n';
    for (int i = 0; i <= st1end; ++i) {
        if (i == 0) {
            std::cout << ' ';
        }
        else {
            std::cout << _str[i - 1 + str2begin];
        }
        for (int j = 0; j <= st2end - str2begin; ++j) {
            std::cout << '\t' << table[i][j];
        }
        std::cout << '\n';
    }
    std::cout << "\n\n\n";

}

void Alignment::GetString(std::string& str1, std::string& str2) {
    str1 = _str1;
    str2 = _str2;
}

int Alignment::Max() {
    return _max;
}

void Alignment::TraceBack(int str1begin, int str2begin, int st1end, int st2end, bool change) {
    std::string str1 = "";
    std::string str2 = "";
    int last1 = st1end - 1, last2 = st2end - 1;
    str1 = _str[st1end - 1] + str1;
    str2 = _str[st2end - 1] + str2;
    std::vector<int> savepoint1, savepoint2, point;
    std::vector<std::string> checkpoint1, checkpoint2;
    while (true) {
        if ((st1end - 1 - str1begin > 0 && st2end - 1 - str2begin > 0) &&
            (table[st1end - str1begin - 1][st2end - str2begin - 1] >= 0) &&
                 ((table[st1end - str1begin - 1][st2end - str2begin - 1] == table[st1end - str1begin][st2end - str2begin] - _match ||
                    table[st1end - str1begin - 1][st2end - str2begin - 1] == table[st1end - str1begin][st2end - str2begin] - _mismatch))) {
                    --st1end;
                    --st2end;
                    str1 = _str[st1end - 1] + str1;
                    str2 = _str[st2end - 1] + str2;
            
        }
        else if ((st2end - str2begin - 1 > 0) &&
             (table[st1end - str1begin][st2end - str2begin - 1] >= 0 && table[st1end - str1begin][st2end - str2begin - 1] == table[st1end - str1begin][st2end - str2begin] - _gap)) {
            if ((st1end - str1begin - 1 > 0) 
            && (table[st1end - str1begin - 1][st2end - str2begin] >= 0 && table[st1end - str1begin - 1][st2end - str2begin] == table[st1end - str1begin][st2end - str2begin] - _gap)) {
                savepoint1.push_back(st1end);
                savepoint2.push_back(st2end);
                checkpoint1.push_back(str1);
                checkpoint2.push_back(str2);
                point.push_back(1);
            }
            --st2end;
            str2 = _str[st2end - 1] + str2;
        }
        else if ((st1end - str1begin - 1 > 0) 
            && (table[st1end - str1begin - 1][st2end - str2begin] >= 0 && table[st1end - str1begin - 1][st2end - str2begin] == table[st1end - str1begin][st2end - str2begin] - _gap)) {
            if ((st2end - str2begin - 1 > 0) &&
            (table[st1end - str1begin][st2end - str2begin - 1] >= 0 && table[st1end - str1begin][st2end - str2begin - 1] == table[st1end - str1begin][st2end - str2begin] - _gap)) {
                savepoint1.push_back(st1end);
                savepoint2.push_back(st2end);
                checkpoint1.push_back(str1);
                checkpoint2.push_back(str2);
                point.push_back(2);            
            }
            --st1end;
            str1 = _str[st1end - 1] + str1;
        }
        else if(!savepoint1.empty()){
            st1end = savepoint1.back();
            savepoint1.pop_back();
            st2end = savepoint2.back();
            savepoint2.pop_back();
            str1 = checkpoint1.back();
            checkpoint1.pop_back();
            str2 = checkpoint2.back();
            checkpoint2.pop_back();
            if(point.back() == 2){
                --st2end;
                str2 = _str[st2end - 1] + str2;
            }
            else{
                --st1end;
                str1 = _str[st1end - 1] + str1;
            }
            point.pop_back();
        }

        if (table[st1end - str1begin][st2end - str2begin] == _match) {
            if(table[st1end - str1begin - 1][st2end - str2begin - 1] == 0 && table[st1end - str1begin - 1][st2end - str2begin] == _gap &&
            table[st1end - str1begin][st2end - str2begin - 1] == _gap){
                break;
            }
        }
    }

    if(_st1 == 0 || change){
        _st1 = st1end - 1;
        _st2 = st2end - 1;
        _end1 = last1;
        _end2 = last2;
        _str1 = str1;
        _str2 = str2;
    }
    else if(_st1 >= st1end - 1){
        if((_end1 >= last1 && _end2 > last2) || (_end1 > last1 && _end2 >= last2)){
            _str1 = str1;
            _str2 = str2;
        }
        if(_st2 > st2end - 1){
            _str1 = str1;
            _str2 = str2;            
        }
        
    }

}


void Alignment::GlCalcScore(int str1begin, int str2begin) {
    int mscore, a, b, c, maxcount = 0, max = 0;
    int incredown = 1, increright = 1;
    int i = str1begin, j = str2begin;
    int min = 1 << (sizeof(int) * 8) - 1;
    bool right = true, down = false, change = false, zero = true, downincremax = false, rightincremax = false;
    int loc1, loc2;
    while (true) {
        if (i - str1begin > 0 && j - str2begin > 0) {
            if (_str[i - 1] == _str[j - 1]) {
                mscore = _match;
            }
            else {
                mscore = _mismatch;
            }
        }

        if (i - str1begin == 0 || j - str2begin == 0) {
            a = min;
            b = min;
            c = min;
            if (i - str1begin == 0 && j - str2begin == 0) {
                a = 0;
            }
            else if (j - str2begin == 0) {
                b = table[i - str1begin - 1][j - str2begin] + _gap;
            }
            else if (i - str1begin == 0) {
                c = table[i - str1begin][j - str2begin - 1] + _gap;
            }
        }
        else {
            a = table[i - str1begin - 1][j - str2begin - 1] + mscore;
            b = table[i - str1begin][j - str2begin - 1] + _gap;
            c = table[i - str1begin - 1][j - str2begin] + _gap;
        }
        if (a >= b && a >= c) {
            table[i - str1begin][j - str2begin] = a;
        }
        else if (b >= a && b >= c) {
            table[i - str1begin][j - str2begin] = b;
        }
        else if (c >= a && c >= b) {
            table[i - str1begin][j - str2begin] = c;
        }
        if (max < table[i - str1begin][j - str2begin]) {
            max = table[i - str1begin][j - str2begin];
            change = true;
            maxcount = 0;
            loc1 = i;
            loc2 = j;
        }

        if (table[i - str1begin][j - str2begin] > 0) {
            zero = false;
        }

        if (i - str1begin == incredown && j - str2begin == increright) {
            if (incredown + str1begin < str2begin) {
                ++incredown;
            }
            else {
                downincremax = true;
            }
            if (increright + str2begin < _idx) {
                ++increright;
            }
            else {
                rightincremax = true;
            }
            if (downincremax && rightincremax) {
                break;
            }
            if (!rightincremax) {
                right = true;
                down = false;
                i = str1begin;
            }
            else {
                right = false;
                down = true;
            }


            if (change) {
                change = false;
            }
            else {
                ++maxcount;
                if (maxcount > 6) {
                    break;
                }
            }
            if (zero) {
                break;
            }
            else {
                zero = true;
            }
        }
        else if (j - str2begin == increright) {
            right = false;
            down = true;
        }
        else if (i - str1begin == incredown) {
            right = true;
            down = false;
        }
        if (right) {
            ++j;
        }
        if (down) {
            if (downincremax) {
                ++i;
            }
            else {
                if (i - str1begin + 1 == incredown) {
                    right = true;
                    down = false;
                    j = str2begin;
                }
                ++i;
            }
        }
    }


    if (max > _max) {
        _max = max;
        TraceBack(str1begin, str2begin, loc1, loc2, true);
        //DrawTable(str1begin, str2begin, loc1, loc2);
    }
    else if(max == _max){
        TraceBack(str1begin, str2begin, loc1, loc2, false);
    }
}

int main() {
    std::ifstream in("music.inp");
    std::ofstream out("music.out");
    int match, mismatch, gap, count, cntend;
    in >> match >> mismatch >> gap;
    std::string str;
    in >> str;
    std::string str1, str2;
    int idx = str.size();
    Alignment align(match, mismatch, gap, idx, str);
    for (int i = 0; i < idx - 1; ++i) {
        count = 1;
        for (int j = i + 1; j < idx; ++j) {
            if (str[i] == str[j] && j - i - (count - 1) == 1) {
                ++count;
                cntend = j;
            }
            else if (str[i] == str[j] && j - i > 1 && idx - j > 1) {
                align.GlCalcScore(i, j);
            }
        }
        if (count > 2) {
            count = count / 2;
            if (align.Max() < count * match) {
                align.GlCalcScore(i, i + count);
            }
        }
    }

    align.GetString(str1, str2);
    out << str1 << '\n' << str2 << '\n';
    out << align.Max() << '\n';

    in.close();
    out.close();
}