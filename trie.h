

#ifndef TRIE_TRIE_H
#define TRIE_TRIE_H

#pragma once

#include "trieNode.h"
#include <vector>
#include <type_traits>
#include <algorithm>


enum class charFamilyArrayIsCastedToString{yes, no};

template<class Type, charFamilyArrayIsCastedToString decision = charFamilyArrayIsCastedToString::no>
class Trie
{
    std::shared_ptr<TrieNode<Type> > mRoot;

    template<typename TypeIter>
    struct rangedForAdapter
    {

        TypeIter mBegin;
        TypeIter mEnd;

        auto begin(){return mBegin;}
        auto end(){return mEnd;}

    };

public:
    explicit Trie(Type pRootData): mRoot(std::make_shared<TrieNode<Type>>(TrieNode<Type>(pRootData)))
    {

    }

    template<class TypeContainer>
    bool find(TypeContainer&& pWord)
    {
        return find(std::cbegin(pWord), std::cend(pWord));
    }

    template<class TypeContainer>
    void add(TypeContainer&& pWord)
    {
        add(std::begin(pWord), std::end(pWord));
    }

    template<class TypeContainerIter, typename deducedType = Type, std::enable_if_t<
            std::is_same_v<std::remove_cv_t<typename std::iterator_traits<TypeContainerIter>::value_type>, deducedType  >
            , int> = 0>
    bool find(TypeContainerIter&& pBeginIter, TypeContainerIter&& pEndIter)
    {
        std::shared_ptr< TrieNode<Type> > p = mRoot;

        for(auto& elem: rangedForAdapter<TypeContainerIter>{pBeginIter,pEndIter})
        {
            if (p == nullptr)
            {
                return false;
            }
            else
            {
                p = p->getChild(elem);
            }
        }

        return p != nullptr && p->isTerminal();//lazy eval, do not call isTerminal if p is nullptr.
    }

    template<class TypeContainerIter, typename deducedType = Type, std::enable_if_t<
            std::is_same_v<std::remove_cv_t<typename std::iterator_traits<TypeContainerIter>::value_type>, deducedType  >
            , int> = 0>
    void add(TypeContainerIter&& pBeginIter, TypeContainerIter&& pEndIter)
    {
        std::shared_ptr< TrieNode<Type> > p = mRoot;

        for(auto& character: rangedForAdapter<TypeContainerIter>{pBeginIter,pEndIter})
        {
            p = p->setChild(character);
        }

        p->setTerminal(true);
    }

    //optional overloads to handle null terminated char family arrays

    template<std::size_t N, typename deducedType = Type,std::enable_if_t<(decision==charFamilyArrayIsCastedToString::yes) && (std::is_same_v<char, deducedType> || std::is_same_v<wchar_t, deducedType>),int> = 0>
    void add(const Type (&pCharArray)[N] )
    {
        add(std::basic_string<deducedType>(pCharArray));
    }


    template<std::size_t N, typename deducedType = Type,std::enable_if_t<(decision==charFamilyArrayIsCastedToString::yes) && (std::is_same_v<char, deducedType> || std::is_same_v<wchar_t, deducedType>),int> = 0>
    bool find(const Type (&pCharArray)[N] )
    {
        return find(std::basic_string<deducedType>(pCharArray));
    }



};

#endif //TRIE_TRIE_H
