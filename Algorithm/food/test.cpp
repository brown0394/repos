#include <iostream>

void sort(int* arr, int size){
    int temp[9];
    int small = 999;
    int idx = 0;
    for(int i = 0; i < 8; ++i){
        for(int j = i+1; j < 9; ++j){
            if(arr[i] < arr[j]){
                small = arr[i];
                arr[i] = arr[j];
                arr[j] = small;
            }
        }
        temp[idx++] = arr[i];
    }
    /*
    for(int i = 0; i < 9; ++i){
        arr[i] = temp[i];
    }*/
    arr = temp;
}


int main(){
    bool arr2[9]{false};
    int arr[] = {5, 8, 9, 15, 2, 3, 6, 7, 1};
    sort(arr, 9);
    for(int i = 0; i < 9; ++i){
        std::cout << arr2[i] << ' ';
    }
}