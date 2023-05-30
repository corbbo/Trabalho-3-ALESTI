#include "Palavra.hpp"

// construtor
Palavra::Palavra (string palavra, string significado){
    this->palavra = palavra;
    this->significado = significado;
}

string Palavra::getPalavra(){
    return palavra;
}

string Palavra::getSignificado(){
    return significado;
}