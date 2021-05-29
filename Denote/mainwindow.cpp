#include "mainwindow.h"
#include "document.h"
#include "documentview.h"
#include "subwindow.h"


#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    createMenus();
    setWindowTitle(tr("Denote"));

    Document *doc = new Document();
    DocumentView *doc_view = new DocumentView(doc);
    SubWindow *sub = new SubWindow(this, doc_view);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, sub);

    subWindows.append(sub);

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
