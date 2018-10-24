#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <QString>

class Elemento
{

private:
    int numero;
    Elemento* proximo;
    Elemento* anterior;

public:
    Elemento();
    Elemento(int numero);
    Elemento(Elemento* elemento);

    ~Elemento();




    int inline getNumero() const        { return this->numero;      }
    Elemento* getProximo()              { return this->proximo;     }
    Elemento* getAnterior()             { return this->anterior;    }
    void setNumero(int numero)          { this->numero = numero;    }
    void setProximo(Elemento* proximo)  {this->proximo = proximo;   }
    void setAnterior(Elemento* anterior){this->anterior = anterior; }

    //sobrecarga de operadores:
    bool operator ==(Elemento* elemento)    { return this->getNumero() == elemento->getNumero();}
    bool operator <(Elemento* elemento)     { return this->getNumero() <  elemento->getNumero();}
    bool operator <=(Elemento* elemento)    { return this->getNumero() <= elemento->getNumero();}
    bool operator >(Elemento* elemento)     { return this->getNumero() >  elemento->getNumero();}
    bool operator >=(Elemento* elemento)    { return this->getNumero() >= elemento->getNumero();}
    bool operator !=(Elemento* elemento)    { return this->getNumero() != elemento->getNumero();}



};

#endif // ELEMENTO_H
