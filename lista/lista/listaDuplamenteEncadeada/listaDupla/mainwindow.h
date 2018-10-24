#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <qinputdialog.h>
#include "Listadupla.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void atualizarResultado();

private slots:
    void on_pushButtonAdicionarInicio_clicked();

    void on_pushButtonAdicionarFim_clicked();

    void on_pushButtonAdicionarOrdenado_clicked();

    void on_pushButtonRemoverTudo_clicked();

    void on_pushButtonRemoverInicio_clicked();

    void on_pushButtonRemoverFim_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    ListaDupla lista;
};

#endif // MAINWINDOW_H
