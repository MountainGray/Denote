#include "mainwindow.h"
#include "Framework/document.h"
#include "Framework/documentview.h"
#include "Framework/subwindow.h"
#include "Ui/ui.h"
#include "Graphics/page.h"
#include "Framework/ToolMenus/toolmenuviewer.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    createMenus();
    setWindowTitle(tr("Denote"));

    ToolMenuViewer *tool_menu_viewer = new ToolMenuViewer(this);

    ui = new UI(tool_menu_viewer);

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

    DocumentView *doc_view = new DocumentView(this, doc);
    addDockWidget(Qt::LeftDockWidgetArea, doc_view);

    DocumentView *doc_view2 = new DocumentView(this, doc);
    addDockWidget(Qt::LeftDockWidgetArea, doc_view2);

    addDockWidget(Qt::LeftDockWidgetArea, tool_menu_viewer);


    QMainWindow::setDockOptions(AllowNestedDocks | AnimatedDocks);
    QCoreApplication::setAttribute(Qt::AA_CompressHighFrequencyEvents);
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


