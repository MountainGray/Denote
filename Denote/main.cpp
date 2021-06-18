#include "mainwindow.h"

#include "tabletapplication.h"


int main(int argc, char *argv[])
{
    TabletApplication a(argc, argv);
    MainWindow w;
    a.setUI(w.getUI());
    w.resize(1200,600);
    w.show();
    return a.exec();
}
