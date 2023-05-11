#include "Lista.h" 
#include "FPHeapMinIndireto.h"
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <array>
#include <cstring>
#include <float.h>
using namespace std;

	class Grafo {
	public:
		class Aresta {
	  private:
	    int v1, v2, peso; 
	  public: 
	    Aresta (int v1, int v2, int peso) {
	      this->v1 = v1; this->v2 = v2; this->peso = peso;
	    }
	    int _peso () { return this->peso; }
	    int _v1 () { return this->v1; }
	    int _v2 () { return this->v2; }
      bool operator<(const Aresta &p) const{
        return peso<p.peso;
      }
	    ~Aresta(){}
	  };
	private:	
		class Celula {
      friend class Grafo;
      friend ostream& operator<< (ostream& out, const Celula& celula) {
        out << "vertice:" << celula.vertice << endl;
        out << "peso:"    << celula.peso    << endl;
        return out;
      }    
		private:	
	    int vertice, peso;
	  public:
	    Celula (int v, int p) {
	    	this->vertice = v; this->peso = p;
	    }
	    Celula (const Celula& cel) { *this = cel; }      
      bool operator== (const Celula& celula) const {
        return this->vertice == celula.vertice;
      }
      bool operator!= (const Celula& celula) const {
        return this->vertice != celula.vertice;
      }
      const Celula& operator= (const Celula& cel) {     
        this->vertice = cel.vertice; this->peso = cel.peso;
        return *this; // @{\it permite atribui\c{c}\~oes encadeadas}@
      }      
      ~Celula () {}	    
	  }; 
    Lista<Celula> *adj; 
    int numVertices, numOperacao;
  public:
    Grafo( istream &in );
    Grafo (int numVertices);	  
    Grafo (int numVertices, int numArestas);	  
	  void insereAresta (int v1, int v2, int peso);
	  bool existeAresta (int v1, int v2) const;
	  bool listaAdjVazia (int v) const;
    Aresta *lerAresta ();
	  Aresta *primeiroListaAdj (int v);
	  Aresta *proxAdj (int v);
	  Aresta *retiraAresta (int v1, int v2);
	  void imprime () const ;
	  int _numVertices () const;
	  Grafo *grafoTransposto ();
    Grafo *grafoNaoDirecionado();
    // void Grafo::insereArestaNova ();
    int grauVertice(int v) const;
    bool completo() const;
    bool euleriano() const;
    bool subEuleriano() const;
    int _numOperacao();
    void caminhoEuler();
    void visitaDfs(int u, int *cor, int *antecessor);
    void buscaProfundidade();
    void aciclicoVisitaDFS(int u, int *cor, int *antecessor, bool &ciclo);
    bool aciclico();
    void numComponentesVisitaDFS(int u, int *cor, int *antecessor);
    int numComponentes();
    void ordenacaoTopologicaVisitaDFS(int u, int *cor, int *antecessor, vector<int> &L);
    vector<int> ordenacaoTopologica();
    void buscaLargura(int x, int y);
    void visitaBfs(int u, int *cor, int *antecessor, int *dist, vector<int>& visitados);
    void imprimeCaminho(int u, int v, int *antecessor);
    int encontreConjunto (int conjunto[], int x);
    void unirConjunto(int conjunto[], int x, int y);
    void kruskal();
    void prim(int raiz);
    ~Grafo ();	  
	};

  Grafo::Grafo( istream &in )
  {
    this->numOperacao = 0;
   int v1, v2, peso, numVertices;
   in >> numVertices;
  
   this->adj = new Lista<Celula>[numVertices]; 
   this->numVertices = numVertices; 	  	  	
   
    while (in>>v1>>v2>>peso) {
      Grafo::Aresta *a = new Grafo::Aresta (v1, v2, peso);
      this->insereAresta (a->_v1 (), a->_v2 (), a->_peso ()); 
      delete a;
    }
  }

  Grafo::Grafo (int numVertices) {
  	this->adj = new Lista<Celula>[numVertices]; 
  	this->numVertices = numVertices; 	  	
  }	  
  Grafo::Grafo (int numVertices, int numArestas) {
  	this->adj = new Lista<Celula>[numVertices]; 
  	this->numVertices = numVertices; 	  	
  }	  

  Grafo::Aresta *Grafo::lerAresta () {
    cout << "Aresta:" << endl;
    cout << "  V1:"; int v1 = 0;
    cin >> v1;
    cout << "  V2:"; int v2 = 0;
    cin >> v2;
    cout << "  Peso:"; int peso = 0;
    cin >> peso;
    return new Grafo::Aresta (v1, v2, peso);
  }

  void Grafo::insereAresta (int v1, int v2, int peso) {
    Celula item (v2, peso); 
    this->adj[v1].insere (item); 
  }
  
  bool Grafo::existeAresta (int v1, int v2) const {
    Celula item (v2, 0);
    return (this->adj[v1].pesquisa (item) != NULL);
  }
  bool Grafo::listaAdjVazia (int v) const {
		return this->adj[v].vazia ();  
  }	  
  Grafo::Aresta *Grafo::primeiroListaAdj (int v) {
    // @{\it Retorna a primeira aresta que o v\'ertice v participa ou}@
    // @{\it {\bf NULL} se a lista de adjac\^encia de v for vazia}@ 
    Celula *item = this->adj[v]._primeiro ();    
    return item != NULL ? new Aresta(v,item->vertice,item->peso) : NULL;
  }
  Grafo::Aresta *Grafo::proxAdj (int v) {
    // @{\it Retorna a pr\'oxima aresta que o v\'ertice v participa ou}@
    // @{\it {\bf NULL} se a lista de adjac\^encia de v estiver no fim}@
    Celula *item = this->adj[v].proximo ();    
    return item != NULL ? new Aresta(v,item->vertice,item->peso) : NULL;
  }
  Grafo::Aresta *Grafo::retiraAresta (int v1, int v2) {
    this->numOperacao++;
    Celula chave (v2, 0);
    Celula *item = this->adj[v1].retira (chave);
    Aresta *aresta = item != NULL ? new Aresta(v1,v2,item->peso) : NULL;
    delete item; 
    return aresta;
  }
  void Grafo::imprime () const {
    for (int i=0; i < this->numVertices; i++){ 
      cout << "Vertice " << i << ":" << endl;
      Celula *item = this->adj[i]._primeiro ();
      while (item != NULL) {
        cout << "  " << item->vertice << " (" <<item->peso<< ")" << endl;
        item = this->adj[i].proximo ();
      }
    }
  }
  int Grafo::_numVertices () const { 
    return this->numVertices; 
  }
  Grafo *Grafo::grafoTransposto () {  	
    Grafo *grafoT = new Grafo (this->numVertices); 
    for (int v = 0; v < this->numVertices; v++)
      if (!this->listaAdjVazia (v)) {
        Aresta *adj = this->primeiroListaAdj (v);
        while (adj != NULL) {
          grafoT->insereAresta (adj->_v2 (), adj->_v1 (), adj->_peso ());
          delete adj;
          adj = this->proxAdj (v);
        }
      }
    return grafoT;
  }
  Grafo *Grafo::grafoNaoDirecionado () {  	
    Grafo *grafoND = new Grafo (this->numVertices); 
    for (int v = 0; v < this->numVertices; v++)
      if (!this->listaAdjVazia (v)) {
        Aresta *adj = this->primeiroListaAdj (v);
        while (adj != NULL) {
          grafoND->insereAresta (adj->_v2 (), adj->_v1 (), adj->_peso ());
          grafoND->insereAresta (adj->_v1 (), adj->_v2 (), adj->_peso ());
          
          delete adj;
          adj = this->proxAdj (v);
        }
      }
    return grafoND;
  }
  int Grafo::grauVertice(int v) const{
    int cont=0;
    Celula *item = this->adj[v]._primeiro ();
      while (item != NULL) {
        cont++;
        item = this->adj[v].proximo ();
      }
    return cont;
  }

  bool Grafo::completo() const {
    int aux=true;
    for (int i=0; i < this->numVertices; i++) {
      if (this->grauVertice(i) != this->numVertices - 1)
        aux = false;
        break;
    }
    return aux;
  }

  bool Grafo::euleriano() const{
    for (int i=0; i < this->numVertices; i++) { 
      if (this->grauVertice(i)%2!=0) {
        return false;
      }
    }
    return true;
  }

  bool Grafo::subEuleriano () const{
    int cont = 0;
    for (int i=0; i < this->numVertices; i++) { 
      if (grauVertice(i)%2!=0) {
        cont++;
        if(cont > 2)
          return false;
      }
    }
    return true;
  }

  void Grafo::caminhoEuler()  {  
    if (euleriano()==true){
      int indiceMaior = 0;
      int grauMaior = grauVertice(indiceMaior);
      for (int i=1; i < this->numVertices; i++){
        if (grauMaior <= grauVertice(i)){
          indiceMaior = i;
          grauMaior = grauVertice(indiceMaior);
        }
      }
      cout << "Caminho Euleriano: " << endl;
      int v = indiceMaior;
      Aresta *adj = this->primeiroListaAdj(v);
      cout << v << "\t";
    
      while (adj != NULL){
        v = adj->_v2();
        cout << adj->_v2() << "\t";
        this->retiraAresta(adj->_v1(), adj->_v2());
        this->retiraAresta(adj->_v2(), adj->_v1());
        adj = this->primeiroListaAdj(v);
      }
      cout << endl;
    }
    
    else if (subEuleriano()){
      int indiceImpar=0;
      for (int i=0; i < this->numVertices; i++){
        if ((grauVertice(i) % 2)!=0){
          indiceImpar = i;
          break;
        }
      }
      cout << "Caminho Sub-Euleriano: ";
      int v = indiceImpar;
      Aresta *adj = this->primeiroListaAdj(v);
      cout << v << "\t";
    
      while (adj!=NULL){
        v = adj->_v2();
        cout << adj->_v2() << "\t";
        this->retiraAresta(adj->_v1(), adj->_v2());
        this->retiraAresta(adj->_v2(), adj->_v1());
        adj = this->primeiroListaAdj(v);
      }
      cout << endl;
    }
  }
  void Grafo::visitaDfs(int u, int *cor, int *antecessor){
    Aresta *adj = this->primeiroListaAdj(u);
    cor[u] = 1;
    int v = 0;
   
    while (adj!=NULL){
      v = adj->_v2();
      if(cor[v] == 0){
        antecessor[v] = u;
        visitaDfs(v, cor, antecessor);
      }
      adj = this->proxAdj(u);
    }
    cor[u] = 2;
  }

  void Grafo::buscaProfundidade(){
    int *antecessor = new int[this->_numVertices()];
    int *cor = new int[this->_numVertices()];
    
    for(int u=0; u< this->numVertices; u++){
      antecessor[u]=-1;
      cor[u] = 0;
    }
    
    for(int u=0; u < this->numVertices; u++){
      if(cor[u] == 0){
        visitaDfs(u, cor, antecessor);
      }
    }
  }
    
  void Grafo::aciclicoVisitaDFS(int u, int *cor, int *antecessor, bool &ciclo){
    Aresta *adj = this->primeiroListaAdj(u);
    cor[u] = 1;
    int v = 0;

    while (adj != NULL){
      v = adj->_v2();
      if(cor[v] == 1 && antecessor[u] != v)
        ciclo = true;
      if(cor[v] == 0 ){
        antecessor[v] = u;
        aciclicoVisitaDFS(v, cor, antecessor,ciclo);
      }
      adj = this->proxAdj(u);
    }
    cor[u] = 2;
  }
  bool Grafo::aciclico(){
    int *antecessor = new int[this->_numVertices()];
    int *cor = new int[this->_numVertices()];
    bool ciclo=false;

    for(int u=0; u < this->numVertices; u++){
      antecessor[u] = -1;
      cor[u] = 0;
    }
    for(int u=0; u < this->numVertices; u++)
      if(cor[u] == 0)
        aciclicoVisitaDFS(u, cor, antecessor, ciclo);
    if (ciclo == false) //Não tem ciclo = ciclo False = Aciclico True
      return false;
    return true;
  }

  void Grafo::numComponentesVisitaDFS(int u, int *cor, int *antecessor){
    Aresta *adj = this->primeiroListaAdj(u);
    cor[u] = 1;
    int v = 0;

    while (adj != NULL){
      v = adj->_v2();
      if(cor[v] == 0 ){
        antecessor[v] = u;
        numComponentesVisitaDFS(v, cor, antecessor);
      }
      adj = this->proxAdj(u);
    }
    cor[u] = 2;
  }


  int Grafo::numComponentes(){
    int *antecessor = new int[this->_numVertices()];
    int *cor = new int[this->_numVertices()];
    int k=0;
    for(int u=0; u < this->numVertices; u++){
      antecessor[u] = -1;
      cor[u] = 0;
    }
    for(int u=0; u < this->numVertices; u++)
      if(cor[u] == 0){
        numComponentesVisitaDFS(u, cor, antecessor);
        k++;
      }
    return k;
  }

  void Grafo::ordenacaoTopologicaVisitaDFS(int u, int *cor, int *antecessor, vector<int> &L){
    Aresta *adj = this->primeiroListaAdj(u);
    cor[u] = 1;
    int v = 0;

    while (adj != NULL){
      v = adj->_v2();
      if(cor[v] == 0 ){
        antecessor[v] = u;
        ordenacaoTopologicaVisitaDFS(v, cor, antecessor, L);
      }
      adj = this->proxAdj(u);
    }
    cor[u] = 2;
    L.push_back(u);
  }

  vector<int> Grafo::ordenacaoTopologica(){
    int *antecessor = new int[this->_numVertices()];
    int *cor = new int[this->_numVertices()];
    vector<int> L;

    for(int u=0; u < this->numVertices; u++){
      antecessor[u] = -1;
      cor[u] = 0;
    }
    for(int u=0; u < this->numVertices; u++)
      if(cor[u]==0)
        ordenacaoTopologicaVisitaDFS(u, cor, antecessor, L);
    reverse(L.begin(), L.end());
    return L;
  }

