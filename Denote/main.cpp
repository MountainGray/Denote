#include "mainwindow.h"

#include "application.h"
#include <QSurfaceFormat>


int main(int argc, char *argv[])
{
    Application a(argc, argv);

    QSurfaceFormat format;
    format.setSamples(6);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    /*
    QPalette p = a.palette();
    p.setBrush(QPalette::Window, QBrush(QColor(50,50,50)));
    p.setBrush(QPalette::WindowText, QBrush(QColor(240,240,240)));
    p.setBrush(QPalette::Base, QBrush(QColor(50,50,50)));
    p.setBrush(QPalette::AlternateBase, QBrush(QColor(50,50,50)));
    p.setBrush(QPalette::ToolTipBase, QBrush(QColor(100,100,100)));
    p.setBrush(QPalette::Text, QBrush(QColor(240,240,240)));
    p.setBrush(QPalette::Button, QBrush(QColor(50,50,50)));
    p.setBrush(QPalette::ButtonText, QBrush(QColor(240,240,240)));
    p.setBrush(QPalette::BrightText, QBrush(QColor(255,255,255)));
    p.setBrush(QPalette::NoRole, QBrush(QColor(50,50,50)));
    p.setBrush(QPalette::Light, QBrush(QColor(50,50,50)));
    p.setBrush(QPalette::Midlight, QBrush(QColor(50,50,50)));
    p.setBrush(QPalette::Dark, QBrush(QColor(50,50,50)));
    p.setBrush(QPalette::Mid, QBrush(QColor(50,50,50)));
    p.setBrush(QPalette::Shadow, QBrush(QColor(50,50,50)));
    a.setPalette(p);
    */

    MainWindow w;
    a.setUI(w.getUI());
    w.resize(1200,600);
    w.showMaximized();
    w.show();
    return a.exec();
}
