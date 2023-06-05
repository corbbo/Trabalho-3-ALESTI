#include "wordTree.hpp"
#include "charNode.hpp"
#include <fstream>
#include <iostream>

wordTree::wordTree() {
    root = new charNode('.', "ROOT");
    for (char aleph = 'A'; aleph < '['; aleph++) {
        charNode* aux = new charNode(aleph, "");
        root->addChild(aux); //adiciona subarvores A-Z
    }
}
void wordTree::subtreeDestroyer(charNode* nodo) {
    list<charNode*>::iterator k = nodo->getSubtreeList().begin();
    for (int i = 0; i < nodo->getSubtreesSize(); k++, i++) {
        if ((*k)->getSubtreesSize() > 0) subtreeDestroyer((*k));
        delete (*k);
    }
}
wordTree::~wordTree() {
    list<charNode*>::iterator k = root->getSubtreeList().begin();
    for (int i = 0; i < root->getSubtreesSize(); k++, i++) {
        if ((*k)->getSubtreesSize() > 0) subtreeDestroyer((*k));
        delete (*k);
    }
    delete root;
}

charNode* wordTree::getRoot() {return root;}

//The function below finds the child node of charNode papa that has the signature sig. This is done by
//iterating through the list of subtrees of papa and comparing the signature of each node in each subtree with sig.
//If the signature of a node is equal to sig, the function returns that node. If the signature of a node is not
//equal to sig, the function calls itself recursively, searching for the signature in the subtree of the node.
//If the signature is not found in the subtree, the function returns the node that was used as input. This
//process is repeated until the signature is found or the function returns papa, the original input.
charNode* wordTree::getChildSig(string sig, charNode* papa) {
    list<charNode*>::iterator k = papa->getSubtreeList().begin();
    charNode* aux = papa;
    for (int i = 0; i < papa->getSubtreesSize(); i++) {
        if ((*k)->getSig() == sig) aux = (*k);
        else if ((*k)->getSubtreesSize() > 0) aux = getChildSig(sig, (*k));
    }
    return aux;
}

//The function below adds a word to the word tree. It first searches for the first character of the word, which
//itself is the root of a subtree (from A-Z). Then, it begins searching for every other character of the word
//in the subtree of the previous character. If the character is not found, it is added to the tree. If the
//character is found, the search continues in the subtree of the found character. This process is repeated
//until the last character of the word is found or added to the tree. The last character of the word
//receives the signature or meaning of the word, indicating to future searches that a word ends in that node.
void wordTree::addWord(string word, string sig) {
    charNode* aux = root;
    for (int i = 0; i < word.length(); i++) {
        charNode* child = aux->findChildChar(word[i]);
        if (child == aux) {
            charNode* newChild = new charNode(word[i], "", aux);
            aux = newChild;
        }
        else aux = child;
    }
    aux->setSig(sig);
}

//The function below finds the last node of a string with signature sig. It first searches for the first character
//of the string, which itself is the root of a subtree (from A-Z). Then, it begins searching for every other
//character of the string in the subtree of the previous character. If the character is not found, the function
//returns the root of the tree. If the character is found, the search continues in the subtree of the found
//character. This process is repeated until the last character of the string is found or the function returns
//the root of the tree.
charNode* wordTree::findCharNodeForSig(string sig) {
    int pos = -1;
    while (pos <= 24) {
        charNode *aux = root->getSubtree(pos++);
        charNode *retorno;
        list<charNode*>::iterator k = aux->getSubtreeList().begin();
        for (int i = 0; i < aux->getSubtreesSize(); k++, i++) {
            retorno = getChildSig(sig, (*k));
            if (retorno->getSig() == sig) return retorno;
        }
    }
    return root;
}

//The function below finds the last node that forms the string word. It first searches for the first character
//of the word, which itself is the root of a subtree (from A-Z). Then, it begins searching for every other
//character of the word in the subtree of the previous character. If the character is not found, the function
//returns the root of the tree. If the character is found, the search continues in the subtree of the found
//character. This process is repeated until the last character of the word is found or the function returns
//the root of the tree.
charNode* wordTree::findCharNodeForWord(string word) {
    int pos = 0;
    charNode* aux = root->findChildChar(word[pos++]);
    while (pos < word.size()) {
        charNode* tmp = aux->findChildChar(word[pos++]);
        if (aux != tmp) aux = tmp;
        else return root;
    }
    return aux;
}

// This function returns the last node of a string
// @param nodo nodo is a pointer to a charNode object, which represents the last node of a string
// @return a pointer to a charNode object, which represents the last node of a string
charNode* wordTree::getStringEnd(charNode* nodo) {
    charNode* aux = nodo;
    while (aux->getSig() == "") {
        list<charNode*>::iterator k = aux->getSubtreeList().begin();
        aux = (*k);
    }
    return aux;
}

//The function below searches for all words that can be formed with the given prefix. It first searches for the
//node that forms the prefix. Then, it searches for all words that can be formed with the prefix by searching
//for every node with a non-empty signature in the subtrees of the node that forms the prefix. If a node with
//a non-empty signature is found in a subtree, the function adds the word that's formed by the node to a list. 
//It then continues going down that subtree, searching for more words. This process is repeated until the function
//reaches the end of that subtree. Then, it goes back to the previous node and continues searching for words.
//The entire process is repeated until all subtrees of the node that forms the prefix are searched. Once finished,
//the function returns the list of words that can be formed with the prefix.
list<string> wordTree::searchAll(string prefix) {
    list<string> words;
    charNode* aux = findCharNodeForWord(prefix);
    if (aux == root || (aux->getSubtreesSize() <= 0 && aux->getSig() == "")) return words;
    else if (aux->getSig() != "") words.push_back(aux->getWord());
    list<charNode*>::iterator k = aux->getSubtreeList().begin();
    for (int i = 0; i < aux->getSubtreesSize(); i++, k++) {
        if ((*k)->getSubtreesSize() > 0) {
            list<string> auxList = searchAll((*k)->getWord());
            words.insert(words.end(), auxList.begin(), auxList.end());
        }
        if ((*k)->getSig() != "") words.push_back((*k)->getWord());
    }
    return words;
}