void Grafo::buscaLargura(int x, int y){
  int *cor = new int[this->numVertices];
  int *antecessor = new int[this->numVertices];
  int *dist = new int[this->numVertices];
  for(int u=0; u < this->numVertices; u++){
    cor[u] = 0;
    dist[u] = 999999;
    antecessor[u] = -1;
  }
  vector<int> visitados; // vetor para armazenar os vértices visitados
  visitaBfs(x, cor, antecessor, dist, visitados); // chama a função apenas para o vértice de origem
  cout << "Busca em Largura: ";
  for (int i = 0; i < visitados.size(); i++) { // imprime os vértices visitados
    cout << visitados[i] << " ";
  }
  cout << endl;
  imprimeCaminho(x, y, antecessor);
}

void Grafo::visitaBfs(int u, int *cor, int *antecessor, int *dist, vector<int>& visitados){ // recebe o vetor por referência
  queue<int> fila;
  int v;
  dist[u] = 0;
  cor[u] = 1;
  fila.push(u);
  while (!fila.empty()){
    u = fila.front();
    fila.pop();
    visitados.push_back(u); // adiciona o vértice visitado ao vetor
    Aresta *adj = this->primeiroListaAdj(u);
    while (adj != NULL){
      v = adj->_v2();
      if(cor[v] == 0){
        cor[v] = 1;
        dist[v] = dist[u] + 1;
        antecessor[v] = u;
        fila.push(v);
      }
      adj = this->proxAdj(u);
    }
    cor[u] = 2;
  }
}



