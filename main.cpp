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

//     cout << "---------------------";
//     
  // // Ex1: criar e imprimir grafo transposto.
  // Grafo *grafoT = grafo->grafoTransposto();
  // grafoT->imprime();

  // printf("\n\n");
  // printf("\n-----------------------------------------\n");
  // printf("\n\n");

  // // Ex2: Criar e imprimir um grafo não orientado.
  // Grafo *grafoND = grafo->grafoNaoDirecionado();
  // grafoND->imprime();

  // printf("\n\n");
  // printf("\n-----------------------------------------\n");
  // printf("\n\n");

  // // //Ex3: Ler e inserir nova aresta, verificando se ela já existe.
  // // Grafo::Aresta *a = grafo->lerAresta();

  // // if (!(grafo->existeAresta(a->_v1(), a->_v2()))) {
  // //     grafo->insereAresta(a->_v1(), a->_v2(), a->_peso());
  // //     cout << "Aresta inserida!" << endl;
  // // } else cout << "A aresta já existe" << endl;

  // // //Ex4: Ler e remover uma aresta, verificando se ela já existe.

  // // Grafo::Aresta *aa = grafo->lerAresta();

  // // if (grafo->existeAresta(aa->_v1(), aa->_v2())) {
  // //     grafo->retiraAresta(aa->_v1(), aa->_v2());
  // //     cout << "Aresta removida!" << endl;
  // // } else cout << "A aresta não existe" << endl;

  // // Ex5: Imprimir uma lista adjacente de um determinado vértices.

  // cout << "  V:";
  // int v = 0;
  // cin >> v;

  // Grafo::Aresta *adj = grafo->primeiroListaAdj(v);

  // cout << "Adjacente de " << v << " é: ";

  // while (adj != NULL)
  // {
  //     cout << adj->_v2() << " ";
  //     adj = grafo->proxAdj(v);
  // }

  // cout << endl;

  // // //Ex6: Criar um método para retornar o grau de um determinado vértice

  // cout << "O grau do vertice é: " << grafo->grauVertice(v) << endl;

  // // //Ex7: Criar um método para verificar se um grafo é completo

  // if (grafo->completo())
  // {
  //     cout << "O grafo é completo" << endl;
  // }
  // else
  //     cout << "O grafo não é completo" << endl;

  // // Ex8: Verificar se o grafo é Euleriano

  // if (grafo->euleriano())
  // {
  //     cout << "O grafo é euleriano" << endl;
  // }
  // else
  //     cout << "O grafo não é euleriano" << endl;

  // // Ex9: Verificar se o grafo é Sub-Euleriano

  // if (grafo->subEuleriano())
  // {
  //     cout << "O grafo é sub-euleriano" << endl;
  // }
  // else
  //     cout << "O grafo não é sub-euleriano" << endl;

  // // Ex10: Caminho Euleriano/Sub Euleriano

  // grafo->caminhoEuler();


  // // Ex11: Busca em Profundidade

  // grafo->buscaProfundidade();


  // // Ex12: Acíclico?

  // grafo->busca_aciclico();
  // cout << endl;


  // // Ex13: Numero de componentes

  // Grafo *grafoND = grafo->grafoNaoDirecionado();
  // cout << "Numero de componentes: " << grafoND->numComponentes() << endl;


  // // Ex14: Ordenação Topológica
  
  // vector<int> L;
  // Grafo *grafoT;
  // grafoT = grafo->grafoTransposto();
  // L = grafoT->ordenacaoTopologica();

  // cout << "Ordenacao Topologica: ";
  // if (!L.empty()){
  //   for (auto v : L){
  //     cout << v << " ";
  //   }
  // }

// // Ex15: Fazer a busca em largura e mostrar o menor caminho possível entre dois vértices (Exemplificado abaixo entre os vértices 0 e 3)
  grafo->buscaLargura(0,3);


}
