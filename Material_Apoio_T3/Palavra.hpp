#ifndef _PALAVRA_
#define _PALAVRA_

#include <iostream>
#include <string>

using namespace std;

// Classe Palavra
class Palavra {
    string palavra = "";
    string significado = "";
public:
    Palavra (string palavra, string significado);
    string getPalavra();
    string getSignificado();
};

#endif
