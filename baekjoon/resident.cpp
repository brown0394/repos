#include <iostream>

int main(){
    int num, col;
    int test;
    std::cin >> test;
    for(int k = 0; k < test; ++k){
        std::cin >> num >> col;
        ++num;
        int** table = new int*[num];
        for(int i = 0; i < num; ++i){
            table[i] = new int[col];
            table[i][0] = 1;
            table[i][1] = i + 2;
        }
        for(int i = 1; i < col; ++i){
            table[0][i] = table[0][i-1] + 1;
        }
        for(int i = 1; i < num; ++i){
            for(int j = 2; j < col; ++j){
                table[i][j] = table[i-1][j] + table[i][j-1];
            }
        }
        std::cout << table[num-1][col-1] << '\n';
        for(int i = 0; i < num; ++i){
            delete[] table[i];
        }
        delete[] table;
    }

}