
#include "trie.h"
#include <iostream>

int main()
{
    {

        Trie<char,charFamilyArrayIsCastedToString::yes> tan('/');
        std::string a("aaaacas");
        std::vector<char> charvect(a.begin(), a.end());

        Trie<int> sds(2);


        tan.add(charvect);
        tan.add("asdd");
        tan.add(a);

        std::cout << "break" << std::endl;

        std::cout << tan.find("aaaacas") << std::endl;
        std::cout << tan.find(std::vector<char>(a.begin(), a.end()) ) << std::endl;
        std::cout << tan.find(std::vector<char>(a.begin(), a.end()-1)) << std::endl;
        std::cout << tan.find(std::vector<char>(a.begin(), a.end())) << std::endl;
    }

    int i = 9;
    Trie<int> sds(i);

    int hh[]={1,2,3};

    sds.add(hh);
    return 0;
}

