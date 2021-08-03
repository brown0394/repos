#include <iostream>
#include <string>
int main()
{
    bool found = false;
    bool first = true;
    std::string str;
    char alpha[27] = {"abcdefghijklmnopqrstuvwxyz"};
    std::cin >> str;
    for(int i = 0; i < 26; ++i)
    {
        if(first)
        {
            first = false;
        }
        else
        {
            std::cout << " ";
        }

        for(int j = 0; j < str.size(); ++j)
        {
            if(str[j] == alpha[i])
            {
                found = true;
                std::cout << j;
                break;
            }
        }
        if(!found)
        {
            std::cout << -1;
        }

        found = false;
        
    }
}