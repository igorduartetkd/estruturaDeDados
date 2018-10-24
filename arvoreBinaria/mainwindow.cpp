#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    igor::ArvoreBinaria<int> arvore1;

    arvore1.insert(2);
    arvore1.insert(1);
    arvore1.insert(3);
    arvore1.insert(4);
    arvore1.insert(0);

    igor::ArvoreBinaria<int> arvore(arvore1);
    arvore.remove(arvore.sucessor(arvore.minimo()));

    std::list<int>* show = arvore.listarOrdem();

    QString saida;

    while(!show->empty()){
        saida += QString::number(show->front()) + "; ";
        show->pop_front();
    }
    QMessageBox::information(this, "Teste Listando Ordem", saida);

    delete show;
    show = arvore.listarPreOrdem();
    saida.clear();

    while(!show->empty()){
        saida += QString::number(show->front()) + "; ";
        show->pop_front();

    }
    QMessageBox::information(this, "Teste Listando pre-ordem", saida);


    delete show;
    show = arvore.listarPosOrdem();
    saida.clear();

    while(!show->empty()){
        saida += QString::number(show->front()) + "; ";
        show->pop_front();

    }
    QMessageBox::information(this, "Teste Listando pos-ordem", saida);


    delete  show;

    //saida = QString::number(*(arvore.search(3)));
    //QMessageBox::information(this, "Teste", saida);
    /*
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}
