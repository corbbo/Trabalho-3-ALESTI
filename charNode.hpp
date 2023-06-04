#ifndef _CHAR_NODE_
#define _CHAR_NODE_

#include <list>
#include <string>

using namespace std;

class charNode {
    private:
        charNode *father;
        list<charNode *> subtrees;
        char chara;
        string sig;
    public:
        charNode(char element = 0, string sig = "", charNode* papa = nullptr);

        char getChara();                                     // GETTERS ------------
        string getSig();                                     // --------------------
        int getSubtreesSize();                               //---------------------          
        charNode *getSubtree(int index);                     //---------------------
        list<charNode*> getSubtreeList();                    //---------------------
        string getWord();                                    //---------------------
        charNode* getFather();                               //---------------------
        bool hasChild();                                     //---------------------

        void setFather(charNode* nodo);                      // SETTERS ------------
        void setLeft(charNode* nodo);                        // --------------------
        void setRight(charNode* nodo);                       // --------------------


        charNode *findChildChar(char element);               // Encontra e retorna o nodo que tem determinado caracter a partir deste nodo
        void addChild(charNode *nodo);                       // Método especial para adicionar filhos na raíz
};
#endif