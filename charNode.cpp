#include "charNode.hpp"
#include <stack>
#include <iostream>

charNode::charNode(char element, string sig, charNode* papa) {
    if (papa != nullptr) {
        father = papa;
        papa->subtrees.push_back(this);
    } else {
        father = nullptr;
    }
    chara = element;
    this->sig = sig;
}

char charNode::getChara() {return chara;}
string charNode::getSig() {
    if (sig != "") return sig;
    else return "";
}
int charNode::getSubtreesSize()           {return (int)subtrees.size();}
charNode* charNode::getSubtree(int index) {
    list<charNode *>::iterator k = subtrees.begin();
    while (index > -1) {
        k++;
        index--;
    }
    return (*k);
}

charNode* charNode::getFather()             {return father;}
list<charNode*> charNode::getSubtreeList()  {return subtrees;}
void charNode::addChild(charNode *nodo)     {nodo->father = this; this->subtrees.push_back(nodo);}
void charNode::setFather(charNode *nodo)    {this->father = nodo;}
void charNode::setSig(string sig)           {this->sig = sig;}

charNode* charNode::findChildChar(char element) {
    list<charNode*>::iterator k = subtrees.begin();
    for (int i = 0; i < subtrees.size(); i++, k++) if ((*k)->getChara() == element) return (*k);
    return this;
}

string charNode::getWord() {
    stack<char> charStack;
    string word = "";
    for (charNode* aux = this; aux->father != nullptr; aux = aux->father) charStack.push(aux->chara);
    while (charStack.size()) {word += charStack.top(); charStack.pop();}
    return word;
}

list<string> charNode::searchAll(charNode* nodo, string prefix) {
    list<string> retorno;
    if (nodo->getSig() == "" && nodo->getSubtreesSize() > 0) {
        list<charNode*>::iterator k = nodo->getSubtreeList().begin();
        for (int i = 0; i < nodo->getSubtreesSize(); k++, i++) {
            list<string> tmp = searchAll((*k), prefix);
            if (tmp.size() != 0) retorno.insert(retorno.end(), tmp.begin(), tmp.end());
        }
    } else if (nodo->getSig() != "") retorno.push_back(nodo->getWord()); 
    return retorno;
}