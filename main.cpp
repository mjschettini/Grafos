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

    Grafo *grafoND = new Grafo (in);
    grafoND = grafo->grafoNaoDirecionado();

    // // Ex16: Implementação algoritmo de kruskal
    cout << "Kruskal: " << endl;
    grafoND->kruskal();

    // // Ex17: Implementação algoritmo de prim (origem em 0)
    cout << "Prim: " << endl;
    grafoND->prim(0);


}