void Grafo::imprimeCaminho(int u, int v, int *antecessor){
  if (u == v) {
    cout << "Menor caminho: " << u << " ";
  } else if (antecessor[v] == -1) {
    cout << "Menor caminho: Nao existe caminho de " << u << " para " << v << endl;
  } else {
    imprimeCaminho(u, antecessor[v], antecessor);
    cout << v << " ";
  }
}

int Grafo::encontreConjunto (int conjunto[], int x){
  if(conjunto[x] == -1){
    return x;
  }
  return encontreConjunto(conjunto, conjunto[x]);
}

void Grafo::unirConjunto(int conjunto[], int x, int y){
  int conjuntoX = encontreConjunto(conjunto, x);
  int conjuntoY = encontreConjunto(conjunto, y);
  conjunto[conjuntoX] = conjuntoY;
}

void Grafo::kruskal(){
  vector<Aresta> S;
  vector<Aresta> A;

  //cria v conjuntos
  int *conjunto = new int[this->_numVertices()];

  //inicializa todos os subconjuntos como conjunto de um unico
  memset(conjunto, -1, sizeof(int) * this->_numVertices());

  for(int v=0; v<this->numVertices; v++){
    if(!this->listaAdjVazia(v)){
      Aresta *adj = this->primeiroListaAdj(v);
      while(adj != NULL){
        A.push_back(*adj);
        delete adj;
        adj = this->proxAdj(v);
      }
    }
  }

  for (auto a : A)
    cout << a._peso() << " ";

  cout << endl;

  sort(A.begin(),A.end());

  for(auto a : A){
    cout << a._peso() << " ";
  }

  cout << endl;

  for (int i =0; i<A.size(); i++){
    if(encontreConjunto(conjunto, A[i]._v1()) != encontreConjunto(conjunto, A[i]._v2())){
      S.push_back(A[i]);
      unirConjunto(conjunto, A[i]._v1(), A[i]._v2());
    }
  }

  for (int i =0; i<S.size(); i++){
    cout << "(" << S[i]._v1() << ", " << S[i]._v2() << ") = " << S[i]._peso() << endl;
  }
}

