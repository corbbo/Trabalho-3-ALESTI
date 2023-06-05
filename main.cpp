#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include "wordTree.hpp"

/*int main(){
    // lista de palavras
    std::list<word> lista;
    string line, pal, sig;

    // ponteiro para o arquivo
	fstream fin;

	// abre o arquivo
	fin.open("dicionario.csv", ios::in);
    if(fin.fail()){
        cout << "Erro ao abrir o arquivo!" << endl;
        return 0;
    }

    // enquanto nao for o fim do arquivo... segue lendo...
	while (!fin.eof()) {
        // pega uma linha do arquivo e coloca dentro de "line"
		getline(fin, line);

        // transforma essa linha em um fluxo
		stringstream s(line);

        // lê cada coluna, ou seja, até chegar no ";"
		getline(s, pal, ';');
        getline(s, sig, ';');
        word p(pal, sig);
        lista.push_back(p);
    }

    while(lista.size() > 0){
        cout << lista.front().getWord() << ": " << lista.front().getSig() << endl;
        lista.pop_front();
    }

}*/
int main() {
    wordTree* arvore = new wordTree();
    arvore->addWord("FRUTA", "Fruta");
    arvore->addWord("FRUTIFERO", "Prospero, abundante");
    arvore->addWord("FRUTIFICAR", "Dar fruto");
    arvore->addWord("FRUTO", "Fruta");
    arvore->addWord("FRUTOSO", "Que produz frutos");
    arvore->addWord("FRUTUOSO", "Que produz frutos");
    arvore->addWord("FRUTUOSIDADE", "Qualidade de frutuoso");
    list<string> lista;
    lista = arvore->searchAll("FRUT");
    list<string>::iterator k = lista.begin();
    for (int i = 0; i < lista.size(); k++, i++) {
        cout << (*k) << endl;
    }
    while (1);
    delete arvore;
}