#include <iostream>
#include <string>


#define SIZE 9

int main() {
    std::string str1, str2, operand1, operand2, result = "";
    std::cin >> str1 >> str2;

    int len1 = str1.size() / SIZE;
    int len2 = str2.size() / SIZE;
    int length, restone;
    if (len1 < len2) {
        length = len1;
        restone = 1;
    }
    else if (len1 == len2) {
        if (str1.size() <= str2.size()) {
            restone = 1;
            length = len1;
        }
        else {
            restone = 2;
            length = len2;
        }
    }
    else {
        length = len2;
        restone = 2;
    }
    int rest1, rest2;
    if (!len1) {
        rest1 = 0;
    }
    else {
        rest1 = str1.size() / (len1 * SIZE);
    }
    if (!len2) {
        rest2 = 0;
    }
    else {
        rest2 = str2.size() / (len2 * SIZE);
    }
    int carry = 0, count1 = 0, count2 = 0;
    int j = 1, lim = SIZE + 1;
    for (int i = 0; i < length; ++i) {
        operand1 = "";
        operand2 = "";
        for (; j < lim; ++j) {
            operand1 = str1[str1.size() - j] + operand1;
            operand2 = str2[str2.size() - j] + operand2;
        }
        lim += SIZE;
        int res = std::stoi(operand1) + std::stoi(operand2) + carry;
        carry = res / 1000000000;
        res = res % 1000000000;
        result = std::to_string(res) + result;
    }
    if (restone == 1) {
        length = str1.size();
    }
    else {
        length = str2.size();
    }
    for (; -1 < length - j; ++j) {
        operand1 = str1[str1.size() - j];
        operand2 = str2[str2.size() - j];
        int res = std::stoi(operand1) + std::stoi(operand2) + carry;
        carry = res / 10;
        res = res % 10;
        result = std::to_string(res) + result;
    }
    if (restone == 1) {
        length = str2.size();
        while (true) {
            if (length - j == -1) {
                break;
            }
            operand2 = str2[str2.size() - j];
            int res = std::stoi(operand2) + carry;
            carry = res / 10;
            res = res % 10;
            result = std::to_string(res) + result;
            ++j;
        }
    }
    else {
        length = str1.size();
        while (true) {
            if (length - j == -1) {
                break;
            }
            operand2 = str1[str1.size() - j];
            int res = std::stoi(operand2) + carry;
            carry = res / 10;
            res = res % 10;
            result = std::to_string(res) + result;
            ++j;
        }
    }
    if (carry > 0) {
        result = std::to_string(carry) + result;
    }
    std::cout << result << '\n';
}