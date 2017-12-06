

#ifndef TRIE_TRIE_H
#define TRIE_TRIE_H

#pragma once

#include "trieNode.h"
#include <vector>
#include <type_traits>
#include <algorithm>
template<class Type>
class Trie
{
    std::shared_ptr<TrieNode<Type> > root;
public:
    Trie(Type);

    template<class TypeContainer> bool find(TypeContainer&&);
    template<class TypeContainer> void add(TypeContainer&&);

    template<class TypeIter, std::enable_if_t<
            std::is_same_v<std::remove_cv_t<std::remove_reference_t<typename std::iterator_traits<TypeIter>::value_type>>, Type  >
            , int> = 0>
    bool find(TypeIter&& beginIter, TypeIter&& endIter)
    {
        std::shared_ptr< TrieNode<Type> > p = root;

        for (auto iter = beginIter; iter != endIter; iter++)
        {
        	if (p == nullptr)
        	{
        		return false;

        	}
        	p = p->getChild(*iter);
        }



        return p != nullptr && p->isTerminal();
    }

    template<class TypeIter, std::enable_if_t<
            std::is_same_v<std::remove_cv_t<std::remove_reference_t<typename std::iterator_traits<TypeIter>::value_type>>, Type  >
            , int> = 0>
    void add(TypeIter&& beginIter, TypeIter&& endIter)
    {
        std::shared_ptr< TrieNode<Type> > p = root;

        std::for_each(beginIter, endIter,     // :((
                      [&p](auto&& character)
                      {
                          p = p->setChild(character);
                      }
        );

        p->setTerminal(true);
    }

    template<std::size_t N, std::enable_if_t<std::is_same_v<char, Type> || std::is_same_v<const char, Type>,int> = 0>
    void add(const char (&arr)[N] )
    {
        add(std::begin(arr), std::end(arr)-1);

    }

    template<std::size_t N, std::enable_if_t<std::is_same_v<char, Type> || std::is_same_v<const char, Type>,int> = 0>
    bool find(const char (&arr)[N] )
    {
        return find(std::begin(arr), std::end(arr)-1);

    }

};



template<class Type>
template<class TypeContainer>
bool Trie<Type>::find(TypeContainer&& word)
{
    return find(std::begin(word), std::end(word));
}

template<class Type>
template<class TypeContainer>
void Trie<Type>::add(TypeContainer&& word)
{
    add(std::begin(word), std::end(word));
}




template<class Type>
Trie<Type>::Trie(Type t): root(std::make_shared<TrieNode<Type>>(TrieNode<Type>(t)))
{

}







#endif //TRIE_TRIE_H
