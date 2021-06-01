#include "mainwindow.h"
#include "document.h"
#include "documentview.h"
#include "subwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    createMenus();
    setWindowTitle(tr("Denote"));
    Document *doc = new Document();

    DocumentView *docView = new DocumentView(this, doc);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, docView);
    subWindows.append(docView);

    DocumentView *docView2 = new DocumentView(this, doc);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, docView2);
    subWindows.append(docView2);

    DocumentView *docView3 = new DocumentView(this, doc);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, docView3);
    subWindows.append(docView3);

    DocumentView *docView4 = new DocumentView(this, doc);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, docView4);
    subWindows.append(docView4);


    QMainWindow::setDockOptions(AllowNestedDocks | AnimatedDocks);
}


MainWindow::~MainWindow(){
}


bool MainWindow::save(){
    return false;
}

void MainWindow::open(){
    
}


void MainWindow::about() {
    QMessageBox::about(this, tr("Denote"),
                       tr("Best app ever!"));
}

void MainWindow::createMenus(){
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(tr("&Open..."), this, &MainWindow::open, QKeySequence::Open);
    fileMenu->addAction(tr("&Save As..."), this, &MainWindow::save, QKeySequence::SaveAs);
    fileMenu->addAction(tr("E&xit"), this, &MainWindow::close, QKeySequence::Quit);

    QMenu *helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(tr("A&bout"), this, &MainWindow::about);
    helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
}


