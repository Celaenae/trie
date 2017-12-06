
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
    bool isTerminalNode;
public:
    TrieNode(Type, bool in_isTerminal = false);
    std::shared_ptr<TrieNode> setChild(Type);
    std::shared_ptr<TrieNode> getChild(Type);
    void removeChild(Type);
    void setTerminal(bool);
    bool isTerminal();
};


template<class Type>
void TrieNode<Type>::setTerminal(bool in_isTerminal)
{
    isTerminalNode = in_isTerminal;
}

template<class Type>
bool TrieNode<Type>::isTerminal()
{
    return isTerminalNode;
}

template<class Type>
std::shared_ptr< TrieNode<Type> > TrieNode<Type>::getChild(Type in_Data)
{
    auto search = children.find(in_Data);

    return search != children.end() ? search->second : nullptr;

}


template<class Type>
std::shared_ptr< TrieNode<Type> > TrieNode<Type>::setChild(Type in_Data)
{


    std::pair<typename std::map<Type, std::shared_ptr<TrieNode> >::iterator , bool> returnedIterator
            = children.try_emplace(in_Data, nullptr );

    if (returnedIterator.second == true)
    {
        (returnedIterator.first)->second = std::make_shared<TrieNode<Type>>(TrieNode<Type>(in_Data));
    }

    return (returnedIterator.first)->second;
}

template<class Type>
void TrieNode<Type>::removeChild(Type in_Data)
{

    std::pair<typename std::map<Type, std::shared_ptr<TrieNode> >::iterator , bool> returnedIterator
            = children.try_emplace(in_Data, nullptr );

    if (returnedIterator.second == true)
    {
        children.erase(returnedIterator.first);
    }

}

template<class Type>
TrieNode<Type>::TrieNode(Type in_data, bool in_isTerminal)
        :data(in_data),
         isTerminalNode(in_isTerminal)
{

}




#endif //TRIE_TRIENODE_H
