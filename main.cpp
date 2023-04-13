#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated"
#include "listaadj/Grafo.h"
#include <fstream>
#include <ctime>
using namespace std;
#pragma GCC diagnostic pop

int main(int argc, char **argv)
{
  ifstream in("input.txt");
  Grafo *grafo = new Grafo(in);
  grafo->imprime();
  cout << endl;
  grafo->buscaLargura(0, 3);
}
