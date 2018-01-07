
#ifndef TRIE_TRIENODE_H
#define TRIE_TRIENODE_H


#pragma once

#include <memory>
#include <map>

template<class Type>
class TrieNode
{
    Type data;
    std::map<Type, std::shared_ptr<TrieNode> > children;
    bool mIsTerminalNode;
public:
    TrieNode(Type, bool in_isTerminal = false);
    std::shared_ptr<TrieNode> setChild(Type);
    std::shared_ptr<TrieNode> getChild(Type);
    void setTerminal(bool);
    bool isTerminal();
};


template<class Type>
void TrieNode<Type>::setTerminal(bool pIsTerminal)
{
    mIsTerminalNode = pIsTerminal;
}

template<class Type>
bool TrieNode<Type>::isTerminal()
{
    return mIsTerminalNode;
}

template<class Type>
std::shared_ptr< TrieNode<Type> > TrieNode<Type>::getChild(Type pData)
{
    auto search = children.find(pData);

    return search != children.end() ? search->second : nullptr;

}


template<class Type>
std::shared_ptr< TrieNode<Type> > TrieNode<Type>::setChild(Type pData)
{

    auto[returnedIterator, isInserted] = children.try_emplace(pData, nullptr );

    if (isInserted == true)
    {
        returnedIterator->second = std::make_shared<TrieNode<Type>>(TrieNode<Type>(pData));
    }

    return returnedIterator->second;
}


template<class Type>
TrieNode<Type>::TrieNode(Type pData, bool pIsTerminal)
        :data(pData),
         mIsTerminalNode(pIsTerminal)
{

}

#endif //TRIE_TRIENODE_H
