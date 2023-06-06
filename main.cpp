#include <iostream>
#include <list>
#include <sstream>
#include "wordTree.hpp"

int main() {
    wordTree* arvore = new wordTree();
    //arvore->read();
    arvore->addWord("ABACATE", "Fruto do abacateiro, de casca verde e polpa amarela, muito apreciado na alimentacao humana");
    arvore->addWord("ABACATEIRO", "Arvore da familia das lauraceas, de folhas perenes, flores pequenas e fruto comestivel, o abacate");
    arvore->searchEngine();
    delete arvore;
}