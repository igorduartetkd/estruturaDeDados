#include <QCoreApplication>
#include "arvoreRubroNegra.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    igor::ArvoreRubroNegra<int> arvore1;

    arvore1.insert(5);
    arvore1.insert(2);
    arvore1.insert(1);
    arvore1.insert(0);
    arvore1.insert(10);
    arvore1.insert(9);
    arvore1.insert(11);

    arvore1.remove(2);
    arvore1.remove(5);
    arvore1.remove(1);
    arvore1.remove(10);


    std::list<int>* elementos = arvore1.listarOrdem();

    std::cout<<"Listar Ordem:"<<std::endl;

    while(!elementos->empty()){
        std::cout<<elementos->front()<<"  ";
        elementos->pop_front();
    }
    std::cout<<std::endl<<std::endl;
    delete elementos;


    elementos = arvore1.listarPreOrdem();

    std::cout<<"Listar Pre-Ordem:"<<std::endl;

    while(!elementos->empty()){
        std::cout<<elementos->front()<<"  ";
        elementos->pop_front();
    }
    std::cout<<std::endl<<std::endl;
    delete elementos;


    elementos = arvore1.listarPosOrdem();

    std::cout<<"Listar Pos-Ordem:"<<std::endl;

    while(!elementos->empty()){
        std::cout<<elementos->front()<<"  ";
        elementos->pop_front();
    }
    std::cout<<std::endl;
    delete elementos;

    return a.exec();
}
