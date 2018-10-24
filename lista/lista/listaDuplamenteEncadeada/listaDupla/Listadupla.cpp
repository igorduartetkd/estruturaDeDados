#include "Listadupla.h"

ListaDupla::ListaDupla():
    primeiro(0),
    ultimo(0),
    tamanho(0)
{
}

ListaDupla::ListaDupla(Elemento *elemento):
    primeiro(elemento),
    ultimo(elemento),
    tamanho(1)
{
}

ListaDupla::~ListaDupla(){
    if(primeiro)    delete primeiro;
}



//metodos para retirar elemento:
Elemento* ListaDupla::retirarInicio(){
    if(tamanho == 0) throw QString("Lista vazia");

    Elemento* retirado = primeiro;

    primeiro = retirado->getProximo();
    retirado->setAnterior(0);
    retirado->setProximo(0);

    if(tamanho == 1){
        ultimo = 0;
    }else{
        primeiro->setAnterior(0);
    }

    tamanho--;
    return retirado;
}

Elemento* ListaDupla::retirarFinal(){

    if(tamanho == 0) throw QString("Lista vazia");

    Elemento* retirado = ultimo;

    ultimo = retirado->getAnterior();
    retirado->setAnterior(0);
    retirado->setProximo(0);

    if(tamanho == 1){
        primeiro = 0;
    }else{
        ultimo->setProximo(0);
    }

    tamanho--;
    return retirado;
}

Elemento* ListaDupla::retirarElemento(int elemento){
    if(tamanho == 0) throw QString("Lista vazia");

    try{
        Elemento* retirado = buscarElemento(elemento);

        if(tamanho == 1){
            primeiro = 0;
            ultimo = 0;
        }else{
            if(retirado == ultimo){
                ultimo = retirado->getAnterior();
                ultimo->setProximo(0);
            }else{
                if(retirado == primeiro){
                    primeiro = retirado->getProximo();
                    primeiro->setAnterior(0);
            }else{
                    retirado->getAnterior()->setProximo(retirado->getProximo());
                    retirado->getProximo()->setAnterior(retirado->getAnterior());
                }
            }
        }

        retirado->setAnterior(0);
        retirado->setProximo(0);

        tamanho--;
        return retirado;

    }catch(QString &erro){
        throw erro;
    }
}
//fim dos metodos para retirar elemento

//metodos para incluir elemento:
void ListaDupla::incluirInicio(Elemento* elemento){
    if(tamanho == 0){
        primeiro = elemento;
        ultimo = elemento;
    }else{
        elemento->setProximo(primeiro);
        primeiro->setAnterior(elemento);
        primeiro = elemento;
    }

    tamanho++;
}

void ListaDupla::incluirFinal(Elemento* elemento){
    if(tamanho == 0){
        primeiro = elemento;
        ultimo = elemento;
    }else{
        ultimo->setProximo(elemento);
        elemento->setAnterior(ultimo);
        ultimo = elemento;
    }

    tamanho++;
}

void ListaDupla::incluirOrdenado(Elemento* elemento){
    if(tamanho == 0){
        primeiro = elemento;
        ultimo = elemento;
    }else{
        Elemento* maior = primeiro;

        while(maior != 0 && (*maior) < elemento ){
            maior = maior->getProximo();
        }

        if(maior == 0){
            this->incluirFinal(elemento);
        }else{
            if(maior == primeiro){
                this->incluirInicio(elemento);
            }else{
                elemento->setProximo(maior);
                elemento->setAnterior(maior->getAnterior());
                elemento->getAnterior()->setProximo(elemento);
                maior->setAnterior(elemento);
            }
        }
    }

    tamanho++;

}

//fim dos metodos para incluir elemento.


Elemento* ListaDupla::buscarElemento(int elemento){
    if(tamanho == 0) throw QString("Lista vazia");
    Elemento* saida = primeiro;

    while(saida != 0){
        if(elemento == saida->getNumero()){
            return saida;
        }
        saida = saida->getProximo();
    }

    throw QString("Elemento nao existe na lista");
}



QString ListaDupla::listar() const{
    QString saida;

    if(this->empty()){
        saida = "Lista Vazia";
    }else{
        Elemento* atual = this->primeiro;

        do{
            saida += QString::number(atual->getNumero()) + "  ";
            atual = atual->getProximo();
        }while(atual);
    }

    return saida;
}


bool ListaDupla::empty() const{
    if(primeiro == 0){
        return true;
    }

    return false;
}
