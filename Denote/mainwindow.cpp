#include "mainwindow.h"
#include "Framework/document.h"
#include "Framework/documentview.h"
#include "Framework/subwindow.h"
#include "Ui/ui.h"
#include "Graphics/page.h"
#include "test.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    createMenus();
    setWindowTitle(tr("Denote"));
    ui = new UI();
    Document *doc = new Document(ui);
    ui->addDocument(doc);

    Page *page1 = new Page();
    page1->setBackgroundType(Engineering);
    doc->addPage(page1);

    Page *page2 = new Page();
    page2->setBackgroundType(Staves);
    doc->addPage(page2);

    Page *page3 = new Page();
    page3->setBackgroundType(Graph);
    doc->addPage(page3);

    DocumentView *docView = new DocumentView(this, doc);
    addDockWidget(Qt::LeftDockWidgetArea,docView);


    test *t = new test();
    setCentralWidget(t);

    //DocumentView *docView2 = new DocumentView(this, doc);
    //addDockWidget(Qt::LeftDockWidgetArea,docView2);

    QMainWindow::setDockOptions(AllowNestedDocks | AnimatedDocks);

    //QCoreApplication::setAttribute(Qt::AA_CompressHighFrequencyEvents);
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


