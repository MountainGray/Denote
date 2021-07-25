#include "mainwindow.h"
#include "Framework/document.h"
#include "Graphics/documentinteractionframe.h"
#include "Graphics/documentsummaryframe.h"
#include "Framework/subwindow.h"
#include "Ui/ui.h"
#include "Graphics/page.h"
#include "Framework/pageitem.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QMainWindow::setDockOptions(AllowNestedDocks | AnimatedDocks);
    QCoreApplication::setAttribute(Qt::AA_CompressHighFrequencyEvents);
    setWindowTitle(tr("Denote Pre-Alpha"));
    createMenus();

    ui = new UI(this);

    addView();
    newDocument();
}


MainWindow::~MainWindow(){

}


void MainWindow::addSubWindow(QDockWidget *widget, Qt::DockWidgetArea area)
{
    addDockWidget(area, widget);
    subWindows.append(widget);
}


void MainWindow::newDocument()
{
    Document *doc = new Document(ui);

    for(int i = 0; i < 3; i++){
        Page* new_page = new Page();
        new_page->setBackgroundType(Engineering);
        new_page->setPageSize(850+200*i,1100-200*i);
        doc->addPage(new_page);
    }

    foreach(DocumentInteractionFrame* view, views){
        view->addDocument(doc);
        view->setDocument(doc);
    }
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


void MainWindow::addView()
{
    DocumentInteractionFrame *new_frame = new DocumentInteractionFrame(this);
    addSubWindow(new_frame, Qt::BottomDockWidgetArea);
    new_frame->addDocument(ui->getActiveDocument());
    views.append(new_frame);
}


void MainWindow::print()
{
    ui->getActiveDocument()->print();
}


void MainWindow::invertView()
{
    foreach(Page* page, ui->getActiveDocument()->getPages()){
        foreach(QGraphicsItem* item, page->items()){
            PageItem* page_item = static_cast<PageItem*>(item);
            if(page_item != nullptr){
                page_item->invertBrightness();
            }
        }
        page->invertBrightness();
        page->update();
        page->updatePortals();
    }
}


void MainWindow::createMenus(){
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(tr("&New..."), this, &MainWindow::newDocument, QKeySequence::New);
    fileMenu->addAction(tr("&Open..."), this, &MainWindow::open, QKeySequence::Open);
    fileMenu->addAction(tr("&Save As..."), this, &MainWindow::save, QKeySequence::SaveAs);
    fileMenu->addAction(tr("E&xit"), this, &MainWindow::close, QKeySequence::Quit);
    fileMenu->addAction(tr("&Print"), this, &MainWindow::print, QKeySequence::Print);

    QMenu* helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(tr("A&bout"), this, &MainWindow::about);
    helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);

    QMenu* view = menuBar()->addMenu("&View");
    view->addAction(tr("Add V&iew"), this, &MainWindow::addView);
    view->addAction("Invert Brightness", this, &MainWindow::invertView);
}
