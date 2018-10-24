#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{

    //5 linhas abaixo para funcionar acentuaçao grafica:
      QTextCodec *linuxCodec = QTextCodec::codecForName("UTF-8");
      QTextCodec::setCodecForTr(linuxCodec);
      QTextCodec::setCodecForCStrings(linuxCodec);
      QTextCodec::setCodecForLocale(linuxCodec);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
