#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::atualizarResultado(){
     ui->textEditResultado->setText(lista.listar());
     ui->textEditResultado->setAlignment(Qt::AlignCenter);
}


void MainWindow::on_pushButtonAdicionarInicio_clicked()
{
    try{

        int elemento = QInputDialog::getInt(this, "ADICIONAR ELEMENTO NO INICIO", "Informe o elemento preu adiciona nessa parada");
        Elemento* incluir = new Elemento(elemento);
        lista.incluirInicio(incluir);

        atualizarResultado();
        ui->pushButtonAdicionarOrdenado->setEnabled(false);

    }catch(...){
        QMessageBox::information(this, "ERRO DE SISTEMA", "Erro ao alocar espaço para oturo elemento");
    }
}

void MainWindow::on_pushButtonAdicionarFim_clicked()
{
    try {
       int elemento = QInputDialog::getInt(this, "ADICIONAR ELEMENTO NO FINAL", "Informe o elemento que deseja adicionar");
       Elemento* incluir = new Elemento(elemento);
       lista.incluirFinal(incluir);

       atualizarResultado();
       ui->pushButtonAdicionarOrdenado->setEnabled(false);

    } catch (...) {
         QMessageBox::information(this, "ERRO DE SISTEMA", "Erro ao alocar espaço para oturo elemento");
    }
}

void MainWindow::on_pushButtonAdicionarOrdenado_clicked()
{
    try{

        int elemento = QInputDialog::getInt(this, "ADICIONAR ELEMENTO ORDENADO", "Informe o elemento preu adiciona nessa parada");
        Elemento* incluir = new Elemento(elemento);
        lista.incluirOrdenado(incluir);

        atualizarResultado();


    }catch(...){
        QMessageBox::information(this, "ERRO DE SISTEMA", "Erro ao alocar espaço para oturo elemento");
    }
}

void MainWindow::on_pushButtonRemoverTudo_clicked()
{
   lista.clear();
   atualizarResultado();
   ui->pushButtonAdicionarOrdenado->setEnabled(true);
}

void MainWindow::on_pushButtonRemoverInicio_clicked()
{
    try{

        Elemento* removido = 0;
        removido = lista.retirarInicio();
        if(removido) delete removido;

        atualizarResultado();
        if(lista.empty()) ui->pushButtonAdicionarOrdenado->setEnabled(true);
    }catch(QString &erro){
        QMessageBox::information(this, "ERRO DE SISTEMA", erro);
    }
}

void MainWindow::on_pushButtonRemoverFim_clicked()
{
    try{

        Elemento* removido = 0;
        removido = lista.retirarFinal();
        if(removido) delete removido;

        atualizarResultado();
        if(lista.empty()) ui->pushButtonAdicionarOrdenado->setEnabled(true);
    }catch(QString &erro){
        QMessageBox::information(this, "ERRO DE SISTEMA", erro);
    }
}


void MainWindow::on_pushButton_clicked()
{
    try{
        bool ok;
        if(lista.empty()) throw QString("Lista Vazia");

        int elemento = QInputDialog::getInt(this, "REMOVER ELEMENTO",
                                            "Informe o elemento preu remover nessa parada", 0,
                                            -21474836, 214748264, 1, &ok);
        if(ok){
            Elemento* removido = lista.retirarElemento(elemento);
            delete removido;

            atualizarResultado();
            if(lista.empty()) ui->pushButtonAdicionarOrdenado->setEnabled(true);
        }

    }catch(QString &erro){
        QMessageBox::information(this, "ERRO DE SISTEMA", erro);
    }
}
