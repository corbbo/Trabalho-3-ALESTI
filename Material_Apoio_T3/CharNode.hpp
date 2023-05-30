#ifndef _CHAR_NODE_
#define _CHAR_NODE_

#include <list>
#include <string>

using namespace std;

class CharNode {
public:
    CharNode *father;
    std::list<CharNode*> subtrees;
    char character;
    string significado;

    // Construtor
    CharNode (char element, string significado);
    // Adiciona um filho ao nodo
    CharNode addChild(char element, string significado);
    // Identifica quantos filhos o nodo possui
    int getSubtreesSize();
    // Acessa o filho número "idx"
    CharNode *getSubtree(int idx);
    // Obtém a palavra correspondente a este nodo, subindo até a raiz da árvore
    string getWord();
    //Encontra e retorna o nodo que tem determinado caracter
    CharNode* findChildChar(char element);
};
#endif