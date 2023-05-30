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
    // constutor
    WordTree();

    int getTotalWords();
    int getTotalNodes();

    // Adiciona palavra na estrutura em árvore
    void addWord(string word, string significado);

    // Vai descendo na árvore até onde conseguir encontrar a palavra
    CharNode findCharNodeForWord(string word);

    // Percorre a árvore e retorna uma lista com as palavras iniciadas pelo prefixo dado.
    std::list<string> searchAll(string prefix);
};

#endif