#include <iostream>
#include <fstream>


class Point {
public:
    int _x;
    int _y;
    int _idx;
    Point* _next;
    Point* _prev;
    Point() :_x(0), _y(0), _idx(0), _next(nullptr), _prev(nullptr) {}
};

class DoubleLink {
public:
    Point* _header;
    DoubleLink() {
        _header = new Point;
        _header->_next = _header;
        _header->_prev = _header;
    }
    ~DoubleLink();
    void Add(int x, int y, int idx);
    void MoveForward(Point* pivot, Point* target);
    void MoveBackward(Point* pivot, Point* target);
    void Sort(Point* pivot, int start, int end);
    void Print(std::ofstream& os);
};

DoubleLink::~DoubleLink() {
    if (_header->_next != _header) {
        Point* temp = _header->_next;
        Point* next = temp->_next;
        while (temp != _header) {
            delete temp;
            temp = next;
            next = next->_next;
        }
    }
    delete _header;
}

void DoubleLink::Add(int x, int y, int idx) {
    Point* newone = new Point;
    newone->_x = x;
    newone->_y = y;
    newone->_idx = idx;
    if (_header == _header->_next) {
        _header->_next = newone;
        _header->_prev = newone;
        newone->_next = _header;
        newone->_prev = _header;
    }
    else {
        _header->_prev->_next = newone;
        newone->_prev = _header->_prev;
        newone->_next = _header;
        _header->_prev = newone;
    }
}

void DoubleLink::MoveForward(Point* pivot, Point* target) {
    target->_prev->_next = target->_next;
    target->_next->_prev = target->_prev;
    pivot->_prev->_next = target;
    target->_prev = pivot->_prev;
    target->_next = pivot;
    pivot->_prev = target;
}

void DoubleLink::MoveBackward(Point* pivot, Point* target) {
    target->_prev->_next = target->_next;
    target->_next->_prev = target->_prev;
    pivot->_next->_prev = target;
    target->_next = pivot->_next;
    pivot->_next = target;
    target->_prev = pivot;
}

void DoubleLink::Sort(Point* pivot, int start, int end) {
    if (_header->_next != _header) {
        if (nullptr == pivot) {
            pivot = _header->_next;
        }
        int forward = 0;
        int backward = 0;
        int sign = 0;
        Point* locpt = pivot->_next;
        Point* forpiv = nullptr;
        bool piv = true;
        for (int i = start; i < end-1; ++i) {
            sign = (locpt->_x * pivot->_y) - (pivot->_x * locpt->_y);
            if (0 == sign) {
                if (((locpt->_x * locpt->_x) + (locpt->_y * locpt->_y)) > ((pivot->_x * pivot->_x) + (pivot->_y * pivot->_y))) {
                    ++backward;
                    locpt = locpt->_next;
                }
                else {
                    Point* nextp = locpt->_next;
                    MoveForward(pivot, locpt);
                    ++forward;
                    if (piv) {
                        piv = false;
                        forpiv = locpt;
                    }
                    locpt = nextp;
                }
            }
            else if (sign < 0) {
                ++backward;
                locpt = locpt->_next;
            }
            else {
                Point* nextp = locpt->_next;
                MoveForward(pivot, locpt);
                ++forward;
                if (piv) {
                    piv = false;
                    forpiv = locpt;
                }
                locpt = nextp;
            }
        }
        if (forward == 0) {
            if (backward < 2) {
                return;
            }
            Sort(pivot->_next, start + 1, end);
        }
        else if (backward == 0) {
            if (forward < 2) {
                return;
            }
            Sort(forpiv, start, start + forward);
        }
        else {
            Sort(forpiv, start, start + forward);
            Sort(pivot->_next, start + forward, end-1);
        }
    }
}

void DoubleLink::Print(std::ofstream& os) {
    Point* temp = _header->_next;
    while (temp != _header) {
        os << temp->_idx << '\n';
        temp = temp->_next;
    }
}

int main() {
    std::ifstream in("angle.inp");
    std::ofstream out("angle.out");
    DoubleLink quadrant1;
    DoubleLink quadrant2;
    DoubleLink quadrant3;
    DoubleLink quadrant4;

    int num = 0;
    in >> num;
    int x = 0, y = 0;
    int one=0, two=0, three=0, four=0;
    for (int i = 0; i < num; ++i) {
        in >> x >> y;
        if (y >= 0) {
            if (x >= 0) {
                quadrant1.Add(x, y, i + 1);
                ++one;
            }
            else {
                quadrant2.Add(x, y, i + 1);
                ++two;
            }
        }
        else {
            if (x < 0) {
                quadrant3.Add(x, y, i + 1);
                ++three;
            }
            else {
                quadrant4.Add(x, y, i + 1);
                ++four;
            }
        }
    }

    quadrant1.Sort(nullptr, 0, one);
    quadrant2.Sort(nullptr, 0, two);
    quadrant3.Sort(nullptr, 0, three);
    quadrant4.Sort(nullptr, 0, four);

    quadrant1.Print(out);
    quadrant2.Print(out);
    quadrant3.Print(out);
    quadrant4.Print(out);

    in.close();
    out.close();
    return 0;
}