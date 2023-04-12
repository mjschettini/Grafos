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
    Grafo *grafoND = grafo->grafoNaoDirecionado();
    grafoND->buscaLargura(6,9);
    /*
    ifstream in ("input.txt");
    clock_t start;
    double tempo;

    Grafo *grafo = new Grafo (in);
    grafo->imprime ();
    cout << "Operacoes: " << grafo->_numOperacao();

    tempo = (clock()-start)/(double) CLOCKS_PER_SEC;
    cout << "\n\n"<< tempo;
    
    */
//     cout << "---------------------";
//     // //Ex1: criar e imprimir grafo transposto.

//     // Grafo *grafoT = grafo->grafoTransposto();
//     // cout << "\n";
//     // grafoT->imprime();}tado.
//     Grafo *grafoND = grafo->grafoNaoDirecionado();
//     cout << "\n";
//     grafoND->imprime();

//     // // Ex3: Ler e inserir nova aresta, verificando se ela já existe.


//     // Grafo::Aresta *aresta = grafo->lerAresta();
//     // if(!grafo->existeAresta(aresta->_v1(), aresta->_v2())){
//     //    grafo->insereAresta(aresta->_v1(), aresta->_v2(), aresta->_peso());
//     // }
//     // grafo->imprime();
//     // cout << endl;

//     // // //Ex4: Ler e remover uma aresta, verificando se ela já existe.

//     // // Grafo::Aresta *aresta = grafo->lerAresta();
//     // if(grafo->existeAresta(aresta->_v1(),aresta->_v2()))
//     //     grafo->retiraAresta(aresta->_v1(),aresta->_v2());
//     // grafo->imprime();
//     // cout << endl;


//     // //Ex5: Imprimir uma lista adjacente de um determinado vértices.

//     cout << "Digite um vértice: "<< endl;
//     cin >> v;
//     Grafo::Aresta *aresta = grafo->primeiroListaAdj(v);
//     cout << "Lista de adjacência: "<< endl;
//     while (aresta!=NULL){
//         cout << aresta->_v2() << "\t";
//         aresta = grafo->proxAdj (v);
//     }
//     cout << endl;



//     // //Ex6: Criar um método para retornar o grau de um determinado vértice

//     cout << "Informe o vértice para saber o grau: ";
//     cin >> v;
//     cout << "O grau do vértice " << v << " é: "<< grafo->grauVertice(v) << endl;

//     // // Ex7: Criar um método para verificar se o grafo é completo
//    cout << "O Grafo eh completo? " <<  grafo->completo();


//     // // Ex8: Crie um método para verificar se um grafo é Euleriano
//    cout << "O Grafo eh Euleriano? " << grafoND->euleriano();

//     // Ex9: Crie um método para verificar se o grafo é Sub-Euleriano
//    cout << "O Grafo eh Sub-Euleriano? " << grafoND->subEuleriano();

//     // Ex10: Crie um método para mostrar o caminho de um grafo



}
