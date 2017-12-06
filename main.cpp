
#include "trie.h"
#include <iostream>

int main()
{
    {
        Trie<char> tan('/');
        std::string a("aaaacas");
        std::vector<char> charvect(a.begin(), a.end());

        tan.add(charvect);
        tan.add("asdd");

        std::cout << "break" << std::endl;

        std::cout << tan.find("aaaacas") << std::endl;
        std::cout << tan.find(std::vector<char>(a.begin(), a.end()) ) << std::endl;
        std::cout << tan.find(std::vector<char>(a.begin(), a.end()-1)) << std::endl;
        std::cout << tan.find(std::vector<char>(a.begin(), a.end())) << std::endl;
    }



    return 0;
}

