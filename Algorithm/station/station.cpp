#include <cmath>
#include <iostream>
#include <fstream>

class Coord
{
public:
    float x;
    float y;
    float z;

    const void operator=(Coord& other)
    {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
    };
};

class Station
{
public:
    Coord A, B, C, D;
    Coord pt1, pt2, point;
    double low, mid, high, closest;
    char where;
    double Distance();
    double FindClose(Coord& _pt1);
    void Search();
    void Mid(Coord& one, Coord& two);
    void Gradient(double zaxis, Coord& one, Coord& two);
    void Closest(Coord& stpt);
};

void Station::Gradient(double zaxis, Coord& one, Coord& two)
{
    pt1.z = zaxis;
    double num = (zaxis - one.z) / (two.z - one.z);
    pt1.y = num * (two.y - one.y) + one.y;
    pt1.x = num * (two.x - one.x) + one.x;
}

void Station::Mid(Coord& one, Coord& two)
{
    pt2.x = (one.x + two.x) / 2;
    pt2.y = (one.y + two.y) / 2;
    pt2.z = (one.z + two.z) / 2;
}

double Station::Distance()
{
    return sqrt(pow(pt1.x - pt2.x, 2) + pow(pt1.y - pt2.y, 2) + pow(pt1.z - pt2.z, 2));
}

double Station::FindClose(Coord& _pt1)
{
    pt1 = _pt1;
    pt2 = C;
    low = Distance();
    pt2 = D;
    high = Distance();
    Mid(C, D);
    mid = Distance();

    if (low <= mid && low <= high)
    {
        closest = low;
        where = 'C';
    }
    else if (mid <= low && mid <= high)
    {
        closest = mid;
        where = 'M';
    }
    else
    {
        closest = high;
        where = 'D';
    }
    return closest;
}

void Station::Closest(Coord& stpt)
{
    int count = 1;
    double distance, temp, pttemp;
    switch (where)
    {
    case 'C':
    {
        point = C;
        break;
    }
    case 'M':
    {
        Mid(C, D);
        point = pt2;
        break;
    }
    case 'D':
    {
        point = D;
        break;
    }
    }
    bool lpd = false;
    pt2 = stpt;
    pt1 = point;
    distance = closest;
    pttemp = distance + 1;
    while (distance != pttemp)
    {
        pttemp = distance;
        if (point.z - count >= D.z)
        { //반대 최하단 보다 높으면
            Gradient(point.z - count, C, D);
            temp = Distance();
            if (temp < distance)
            {
                while (temp < distance)
                {
                    if (point.z - count < D.z)
                    {
                        break;
                    }
                    distance = temp;
                    ++count;
                    Gradient(point.z - count, C, D);
                    temp = Distance();
                }
            }
            --count;
            Gradient(point.z - count, C, D);
            count = 1;
        }
        if (pt2.z == pt1.z) {
            Gradient(point.z, C, D);
        }
        point = pt2;
        pt2 = pt1;
        if (point.z - count >= B.z)
        {
            Gradient(point.z - count, A, B);
            temp = Distance();
            if (temp < distance)
            {
                while (temp < distance)
                {
                    if (point.z - count < B.z)
                    {
                        break;
                    }
                    distance = temp;
                    ++count;
                    Gradient(point.z - count, A, B);
                    temp = Distance();
                }
                lpd = true;

            }
            --count;
            Gradient(point.z - count, A, B);
            temp = Distance();
            count = 1;
        }
        if (!lpd && point.z + count <= A.z)
        {
            Gradient(point.z + count, A, B);
            temp = Distance();
            if (temp < distance)
            {
                while (temp < distance)
                {
                    if (point.z + count > A.z)
                    {
                        break;
                    }
                    distance = temp;
                    ++count;
                    Gradient(point.z + count, A, B);
                    temp = Distance();
                }
            }
            --count;
            Gradient(point.z + count, A, B);
            temp = Distance();
            count = 1;
        }
        if (pt2.z == pt1.z) {
            Gradient(point.z, A, B);
        }
        point = pt2;
        pt2 = pt1;
        lpd = false;
        if (point.z + count <= C.z)
        {
            Gradient(point.z + count, C, D);
            temp = Distance();
            if (temp < distance)
            {
                while (temp < distance)
                {
                    if (point.z + count > C.z)
                    {
                        break;
                    }
                    distance = temp;
                    ++count;
                    Gradient(point.z + count, C, D);
                    temp = Distance();
                }
            }
            --count;
            Gradient(point.z + count, C, D);
            count = 1;
        }
        if (pt2.z == pt1.z) {
            Gradient(point.z, C, D);
        }
        point = pt2;
        pt2 = pt1;
        if (point.z - count >= B.z)
        {
            Gradient(point.z - count, A, B);
            temp = Distance();
            if (temp < distance)
            {
                while (temp < distance)
                {
                    if (point.z - count < B.z)
                    {
                        break;
                    }
                    distance = temp;
                    ++count;
                    Gradient(point.z - count, A, B);
                    temp = Distance();
                }
                lpd = true;
            }
            --count;
            Gradient(point.z - count, A, B);
            temp = Distance();
            count = 1;
        }
        if (!lpd && point.z + count <= A.z)
        {
            Gradient(point.z + count, A, B);
            temp = Distance();
            if (temp < distance)
            {
                while (temp < distance)
                {
                    if (point.z + count > A.z)
                    {
                        break;
                    }
                    distance = temp;
                    ++count;
                    Gradient(point.z + count, A, B);
                    temp = Distance();
                }
            }
            --count;
            Gradient(point.z + count, A, B);
            temp = Distance();
            count = 1;
        }
        if (pt2.z == pt1.z) {
            Gradient(point.z, A, B);
        }
        point = pt2;
        pt2 = pt1;
        lpd = false;
    }
    closest = distance;
}

void Station::Search()
{
    Coord mid;
    double temp1, temp2;
    char wh1, wh2;
    int num = 1;
    temp1 = FindClose(A);
    wh1 = where;
    Mid(A, B);
    mid = pt2;
    temp2 = FindClose(pt2);
    wh2 = where;
    if (temp1 > temp2)
    {
        temp1 = temp2;
        num = 2;
        wh1 = wh2;
    }
    temp2 = FindClose(B);
    wh2 = where;
    if (temp1 > temp2)
    {
        wh1 = wh2;
        num = 3;
        temp1 = temp2;
    }
    closest = temp1;
    where = wh1;
    switch (num)
    {
    case 1:
    {
        Closest(A);
        break;
    }
    case 2:
    {
        Closest(mid);
        break;
    }
    case 3:
        Closest(B);
        break;
    }
}

int main()
{
    std::ifstream in("station.inp");
    std::ofstream out("station.out");
    Station st;
    Coord temp1, temp2;

    in >> temp1.x >> temp1.y >> temp1.z;
    in >> temp2.x >> temp2.y >> temp2.z;
    if (temp1.z >= temp2.z)
    {
        st.A = temp1;
        st.B = temp2;
    }
    else
    {
        st.B = temp1;
        st.A = temp2;
    }

    in >> temp1.x >> temp1.y >> temp1.z;
    in >> temp2.x >> temp2.y >> temp2.z;
    if (temp1.z >= temp2.z)
    {
        st.C = temp1;
        st.D = temp2;
    }
    else
    {
        st.D = temp1;
        st.C = temp2;
    }
    st.Search();
    //양 끝단, 중간점

    int ans = st.closest;
    if(st.closest - ans > 0){
        ++ans;
    }

    out << ans << '\n';
    in.close();
    out.close();
    return 0;
}