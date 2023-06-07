#ifndef _WORD_TREE_
#define _WORD_TREE_

#include <list>
#include <iterator>
#include "charNode.hpp"

using namespace std;

class wordTree {
    private:
        charNode *root;
        charNode* getChildSig(string sig, charNode* papa);        // Procura recursivamente por um sig a partir de um nodo pai (para ser usado em findCharNodeForSig)
        charNode* getStringEnd(charNode* nodo);                   // Retorna o último nodo de uma string (para ser usado em findCharNodeForSig)
        void subtreeDestroyer(charNode* nodo);                    // Destrói recursivamente uma subárvore (para ser usado em ~wordTree)
    public:
        wordTree();                                               // Constutor
        ~wordTree();                                              // Destrutor

        charNode* getRoot();                                      // Retrieve root

        void addWord(string word, string sig);                    // Adiciona palavra na estrutura em árvore
        charNode *findCharNodeForSig(string sig);                 // Vai descendo na árvore até onde conseguir encontrar a palavra que tem significado sig
        charNode *findCharNodeForWord(string word);               // Vai descendo na árvore até onde conseguir encontrar a palavra providenciada
        list<string> searchAll(string prefix);                    // Percorre a árvore e retorna uma lista com as palavras iniciadas pelo prefixo dado.

        void read();                                              // Le o arquivo .csv
        void searchEngine();                                      // Motor de busca
};

#endif