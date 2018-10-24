#ifndef LISTADUPLA_H
#define LISTADUPLA_H

#include <QString>
#include <QMessageBox>
#include <QInputDialog>
#include "Elemento.h"


class ListaDupla
{
private:
    Elemento* primeiro;
    Elemento* ultimo;
    int tamanho;

    //metodos privados:


public:
    ListaDupla();
    ListaDupla(Elemento* elemento);
    ~ListaDupla();

    //metodos para retirar elemento:
    Elemento* retirarInicio();
    Elemento* retirarFinal();
    Elemento* retirarElemento(int elemento);

    //metodos para incluir elemento:
    void incluirInicio(Elemento* elemento);
    void incluirFinal(Elemento* elemento);
    void incluirOrdenado(Elemento* elemento);



    Elemento* buscarElemento(int elemento);
    void ordenar();
    QString listar() const;
    bool empty() const;
    void clear() { if(primeiro) delete primeiro; primeiro = ultimo = 0; tamanho = 0;}


};

#endif // LISTADUPLA_H
