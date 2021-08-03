#include <iostream>
#include <string>

int main()
{
    int inputnum, repeat;
    std::cin >> inputnum;
    std::string str;
    for(int i = 0; i < inputnum; ++i)
    {
        std::cin >> repeat >> str;
        for(int j = 0; j < str.size(); ++j)
        {
            for(int k = 0; k < repeat; ++k)
            {
                std::cout << str[j];
            }
        }
        std::cout << "\n";
    }

}