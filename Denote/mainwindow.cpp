#include "mainwindow.h"
#include "document.h"
#include "documentview.h"
#include "subwindow.h"
#include "page.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    createMenus();
    setWindowTitle(tr("Denote"));
    Document *doc = new Document();

    Page *page1 = new Page();
    page1->setBackgroundType(Engineering);
    doc->addPage(page1);

    Page *page2 = new Page();
    page2->setBackgroundType(LinesMargin);
    doc->addPage(page2);

    Page *page3 = new Page();
    page3->setBackgroundType(Lines);
    doc->addPage(page3);

    DocumentView *docView = new DocumentView(this, doc);
    addDockWidget(Qt::LeftDockWidgetArea,docView);

    DocumentView *docView2 = new DocumentView(this, doc);
    addDockWidget(Qt::LeftDockWidgetArea,docView2);

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


