#include "wordTree.hpp"
#include "charNode.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

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

//This function returns the last node of a string
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
    list<string> words; //List of words that can be formed with the prefix that will be returned
    charNode* aux = findCharNodeForWord(prefix); //Find the node that forms the prefix
    if (aux->getSubtreesSize() > 0 && aux != root) {
        list<charNode*> iteratorExorcisado = aux->getSubtreeList();                                         // <--- contribuições para o exorcismo/purgação do iterator k
        int size = iteratorExorcisado.size();                                                                         
        for (int i = 0; i < size; i++) { //For each subtree of the node that forms the prefix          
            iteratorExorcisado.pop_front();                                                                       
        }            
        //list<charNode*>::iterator k = aux->getSubtreeList().begin();                                      // <--- Criações do demônio que desvirtuam o código e o ser humano
        iteratorExorcisado = aux->getSubtreeList();
        size = iteratorExorcisado.size();
        for (int i = 0; i < size; i++) { //For each subtree of the node that forms the prefix
            charNode* temp = iteratorExorcisado.front();
            iteratorExorcisado.pop_front();
        //for (int i = 0; i < aux->getSubtreesSize() && (*k) != nullptr; i++, k++) { //For each subtree of the node that forms the prefix <--- Criações do demônio que desvirtuam o código e o ser humano
            if (temp->getSig() != "") {
                words.push_back(temp->getWord()); //If the node has a signature, add the word to the list
            }
            if (temp->getSubtreesSize() == 0) {
                continue; //If the subtree is empty, continue
            }
            else { //If the subtree is not empty
                list<string> auxList = searchAll(temp->getWord()); //Recursively search for more words
                words.splice(words.end(), auxList); //Add the words found to the list
            }
        }
    }
    return words;
}

//The function below is the main function of the program. It first asks the user to choose a search mode. Then,
//it asks the user to input a prefix or a word, depending on the search mode. Then, it searches for all words
//that can be formed with the prefix or the word. If the list of words is not empty, the function prints all
//words that can be formed with the prefix or the word. If the list of words is empty, the function prints a
//message saying that no words were found. Then, the function asks the user to choose another search mode. This
//process is repeated until the user chooses to exit the program.
void wordTree::searchEngine() {
    int mode = 0;
    cout << "Bem-vindo ao dicionario de palavras!" << endl;
    cout << "Por favor, escolha o modo de busca:" << endl;
    cout << "1 - Busca por prefixo" << endl;
    cout << "2 - Busca por palavra" << endl;
    cout << "3 - Sair" << endl;
    cin >> mode;
    while (mode != 3) {
        if (mode == 1) {
            string prefix;
            cout << "Digite o prefixo que deseja buscar: ";
            cin >> prefix;
            list<string> words = searchAll(prefix);
            if (words.size() > 0) {
                cout << "Palavras encontradas:" << endl;
                list<string>::iterator k = words.begin();
                for (int i = 0; i < words.size(); i++, k++) {
                    cout << (*k) << endl;
                }
                cout << endl;
                cout << "Digite a palavra entre as encontradas que deseja buscar: ";
                string word;
                cin >> word;
                charNode* aux = findCharNodeForWord(word);
                if (aux != root) cout << aux->getWord() << ": " << aux->getSig() << endl;
                else cout << "Palavra nao encontrada." << endl;
            }
            else cout << "Nenhuma palavra encontrada." << endl;
        }
        else if (mode == 2) {
            string word;
            cout << "Digite a palavra que deseja buscar: ";
            cin >> word;
            charNode* aux = findCharNodeForWord(word);
            if (aux != root) cout << aux->getWord() << ": " << aux->getSig() << endl;
            else cout << "Palavra nao encontrada." << endl;
        }
        else cout << "Modo invalido." << endl;
        cout << "Por favor, escolha o modo de busca:" << endl;
        cout << "1 - Busca por prefixo" << endl;
        cout << "2 - Busca por palavra" << endl;
        cout << "3 - Sair" << endl;
        cin >> mode;
    }
}

//The function below reads the file "dicionario.csv" and adds all words and their signatures to the tree.
//The file "dicionario.csv" contains a list of words and their signatures, separated by a semicolon. The
//function reads the file line by line, and for each line, it adds the word and the signature to the tree.
//The function then closes the file.
void wordTree::read() {
    ifstream infile;
    infile.open("dicionario.csv");
    string line;
    while(!infile.eof()) {
        getline(infile, line);
        stringstream ss(line);
        string word;
        string sig;
        getline(ss, word, ';');
        getline(ss, sig);
        addWord(word, sig);
    }
    infile.close();
}