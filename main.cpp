#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated"
#include "listaadj/Grafo.h"
#include <fstream>
#include <ctime>
using namespace std;
#pragma GCC diagnostic pop

int main (int argc, char **argv)
{
    ifstream in ("input.txt");
    Grafo *grafo = new Grafo (in);
    grafo->imprime();
    cout << endl;

// // Ex15: Fazer a busca em largura e mostrar o menor caminho possível entre dois vértices (Exemplificado abaixo entre os vértices 0 e 3)
  grafo->buscaLargura(0,3);


}
