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

charNode* charNode::findChildChar(char element) {
    list<charNode*>::iterator k = subtrees.begin();
    while ((*k) != nullptr) {
        if ((*k)->chara == element) return (*k);
        else k++;
    }
    return this;
}

string charNode::getWord() {
    stack<char> charStack;
    string word = "";
    for (charNode* aux = this; aux->father != nullptr; aux = aux->father) charStack.push(aux->chara);
    while (charStack.size()) {word += charStack.top(); charStack.pop();}
    return word;
}