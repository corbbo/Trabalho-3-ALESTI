#ifndef _CHAR_NODE_
#define _CHAR_NODE_

#include <list>
#include <string>

using namespace std;

class CharNode
{
public:
    CharNode *father;
    std::list<CharNode *> subtrees;
    char character;
    string significado;

    CharNode(char element, string significado);          // Construtor
    CharNode addChild(char element, string significado); // Adiciona um filho ao nodo
    int getSubtreesSize();                               // Identifica quantos filhos o nodo possui
    CharNode *getSubtree(int idx);                       // Acessa o filho número "idx"
    string getWord();                                    // Obtém a palavra correspondente a este nodo, subindo até a raiz da árvore
    CharNode *findChildChar(char element);               // Encontra e retorna o nodo que tem determinado caracter
};
#endif