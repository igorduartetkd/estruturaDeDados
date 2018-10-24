#ifndef ARVORERUBRONEGRA_H
#define ARVORERUBRONEGRA_H


#include <iostream> //std::string
#include <list> //std::list

#define TEMP ArvoreRubroNegra<tipo>
#define SUBARVORE SubArvore<tipo>

namespace igor{


//classe auxiliar
template <class tipo>
class SubArvore{
public:
    SUBARVORE *left, *right;
    tipo *key;
    SUBARVORE* pai;
    bool cor; // false para vermelho e true para preto

    SubArvore();
    SubArvore(tipo key);
    ~SubArvore();

    SUBARVORE *search1(tipo elemento);
    SUBARVORE *minimo1();
    SUBARVORE *maximo1();
    SUBARVORE *sucessor1();
    SUBARVORE *predecessor1();


    std::list<tipo>* ordem() const;
    std::list<tipo>* preOrdem() const;
    std::list<tipo>* posOrdem() const;
};

template<class tipo>
SUBARVORE::SubArvore():
    left(0),
    right(0),
    key(0),
    pai(0),
    cor(true)
{
}

template<class tipo>
SUBARVORE::SubArvore(tipo key):
    left(0),
    right(0),
    key(new tipo(key)),
    pai(0),
    cor(true)
{
}

template<class tipo>
SUBARVORE::~SubArvore(){
    if(key) delete key;
    if(left) delete left;
    if(right) delete right;
    key = 0;
    left = right = 0;
    cor = true;
}

template<class tipo>
std::list<tipo>* SUBARVORE::ordem() const{
std::list<tipo> *listaSaida = 0 , *listaAuxiliar = 0;

try {
   listaSaida = new std::list<tipo>;
} catch (std::bad_alloc&) {
    throw std::string ("Erro ao alocar espaço em memoria para lista");
}

try{
    if(left->left){
        listaAuxiliar = left->ordem();
        listaSaida->splice(listaSaida->end(), *listaAuxiliar);
        if (listaAuxiliar) delete listaAuxiliar;
        listaAuxiliar = 0;
    }

    listaSaida->push_back(*(key));

    if(right->right){
        listaAuxiliar = right->ordem();
        listaSaida->splice(listaSaida->end(), *listaAuxiliar);
        if(listaAuxiliar) delete listaAuxiliar;
        listaAuxiliar = 0;
    }
} catch (std::string &erro){
    delete listaSaida;
    throw erro;
}

return listaSaida;
}


template <class tipo>
std::list<tipo>* SUBARVORE::preOrdem() const{
    std::list<tipo> *listaSaida = 0 , *listaAuxiliar = 0;

    try {
       listaSaida = new std::list<tipo>;
    } catch (std::bad_alloc&) {
        throw std::string ("Erro ao alocar espaço em memoria para lista");
    }

    try{
        listaSaida->push_back(*(this->key));

        if(left->left){
            listaAuxiliar = left->preOrdem();
            listaSaida->splice(listaSaida->end(), *listaAuxiliar);
            delete listaAuxiliar;
            listaAuxiliar = 0;
        }

        if(right->right){
            listaAuxiliar = right->preOrdem();
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


template <class tipo>
std::list<tipo>* SUBARVORE::posOrdem() const{
    std::list<tipo> *listaSaida = 0 , *listaAuxiliar = 0;

    try {
       listaSaida = new std::list<tipo>;
    } catch (std::bad_alloc&) {
        throw std::string ("Erro ao alocar espaço em memoria para lista");
    }

    try{
        if(left->left){
            listaAuxiliar = left->posOrdem();
            listaSaida->splice(listaSaida->end(), *listaAuxiliar);
            delete listaAuxiliar;
            listaAuxiliar = 0;
        }

        if(right->right){
            listaAuxiliar = right->posOrdem();
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

template<class tipo>
SUBARVORE* SUBARVORE::search1(tipo elemento){
    //SEARCH ITERATIVO:
    SUBARVORE* arvore = this;

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
SUBARVORE* SUBARVORE::minimo1(){
    SUBARVORE* arvore = this;

    while(arvore->left->left){
        arvore = arvore->left;
    }

    return arvore;
}

template<class tipo>
SUBARVORE* SUBARVORE::maximo1(){
    SUBARVORE* arvore = this;

    while(arvore->right->right){
        arvore = arvore->right;
    }

    return arvore;
}

template<class tipo>
SUBARVORE* SUBARVORE::sucessor1(){
    if(this->right) return this->right->minimo1();

    SUBARVORE* papi = this->pai, *x = this;

    while( (papi) && x == papi->right){
        x = papi;
        papi = x->pai;
    }

    return papi;
}

template<class tipo>
SUBARVORE* SUBARVORE::predecessor1(){
    if(this->left) return this->left->maximo1();

    SUBARVORE* papi = this->pai, *x = this;

    while( (papi) && x == papi->left){
        x = papi;
        papi = x->pai;
    }

    return papi;
}






//inicio da classe principal:

template <class tipo>
class ArvoreRubroNegra{
private:
    //TEMP *left, *right;
    //tipo *key;
    //ArvoreRubroNegra<tipo>* root;
    //ArvoreRubroNegra<tipo>* pai;
    //bool cor; //0 para vermelho 1 para preto


    //nova arvore:
    SUBARVORE* root;
    SUBARVORE* nil;



    //metodos de manutençao interna privados:

    void remove(SUBARVORE* arvore);

    void transplant(SUBARVORE *u, SUBARVORE *v);


    //PARTICULARES da rubro-negra:
    void leftRotate(SUBARVORE* x);
    void rightRotate(SUBARVORE* x);
    void insertFixup(SUBARVORE* z);
    void deleteFixup(SUBARVORE* x);

public:


    ArvoreRubroNegra();
    ArvoreRubroNegra(tipo key);
    ArvoreRubroNegra(const ArvoreRubroNegra<tipo> &ArvoreRubroNegraCopia);

    ~ArvoreRubroNegra();


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
TEMP::ArvoreRubroNegra():
    root(0),
    nil(new SUBARVORE)
{
}

template <class tipo>
TEMP::ArvoreRubroNegra(tipo key):
    root(0),
    nil(new SUBARVORE)
{
    try {
        this->key = new tipo(key); //o Tipo deve implementar o construtor de copias
    } catch (std::bad_alloc& ) {
        throw std::string ("Erro ao alocar espaço em memoria no construtor da arvore");
    }
}

template <class tipo>
TEMP::ArvoreRubroNegra(const ArvoreRubroNegra<tipo> &ArvoreRubroNegraCopia):
    root(0),
    nil(new SUBARVORE)
{
    std::list<tipo>* lista;
    try {
       lista = ArvoreRubroNegraCopia.listarPreOrdem();

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
TEMP::~ArvoreRubroNegra(){
    if(root) delete root;
    if(nil) delete nil;
    root = 0;
    nil = 0;
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
        root = new SUBARVORE(elemento);
        root->cor = true;
        root->left = nil;
        root->right = nil;
        root->pai = nil;
        return;
    }

    //iterativo:
    SUBARVORE *y = nil;
    SUBARVORE *x = root;

    while(x != nil){
        y = x;
        if(elemento < *(x->key)){
            x = x->left;
        }else{
            x = x->right;
        }
    }

    SUBARVORE* z = new SUBARVORE (elemento); // x é o novo z (do cormen)
    z->pai = y;
    z->left = nil;
    z->right = nil;
    z->cor = false;



    if(elemento < *(y->key)){
        y->left = z;
    }else{
        y->right = z;
    }

    insertFixup(z);


}

template<class tipo>
void TEMP::clear(){
    if(root) delete root;
}



//operadores:
template<class tipo>
void TEMP::remove(SUBARVORE* z){

    SUBARVORE *y, *x;

    y = z;
    bool cory = y->cor;

    if(z->left == nil){
        x = z->right;
        transplant(z, z->right);
    }else if(z->right == nil){
        x = z->left;
        transplant(z, z->left);
    } else {
        y = z->right->minimo1();
        cory = y->cor;
        x = y->right;
        if( y->pai == z){
            x->pai = y;
        }else{
            transplant(y, y->right);
            y->right = z->right;
            y->right->pai = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->pai = y;
        y->cor = z->cor;
    }

    if(cory == true){
        deleteFixup(x);
    }

    //partirularidade dos ponteiros:
    z->left = z->right = 0;
    delete z;
}



//capacidade:

template<class tipo>
bool TEMP::empty() const{
    if(root) return false;
    return true;
}

template<class tipo>
void TEMP::transplant(SUBARVORE *u, SUBARVORE *v){
    //se for a raiz:
    if(u->pai == nil){
        root = v;
    }
    else{
        if(u == u->pai->left){
            u->pai->left = v;
        }else{
            u->pai->right = v;
        }
    }
    v->pai = u->pai;

}

/*
========================================================
      METODOS PARTICULARES DA ARVORE RUBRO NEGRA:
========================================================
*/

template<class tipo>
void TEMP::leftRotate(SUBARVORE* x){ //x e y com base na ilustraçao do livro do cormen pag 313 third edition
    SUBARVORE* y = x->right;
    x->right = y->left;
    if(y->left != nil){
        y->left->pai = x;
    }
    y->pai = x->pai;

    if(x->pai == nil){ //problema para resolver, quando fizer a mudança de root nao vai alterar em todas as subarvores
        root = y;
    }else{
        if(x == x->pai->left){
            x->pai->left = y;
        }else{
            x->pai->right = y;
        }
    }
    y->left = x;
    x->pai = y;
}

template<class tipo>
void TEMP::rightRotate(SUBARVORE* y){ //x e y com base na ilustraçao do livro do cormen pag 313 third edition
    SUBARVORE* x = y->left;
    y->left = x->right;
    if(x->right != nil){
        x->right->pai = y;
    }
    x->pai = y->pai;

    if(y->pai == nil){ //problema para resolver, quando fizer a mudança de root nao vai alterar em todas as subarvores
        root = x;
    }else{
        if(y == y->pai->left){
            y->pai->left = x;
        }else{
            y->pai->right = x;
        }
    }
    x->right = y;
    y->pai = x;
}

template<class tipo>
void TEMP::insertFixup(SUBARVORE* z){
    SUBARVORE* y = 0;
    while(z->pai->cor == false){
        if( z->pai == z->pai->pai->left){
            y = z->pai->pai->right;
            if(y->cor == false){
                z->pai->cor = true;
                y->cor = true;
                z->pai->pai->cor = false;
                z = z->pai->pai;
            }else{
                if(z == z->pai->right){
                    z = z->pai;
                    leftRotate(z);
                }
                z->pai->cor = true;
                z->pai->pai->cor = false;
                rightRotate(z->pai->pai);
            }
        }else{
            y = z->pai->pai->left;
            if(y->cor == false){
                z->pai->cor = true;
                y->cor = true;
                z->pai->pai->cor = false;
                z = z->pai->pai;
            }else{
                if(z == z->pai->left){
                    z = z->pai;
                    rightRotate(z);
                }
                z->pai->cor = true;
                z->pai->pai->cor = false;
                leftRotate(z->pai->pai);
            }
        }
    }
    root->cor = true;
}

template<class tipo>
void TEMP::deleteFixup(SUBARVORE* x){
    //auxiliares:
    SUBARVORE* w = 0;
    while(x != root && x->cor){
        if(x == x->pai->left){
            w = x->pai->right;
            if(w->cor == false){
                w->cor = true;
                x->pai->cor = false;
                leftRotate(x->pai);
                w = x->pai->right;
            }
            if(w->left->cor && w->right->cor){
                w->cor = false;
                x = x->pai;
            }else{
                if(w->right->cor){
                    w->left->cor = true;
                    w->cor = false;
                    rightRotate(w);
                    w = x->pai->right;
                }
                w->cor = x->pai->cor;
                x->pai->cor = true;
                w->right->cor = true;
                leftRotate(x->pai);
                x = root;
            }
        }else{
            w = x->pai->left;
            if(w->cor == false){
                w->cor = true;
                x->pai->cor = false;
                rightRotate(x->pai);
                w = x->pai->left;
            }
            if(w->right->cor && w->left->cor){
                w->cor = false;
                x = x->pai;
            }else{
                if(w->left->cor){
                    w->right->cor = true;
                    w->cor = false;
                    leftRotate(w);
                    w = x->pai->left;
                }
                w->cor = x->pai->cor;
                x->pai->cor = true;
                w->left->cor = true;
                rightRotate(x->pai);
                x = root;
                }
            }
        }


    x->cor = true;
}

/*
========================================================
      METODOS PUBLICOS:
========================================================
*/
template<class tipo>
void TEMP::remove(tipo elemento){
    SUBARVORE* arvoreRemover = root->search1(elemento);

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
    return *(root->minimo1()->key);
}

template<class tipo>
tipo TEMP::maximo(){
    return *(root->maximo1()->key);
}

template<class tipo>
tipo TEMP::sucessor(tipo elemento){
    SUBARVORE* atual = search1(elemento);
    return *(atual->sucessor1()->key);

}

template<class tipo>
tipo TEMP::predecessor(tipo elemento){
    SUBARVORE* atual = search1(elemento);
    return *(atual->predecessor1()->key);
}

/*
========================================================
       IMPLEMENTAÇAO DAS LISTAGENS:
========================================================
*/
template<class tipo>
std::list<tipo>* TEMP::listarOrdem() const{
    try{
        return root->ordem();
    }catch(std::string &erro){
        throw erro;
    }
}

template<class tipo>
std::list<tipo>* TEMP::listarPreOrdem() const{
    try {
       return root->preOrdem();
    } catch (std::string &erro) {
        throw erro;
    }
}

template<class tipo>
std::list<tipo>* TEMP::listarPosOrdem() const{
    try {
       return root->posOrdem();
    } catch (std::string &erro) {
        throw erro;
    }
}



}//fim da namespace

#endif // ARVORERUBRONEGRA_H
