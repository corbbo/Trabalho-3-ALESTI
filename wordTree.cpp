#include "wordTree.hpp"
#include "charNode.hpp"
#include <iostream>

wordTree::wordTree() {
    root = new charNode('.', "ROOT");
    for (char aleph = 'A'; aleph < '['; aleph++) {
        charNode* aux = new charNode(aleph, "");
        root->addChild(aux); //adiciona subarvores A-Z
    }
}

charNode* wordTree::getRoot() {return root;}

/**
 * This function returns the child node of a given parent node that matches a given signature.
 * 
 * @param sig sig is a string parameter representing the signature of a child node that is being
 * searched for in the subtree of a given parent node.
 * @param papa papa is a pointer to a charNode object, which represents the parent node in a tree data
 * structure.
 * 
 * @return The function `getChildSig` is returning a pointer to a `charNode` object.
 */
charNode* wordTree::getChildSig(string sig, charNode* papa) {
    list<charNode*>::iterator k = papa->getSubtreeList().begin();
    charNode* aux = papa;
    for (int i = 0; i < papa->getSubtreesSize(); i++) {
        if ((*k)->getSig() == sig) aux = (*k);
        else if ((*k)->getSubtreesSize() > 0) aux = getChildSig(sig, (*k));
    }
    return aux;
}

/**
 * The function adds a new word to a word tree by iterating through each character of the word and
 * adding a new node for each character.
 * 
 * @param word The word to be added to the word tree.
 * @param sig The parameter "sig" is a string that represents the signature or meaning of the word
 * being added to the word tree.
 * 
 * @return void, which means it does not return any value.
 */
void wordTree::addWord(string word, string sig) {
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------
    char chara = word.front();                                //These lines of code are extracting the first character of the input word, removing it from the word                 
    word.erase(word.begin());                                 //string, and then finding the child node of the root node that corresponds to that character. This is  
    charNode *aux = root->findChildChar(chara);               //the first step in adding a new word to the word tree.
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------
    while (word.size()) {                                     //Then, it enters a while loop that continues until the word string is empty. Within the loop, it extracts the next character
        chara = word.front();                                 //it extracts the next character of the word, finds the child node of the current node that corresponds to that character, and then
        //cout << chara << "-";                               //either creates a new node for that character or moves to the existing node for that character.
        charNode* tmp = aux->findChildChar(chara);            //Finally, it removes the first character from the word string and repeats the process until the word
        //cout << tmp->getChara() << endl;                    //string is empty.
        if (tmp == aux && word.size() == 1) new charNode(chara, sig, aux);
        else if (tmp == aux) aux = new charNode(chara, "", aux);
        else aux = tmp;
        word.erase(word.begin());
    }
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------
    return;
}

/**
 * This function searches for a specific character node in a word tree that corresponds to a given
 * word.
 * 
 * @param word The parameter "word" is a string variable that represents the word for which we are
 * searching for a corresponding charNode in the wordTree.
 * 
 * @return a pointer to a charNode object that represents the last character of the input word in the
 * wordTree. If the input word is not found in the tree, the function returns a pointer to the root
 * node of the tree.
 */
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

/**
 * This function finds the last character node in a word tree that corresponds to a given word.
 * 
 * @param word The parameter "word" is a string variable that represents the word for which we want to
 * find the corresponding charNode in the wordTree.
 * 
 * @return a pointer to a charNode, which represents the last character node in the word that was
 * searched for in the tree.
 */
charNode* wordTree::findCharNodeForWord(string word) {
    int pos = 0;
    charNode* aux = root->findChildChar(word[pos++]);
    while (pos < word.size()) {
        charNode* tmp = aux->findChildChar(word[pos++]);
        if (aux == tmp) return root;
        else aux = tmp;
    }
    return aux;
}

/**
 * This function returns the last node of a string in a tree data structure.
 * 
 * @param nodo a pointer to a node in a tree data structure that represents a character in a string.
 * 
 * @return a pointer to a charNode object.
 */
charNode* wordTree::getStringEnd(charNode* nodo) {
    charNode* aux = nodo;
    if (nodo->getSubtreesSize() > 0) {
        list<charNode*>::iterator k = nodo->getSubtreeList().begin();
        for (int i = 0; i < nodo->getSubtreesSize(); i++, k++) {
            if ((*k)->getSubtreesSize() > 0) aux = getStringEnd((*k));
            else if ((*k)->getSig() != "") return (*k);
        }
    } else if (aux->getSig() != "") return aux;
}

/**
 * The function searches for all words in a word tree that have a given prefix and returns them in a
 * list.
 * 
 * @param prefix The prefix parameter is a string that represents the prefix of the words that we want
 * to search for in the word tree. The function will return a list of all the words in the tree that
 * start with the given prefix.
 * 
 * @return a list of strings that match the given prefix.
 */
list<string> wordTree::searchAll(string prefix) {
    list<string> strings;
    int pos = 0;
    charNode* aux = root->findChildChar(prefix[pos++]);
    while (pos < prefix.size()) {
        charNode* tmp = aux->findChildChar(prefix[pos++]);
        if (tmp == aux) break;
        else aux = tmp;
    }
    if (aux->getSubtreesSize() <= 0) return strings;
    list<charNode*>::iterator k = aux->getSubtreeList().begin();
    for (int i = 0; i < aux->getSubtreesSize(); i++, k++) {
        strings.push_back(getStringEnd((*k))->getWord());
    }
}