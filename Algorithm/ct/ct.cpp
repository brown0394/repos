#include <iostream>
#include <fstream>

int main() {
    std::ifstream in("ct.inp");
    std::ofstream out("ct.out");
    int size;
    in >> size;
    int vertical[size];
    int horizontal[size];
    int rdiagonal[size + size - 1];
    int ldiagonal[size + size - 1];

    char box[size][size]{'\0'};

    int verticalcount[size] {0};
    int horizontalcount[size] {0};
    int rdiagonalcount[size + size - 1]{ 0 };
    int ldiagonalcount[size + size - 1]{ 0 };

    int verticalTcount[size] {0};
    int horizontalTcount[size] {0};
    int rdiagonalTcount[size + size - 1]{ 0 };
    int ldiagonalTcount[size + size - 1]{ 0 };

    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            box[i][j] = '\0';
        }
    }

    for (int i = 0; i < size; ++i) {
        in >> vertical[i];
        if (vertical[i] == size) {
            for (int j = 0; j < size; ++j) {
                if (box[j][i] != 'B') {
                    box[j][i] = 'B';
                    ++horizontalcount[j];
                    ++rdiagonalcount[i + j];
                    ++ldiagonalcount[(size - (i + 1)) + j];
                }
            }
            vertical[i] = 0;
        }
        else if (vertical[i] == 0) {
            for (int j = 0; j < size; ++j) {
                if (box[j][i] != '-') {
                    box[j][i] = '-';
                    ++horizontalTcount[j];
                    ++rdiagonalTcount[i + j];
                    ++ldiagonalTcount[(size - (i + 1)) + j];
                }
            }
            vertical[i] = 0;
        }
    }
    for (int i = 0; i < size; ++i) {
        in >> horizontal[i];
        if (horizontal[i] == size) {
            for (int j = 0; j < size; ++j) {
                if (box[i][j] != 'B') {
                    box[i][j] = 'B';
                    ++verticalcount[j];
                    ++rdiagonalcount[i + j];
                    ++ldiagonalcount[(size-1+i) - j];
                }
            }
            horizontal[i] = 0;
        }
        else if (horizontal[i] == 0) {
            for (int j = 0; j < size; ++j) {
                if (box[i][j] != '-') {
                    box[i][j] = '-';
                    ++verticalTcount[j];
                    ++rdiagonalTcount[i + j];
                    ++ldiagonalTcount[(size - 1 + i) - j];
                }
            }
            horizontal[i] = 0;
        }
    }
    for (int i = 0; i < size + size - 1; ++i) {
        in >> ldiagonal[i];
        if (i < size) {
            int num = size - (1 + i);
            if (ldiagonal[i] == 0) {
                for (int j = 0; j < i + 1; ++j) {
                    if (box[j][num + j] != '-') {
                        box[j][num + j] = '-';
                        ++verticalTcount[size - (1 + i) + j];
                        ++horizontalTcount[j];
                        ++rdiagonalTcount[size - 1 - i + (2 * j)];
                    }
                }
                ldiagonal[i] = 0;
            }
            else if (ldiagonal[i] == i + 1) {
                for (int j = 0; j < i + 1; ++j) {
                    if (box[j][num + j] != 'B') {
                        box[j][num + j] = 'B';
                        ++verticalcount[size - (1 + i) + j];
                        ++horizontalcount[j];
                        ++rdiagonalcount[size - 1 - i + (2 * j)];
                    }
                }
                ldiagonal[i] = 0;
            }
        }
        else {
            int num = (i % size) + 1;
            if (ldiagonal[i] == 0) {
                for (int j = 0; j < size - num; ++j) {
                    if (box[num + j][j] != '-') {
                        box[num + j][j] = '-';
                        ++verticalTcount[j];
                        ++horizontalTcount[num + j];
                        ++rdiagonalTcount[num + (2 * j)];
                    }
                }
                ldiagonal[i] = 0;
            }
            else if (ldiagonal[i] == (size - num)) {
                for (int j = 0; j < size - num; ++j) {
                    if (box[num + j][j] != 'B') {
                        box[num + j][j] = 'B';
                        ++verticalcount[j];
                        ++horizontalcount[num + j];
                        ++rdiagonalcount[num + (2 * j)];
                    }
                }
                ldiagonal[i] = 0;
            }
        }
    }
    for (int i = 0; i < size + size - 1; ++i) {
        in >> rdiagonal[i];
        if (i < size) {
            if (rdiagonal[i] == 0) {
                for (int j = 0; j < i + 1; ++j) {
                    if (box[j][i - j] != '-') {
                        box[j][i - j] = '-';
                        ++verticalTcount[i - j];
                        ++horizontalTcount[j];
                        ++ldiagonalTcount[size - 1 - i + (2 * j)];
                    }
                }
                rdiagonal[i] = 0;
            }
            else if (rdiagonal[i] == i + 1) {
                for (int j = 0; j < i + 1; ++j) {
                    if (box[j][i - j] != 'B') {
                        box[j][i - j] = 'B';
                        ++verticalcount[i - j];
                        ++horizontalcount[j];
                        ++ldiagonalcount[size - 1 - i + (2 * j)];
                    }
                }
                rdiagonal[i] = 0;
            }
        }
        else {
            int num = (i % size) + 1;
            if (rdiagonal[i] == 0) {
                for (int j = 0; j < size - num; ++j) {
                    if (box[num + j][size - 1 - j] != '-') {
                        box[num + j][size - 1 - j] = '-';
                        ++verticalTcount[size - 1 - j];
                        ++horizontalTcount[num + j];
                        ++ldiagonalTcount[num + (2 * j)];
                    }
                }
                rdiagonal[i] = 0;
            }
            else if (rdiagonal[i] == (size - num)) {
                for (int j = 0; j < size - num; ++j) {
                    if (box[num + j][size - 1 - j] != 'B') {
                        box[num + j][size - 1 - j] = 'B';
                        ++verticalcount[size - 1 - j];
                        ++horizontalcount[num + j];
                        ++ldiagonalcount[num + (2 * j)];
                    }
                }
                rdiagonal[i] = 0;
            }
        }
    }

    bool change;
    int count;
    int diagon;
    while (true) {
        change = false;
        count = 0;
        for (int i = 0; i < size; ++i) {
            if (vertical[i] != 0) {
                if (vertical[i] == verticalcount[i]) {
                    for (int j = 0; j < size; ++j) {
                        if (box[j][i] == '\0') {
                            box[j][i] = '-';
                            ++horizontalTcount[j];
                            ++rdiagonalTcount[i + j];
                            ++ldiagonalTcount[(size - (i + 1)) + j];
                            change = true;
                        }
                    }
                    vertical[i] = 0;
                }
                else if (size - vertical[i] == verticalTcount[i]) {
                    for (int j = 0; j < size; ++j) {
                        if (box[j][i] == '\0') {
                            box[j][i] = 'B';
                            ++horizontalcount[j];
                            ++rdiagonalcount[i + j];
                            ++ldiagonalcount[(size - (i + 1)) + j];
                            change = true;
                        }
                    }
                    vertical[i] = 0;
                }
            }
            else {
                ++count;
            }
        }
        if (count == size) {
            break;
        }
        for (int i = 0; i < size; ++i) {
            if (horizontal[i] != 0) {
                if (horizontal[i] == horizontalcount[i]) {
                    for (int j = 0; j < size; ++j) {
                        if (box[i][j] == '\0') {
                            box[i][j] = '-';
                            ++verticalTcount[j];
                            ++rdiagonalTcount[i + j];
                            ++ldiagonalTcount[(size - 1 + i) - j];
                            change = true;
                        }
                    }
                    horizontal[i] = 0;
                }
                else if (size - horizontal[i] == horizontalTcount[i]) {
                    for (int j = 0; j < size; ++j) {
                        if (box[i][j] == '\0') {
                            box[i][j] = 'B';
                            ++verticalcount[j];
                            ++rdiagonalcount[i + j];
                            ++ldiagonalcount[(size - 1 + i) - j];
                            change = true;
                        }
                    }
                    horizontal[i] = 0;
                }
            }
        }
        for (int i = 0; i < size + size - 1; ++i) {
            if (rdiagonal[i] != 0) {
                if (i < size) {
                    diagon = i + 1;
                }
                else {
                    diagon = size - (i % (size - 1));
                }
                if (rdiagonal[i] == rdiagonalcount[i]) {
                    if (i < size) {
                        for (int j = 0; j < i+1; ++j) {
                            if (box[j][i - j] == '\0') {
                                box[j][i - j] = '-';
                                ++verticalTcount[i - j];
                                ++horizontalTcount[j];
                                ++ldiagonalTcount[size - 1 - i + (2 * j)];
                                change = true;
                            }
                        }
                        rdiagonal[i] = 0;
                    }
                    else {
                        int num = (i % size) + 1;
                        for (int j = 0; j < size - num; ++j) {
                            if (box[num + j][size - 1 - j] == '\0') {
                                box[num + j][size - 1 - j] = '-';
                                ++verticalTcount[size - 1 - j];
                                ++horizontalTcount[num + j];
                                ++ldiagonalTcount[num + (2 * j)];
                                change = true;
                            }
                        }
                        rdiagonal[i] = 0;
                    }
                }
                else if (diagon - rdiagonal[i] == rdiagonalTcount[i]) {
                    if (i < size) {
                        for (int j = 0; j < i+1; ++j) {
                            if (box[j][i - j] == '\0') {
                                box[j][i - j] = 'B';
                                ++verticalcount[i - j];
                                ++horizontalcount[j];
                                ++ldiagonalcount[size - 1 - i + (2 * j)];
                                change = true;
                            }
                        }
                        rdiagonal[i] = 0;
                    }
                    else {
                        int num = (i % size) + 1;
                        for (int j = 0; j < size-num; ++j) {
                            if (box[num + j][size - 1 - j] == '\0') {
                                box[num + j][size - 1 - j] = 'B';
                                ++verticalcount[size - 1 - j];
                                ++horizontalcount[num + j];
                                ++ldiagonalcount[num + (2 * j)];
                                change = true;
                            }
                        }
                        rdiagonal[i] = 0;
                    }
                }
            }
        }
        for (int i = 0; i < size + size - 1; ++i) {
            if (ldiagonal[i] != 0) {
                if (i < size) {
                    diagon = i + 1;
                }
                else {
                    diagon = size - (i % (size - 1));
                }
                if (ldiagonal[i] == ldiagonalcount[i]) {
                    if (i < size) {
                        int num = size - (1 + i);
                        for (int j = 0; j < i+1; ++j) {
                            if (box[j][num + j] == '\0') {
                                box[j][num + j] = '-';
                                ++verticalTcount[size - (1 + i) + j];
                                ++horizontalTcount[j];
                                ++rdiagonalTcount[size - 1 - i + (2 * j)];
                                change = true;
                            }
                        }
                        ldiagonal[i] = 0;
                    }
                    else {
                        int num = (i % size) + 1;
                        for (int j = 0; j < size - num; ++j) {
                            if (box[num + j][j] == '\0') {
                                box[num + j][j] = '-';
                                ++verticalTcount[j];
                                ++horizontalTcount[num + j];
                                ++rdiagonalTcount[num + (2 * j)];
                                change = true;
                            }
                        }
                        ldiagonal[i] = 0;
                    }
                }
                else if (diagon - ldiagonal[i] == ldiagonalTcount[i]) {
                    if (i < size) {
                        int num = size - (1 + i);
                        for (int j = 0; j < i+1; ++j) {
                            if (box[j][num + j] == '\0') {
                                box[j][num + j] = 'B';
                                ++verticalcount[size - (1 + i) + j];
                                ++horizontalcount[j];
                                ++rdiagonalcount[size - 1 - i + (2 * j)];
                                change = true;
                            }
                        }
                        ldiagonal[i] = 0;
                    }
                    else {
                        int num = (i % size) + 1;
                        for (int j = 0; j < size - num; ++j) {
                            if (box[num + j][j] == '\0') {
                                box[num + j][j] = 'B';
                                ++verticalcount[j];
                                ++horizontalcount[num + j];
                                ++rdiagonalcount[num + (2 * j)];
                                change = true;
                            }
                        }
                        ldiagonal[i] = 0;
                    }
                }
            }
        }
        if (!change) {
            break;
        }
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (j == 0) {
                out << box[i][j];
            }
            else {
                out << ' ' << box[i][j];
            }
        }
        out << '\n';
    }

    in.close();
    out.close();
    /*
        delete[] vertical;
        delete[] horizontal;
        delete[] rdiagonal;
        delete[] ldiagonal;
        for (int i = 0; i < size; ++i) {
            delete[] box[i];
        }
        delete[] box;

        delete[] verticalcount;
        delete[] horizontalcount;
        delete[] rdiagonalcount;
        delete[] ldiagonalcount;

        delete[] verticalTcount;
        delete[] horizontalTcount;
        delete[] rdiagonalTcount;
        delete[] ldiagonalTcount;*/
}