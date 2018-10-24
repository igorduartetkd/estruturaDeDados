#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

#include <iostream> //std::string
#include <list> //std::list

#define TEMP ArvoreBinaria<tipo>

namespace igor{

template <class tipo>
class ArvoreBinaria{
private:
    TEMP *left, *right;
    tipo *key;
    ArvoreBinaria<tipo>* root;
    ArvoreBinaria<tipo>* pai;

    //metodos de manutençao interna privados:

    void remove(TEMP* arvore);

    //operaçoes:
    TEMP *search1(tipo elemento);
    TEMP *minimo1();
    TEMP *maximo1();
    TEMP *sucessor1();
    TEMP *predecessor1();

    void transplant(TEMP *u, TEMP *v);

public:

    ArvoreBinaria();
    ArvoreBinaria(tipo key);
    ArvoreBinaria(const ArvoreBinaria<tipo> &arvoreBinariaCopia);

    ~ArvoreBinaria();


    //modificadores:
    void insert(tipo elemento);
    void clear();
    void remove(tipo elemento);

    //capacidade:
    bool empty() const;

    //operaçoes:
    bool search(tipo elemento);
    tipo minimo();
    tipo maximo();
    tipo sucessor(tipo elemento);
    tipo predecessor(tipo elemento);



    //listagens:
    std::list<tipo>* listarOrdem() const;
    std::list<tipo>* listarPreOrdem() const;
    std::list<tipo>* listarPosOrdem() const;

};

/*
========================================================
    METODOS CONSTRUTORES E DESTRUTORES:
========================================================
*/

template <class tipo>
TEMP::ArvoreBinaria():
    left(0),
    right(0),
    key(0),
    root(this),
    pai(0)
{
}

template <class tipo>
TEMP::ArvoreBinaria(tipo key):
    left(0),
    right(0),
    key(0),
    root(this),
    pai(0)
{
    try {
        this->key = new tipo(key); //o Tipo deve implementar o construtor de copias
    } catch (std::bad_alloc& ) {
        throw std::string ("Erro ao alocar espaço em memoria no construtor da arvore");
    }
}

template <class tipo>
TEMP::ArvoreBinaria(const ArvoreBinaria<tipo> &arvoreBinariaCopia):
    left(0),
    right(0),
    key(0),
    root(this),
    pai(0)
{
    std::list<tipo>* lista;
    try {
       lista = arvoreBinariaCopia.listarPreOrdem();

       while(!lista->empty()){
           this->insert(lista->front());
           lista->pop_front();
       }
       delete lista;

    } catch (std::string &erro) {
        if(lista) delete lista;
        throw erro;
    }
}


//destrutor:
template <class tipo>
TEMP::~ArvoreBinaria(){
    if(left) delete left;
    if(right) delete right;
    if(key) delete key;
    left = right = pai = 0;
    key = 0;
}


/*
========================================================
    implementaçao dos metodos:
========================================================
*/

//modificadores:
template <class tipo>
void TEMP::insert(tipo elemento){

    if(this->empty()){
        this->key = new tipo (elemento);
        this->root = this->root;
        return;
    }

    //iterativo:
    ArvoreBinaria<tipo> *y = NULL;
    ArvoreBinaria<tipo> *x = this->root;

    while(x){
        y = x;
        if(elemento < *(x->key)){
            x = x->left;
        }else{
            x = x->right;
        }
    }

    x = new TEMP (elemento);
    x->root = this->root;
    x->pai = y;


    if(elemento < *(y->key)){
        y->left = x;
    }else{
        y->right = x;
    }
}

template<class tipo>
void TEMP::clear(){
    if(left) delete left;
    if(right) delete right;
    if(key) delete key;
    left = right = 0;
    key = 0;
}



//operadores:
template<class tipo>
void TEMP::remove(TEMP* arvore){

    if(arvore->left == 0){
        transplant(arvore, arvore->right);
    }else if(arvore->right == 0){
        transplant(arvore, arvore->left);
    } else {
        TEMP* y = arvore->right->minimo1();
        if( !(y->pai == arvore)){
            transplant(y, y->right);
            y->right = arvore->right;
            y->right->pai = y;
        }
        transplant(arvore, y);
        y->left = arvore->left;
        y->left->pai = y;
    }

    //partirularidade dos ponteiros:
    delete arvore;
}

template<class tipo>
TEMP* TEMP::search1(tipo elemento){
    //SEARCH ITERATIVO:
    ArvoreBinaria<tipo>* arvore = this;

    while( arvore &&  !(elemento == *(arvore->key))){
        if(elemento < *(arvore->key)){
            arvore = arvore->left;
        }else{
            arvore = arvore->right;
        }
    }

    return arvore;
}

template<class tipo>
TEMP* TEMP::minimo1(){
    ArvoreBinaria<tipo>* arvore = this;

    while(arvore->left){
        arvore = arvore->left;
    }

    return arvore;
}

template<class tipo>
TEMP* TEMP::maximo1(){
    ArvoreBinaria<tipo>* arvore = this;

    while(arvore->right){
        arvore = arvore->right;
    }

    return arvore;
}

template<class tipo>
TEMP* TEMP::sucessor1(){
    if(this->right) return this->right->minimo1();

    TEMP* papi = this->pai, *x = this;

    while( (papi) && x == papi->right){
        x = papi;
        papi = x->pai;
    }

    return papi;
}

template<class tipo>
TEMP* TEMP::predecessor1(){
    if(this->left) return this->left->maximo1();

    TEMP* papi = this->pai, *x = this;

    while( (papi) && x == papi->left){
        x = papi;
        papi = x->pai;
    }

    return papi;
}

//capacidade:

template<class tipo>
bool TEMP::empty() const{
    if(key) return false;
    return true;
}

template<class tipo>
void TEMP::transplant(TEMP *u, TEMP *v){
    //se for a raiz:
    if(!(u->pai)){
        u->root = v;
    }
    else{
        if(u == u->pai->left){
            u->pai->left = v;
        }else{
            u->pai->right = v;
        }
    }

    if(v){
        v->pai = u->pai;
    }

    //particularidade dos ponteiros:
    u->left = u->right = u->pai = u->root = 0;

}

/*
========================================================
      METODOS PUBLICOS:
========================================================
*/
template<class tipo>
void TEMP::remove(tipo elemento){
    TEMP* arvoreRemover = search1(elemento);

    if(arvoreRemover) remove(arvoreRemover);
}

template<class tipo>
bool TEMP::search(tipo elemento){
    if(search1(elemento))
        return true;

    return false;
}

template<class tipo>
tipo TEMP::minimo(){
    return *(minimo1()->key);
}

template<class tipo>
tipo TEMP::maximo(){
    return *(maximo1()->key);
}

template<class tipo>
tipo TEMP::sucessor(tipo elemento){
    TEMP* atual = search1(elemento);
    return *(atual->sucessor1()->key);

}

template<class tipo>
tipo TEMP::predecessor(tipo elemento){
    TEMP* atual = search1(elemento);
    return *(atual->predecessor1()->key);
}

/*
========================================================
       IMPLEMENTAÇAO DAS LISTAGENS:
========================================================
*/
template<class tipo>
std::list<tipo>* TEMP::listarOrdem() const{
    std::list<tipo> *listaSaida = 0 , *listaAuxiliar = 0;


    try {
       listaSaida = new std::list<tipo>;
    } catch (std::bad_alloc&) {
        throw std::string ("Erro ao alocar espaço em memoria para lista");
    }

    try{
        if(left){
            listaAuxiliar = left->listarOrdem();
            listaSaida->splice(listaSaida->end(), *listaAuxiliar);
            delete listaAuxiliar;
            listaAuxiliar = 0;
        }

        listaSaida->push_back(*(this->key));

        if(right){
            listaAuxiliar = right->listarOrdem();
            listaSaida->splice(listaSaida->end(), *listaAuxiliar);
            delete listaAuxiliar;
            listaAuxiliar = 0;
        }
    } catch (std::string &erro){
        delete listaSaida;
        throw erro;
    }

    return listaSaida;
}

template<class tipo>
std::list<tipo>* TEMP::listarPreOrdem() const{
    std::list<tipo> *listaSaida = 0 , *listaAuxiliar = 0;

    try {
       listaSaida = new std::list<tipo>;
    } catch (std::bad_alloc&) {
        throw std::string ("Erro ao alocar espaço em memoria para lista");
    }

    try{
        listaSaida->push_back(*(this->key));

        if(left){
            listaAuxiliar = left->listarPreOrdem();
            listaSaida->splice(listaSaida->end(), *listaAuxiliar);
            delete listaAuxiliar;
            listaAuxiliar = 0;
        }

        if(right){
            listaAuxiliar = right->listarPreOrdem();
            listaSaida->splice(listaSaida->end(), *listaAuxiliar);
            delete listaAuxiliar;
            listaAuxiliar = 0;
        }
    } catch (std::string &erro){
        delete listaSaida;
        throw erro;
    }

    return listaSaida;
}

template<class tipo>
std::list<tipo>* TEMP::listarPosOrdem() const{
    std::list<tipo> *listaSaida = 0 , *listaAuxiliar = 0;

    try {
       listaSaida = new std::list<tipo>;
    } catch (std::bad_alloc&) {
        throw std::string ("Erro ao alocar espaço em memoria para lista");
    }

    try{
        if(left){
            listaAuxiliar = left->listarPosOrdem();
            listaSaida->splice(listaSaida->end(), *listaAuxiliar);
            delete listaAuxiliar;
            listaAuxiliar = 0;
        }

        if(right){
            listaAuxiliar = right->listarPosOrdem();
            listaSaida->splice(listaSaida->end(), *listaAuxiliar);
            delete listaAuxiliar;
            listaAuxiliar = 0;
        }

        listaSaida->push_back(*(this->key));
    } catch (std::string &erro){
        delete listaSaida;
        throw erro;
    }

    return listaSaida;
}



}//fim da namespace

#endif // ARVOREBINARIA_H
