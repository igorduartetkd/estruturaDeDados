#include "Elemento.h"

Elemento::Elemento():
    numero(0),
    proximo(0),
    anterior(0)
{
}

Elemento::Elemento(int numero):
    numero(numero),
    proximo(0),
    anterior(0)
{
}

Elemento::Elemento(Elemento* elemento):
    numero(elemento->getNumero()),
    proximo(elemento->getProximo()),
    anterior(elemento->getAnterior())

{
}

Elemento::~Elemento()
{
    if(this->proximo){

        delete this->proximo;
        this->proximo = 0;
    }

}





