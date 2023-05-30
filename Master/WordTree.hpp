#ifndef _WORD_TREE_
#define _WORD_TREE_

#include <list>
#include "CharNode.hpp"

using namespace std;

class WordTree
{
    CharNode *root;
    int totalNodes = 0;
    int totalWords = 0;

public:
    WordTree(); // constutor

    int getTotalWords();
    int getTotalNodes();

    void addWord(string word, string significado); // Adiciona palavra na estrutura em árvore
    CharNode *findCharNodeForWord(string word);    // Vai descendo na árvore até onde conseguir encontrar a palavra
    std::list<string> searchAll(string prefix);    // Percorre a árvore e retorna uma lista com as palavras iniciadas pelo prefixo dado.
};

#endif