void Grafo::prim(int raiz) {
  int *antecessor = NULL;
  double *peso = NULL;
  int u,v;

  int n = this->_numVertices();
  peso = new double[n];
  int *vs = new int[n+1];
  bool *itensHeap = new bool[n];
  antecessor = new int[n];

  for(int u=0; u<n; u++){
    antecessor[u] = -1;
    peso[u] = DBL_MAX;
    vs[u+1] = u;
    itensHeap[u] = true;
  }
  peso[raiz] = 0;
  FPHeapMinIndireto Q(peso, vs, n);
  Q.constroi();
  
  while(!Q.vazio()){
      u = Q.retiraMin();
      itensHeap[u] = false;
      Aresta *adj = this->primeiroListaAdj(u);
      while (adj != NULL){
      v = adj->_v2();
      if(itensHeap[v] &&  adj->_peso() < peso[v]){
        antecessor[v] = u;
        Q.diminuiChave(v, adj->_peso());
      }
      adj = this->proxAdj(u);
      }
  }

  for (int u =0; u<this->_numVertices(); u++){
    if(antecessor[u] != -1)
      cout << "(" << antecessor[u] << ", " << u << ") = " << peso[u] << endl;
  }
}


  Grafo::~Grafo () {
    delete [] this->adj;
  }	  


		
