#include <iostream>
#include <list>
#include <sstream>
#include "wordTree.hpp"

int main() {
    wordTree* arvore = new wordTree();
    arvore->read();
    arvore->searchEngine();
    delete arvore;
}