#include "Framework/document.h"
#include "Graphics/documentinteractionframe.h"
#include "Graphics/documentsummaryframe.h"
#include "Ui/ui.h"
#include "Graphics/page.h"
#include "Framework/pageitem.h"
#include "Tools/tool.h"
#include "Graphics/pagelayoutscene.h"

#include <QMessageBox>
#include <QFileDialog>

#include "Framework/History/historymanagerviewer.h"
#include "Framework/toollibrary.h"
#include "Framework/toolmenuviewer.h"
#include "Graphics/documentsummaryframe.h"
#include "Framework/fileviewer.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QSplitter>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    QMainWindow::setDockOptions(AllowNestedDocks | AnimatedDocks);
    QCoreApplication::setAttribute(Qt::AA_CompressHighFrequencyEvents);
    setWindowTitle(tr("Denote Pre-Alpha"));
    createMenus();

    ui = new UI(this);

    QTabWidget* tabs = new QTabWidget();
    tabs->setMovable(true);
    tabs->setTabBarAutoHide(true);
    tabs->setTabPosition(QTabWidget::West);

    DocumentSummaryFrame* pages = new DocumentSummaryFrame();
    HistoryManagerViewer* history = new HistoryManagerViewer();
    ToolMenuViewer* settings = new ToolMenuViewer();
    ui->setWindows(pages, history, settings);
    ToolLibrary* tools = new ToolLibrary(ui);
    ui->setToolLibrary(tools);
    FileViewer* file_viewer = new FileViewer();

    tabs->addTab(pages, "Pages");
    tabs->addTab(history, "History");
    tabs->addTab(tools, "Tools");
    tabs->addTab(settings, "Tool Settings");
    tabs->addTab(file_viewer, "File Viewer");

    DocumentInteractionFrame *central_view = new DocumentInteractionFrame(ui->getActiveDocument());

    QSplitter* splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(tabs);
    splitter->addWidget(central_view);

    setCentralWidget(splitter);
    views.append(central_view);

    newDocument();
}


MainWindow::~MainWindow(){

}


void MainWindow::newDocument()
{
    Document *doc = new Document(ui);

    Page* new_page = new Page();
    doc->addPage(new_page);

    foreach(DocumentInteractionFrame* view, views){
        view->addDocument(doc);
        view->setDocument(doc);
    }
}


void MainWindow::save(){
    QString file_name = QFileDialog::getSaveFileName(this->getUI()->getMain(),
        tr("Save Denote Document"), "",
        tr("Denote Document (*.denote);;All Files (*)"));
    if(file_name.isEmpty())
        return;

    QFile file(file_name);
    QFileInfo file_info(file_name);

    if(!file.open(QIODevice::WriteOnly)){
        QMessageBox::information(this->getUI()->getMain(), tr("Unable to open file"),
            file.errorString());
    }
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_1);
    ui->getActiveDocument()->serializeWrite(out);
    ui->getActiveDocument()->setName(file_info.baseName());
    data = qCompress(data, 9);
    file.write(data);
    file.close();
}


void MainWindow::open(){
    QString file_name = QFileDialog::getOpenFileName(this->getUI()->getMain(),
        tr("Open Denote Document"), "",
        tr("Denote Document (*.denote);;All Files (*)"));
    if(file_name.isEmpty())
        return;

    QFile file(file_name);
    QFileInfo file_info(file_name);

    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(this->getUI()->getMain(), tr("Unable to open file"),
            file.errorString());
    }
    QByteArray data = file.readAll();
    data = qUncompress(data);
    QDataStream in(&data, QIODevice::ReadOnly);
    if(in.version() != QDataStream::Qt_6_1){
        QMessageBox::information(this->getUI()->getMain(), tr("Unable to open file"), tr("File version is not compatible"));
        return;
    }

    Document *new_doc = new Document(ui);
    new_doc->setName(file_info.baseName());
    new_doc->serializeRead(in);
    ui->setDisplayMode(ui->getDisplayMode());
    foreach(DocumentInteractionFrame* view, views){
        view->addDocument(new_doc);
        view->setDocument(new_doc);
    }
    file.close();
}


void MainWindow::about() {
    QMessageBox::about(this, tr("Denote"),
                       tr("Best app ever!"));
}


void MainWindow::addView()
{
    DocumentInteractionFrame *new_view = new DocumentInteractionFrame(ui->getActiveDocument());
    new_view->resize(1000,500);
    new_view->show();

}


void MainWindow::convertToEndless()
{
    ui->getActiveDocument()->convertToEndless();
}


void MainWindow::convertToPages()
{
    ui->getActiveDocument()->convertToPages();
}


void MainWindow::toggleCropWorkArea()
{
    if(ui->getActiveLayout()->getLayoutType() == PageLayoutScene::Seamless){
        ui->getActiveLayout()->setLayoutType(PageLayoutScene::FitToView);
    } else {
        ui->getActiveLayout()->setLayoutType(PageLayoutScene::Seamless);
    }
}


void MainWindow::print()
{
    IColor::DisplayMode mode = ui->getDisplayMode();
    ui->setDisplayMode(IColor::DisplayMode::Normal);
    ui->getActiveDocument()->print();
    ui->setDisplayMode(mode);
}


void MainWindow::invertView()
{
    IColor::DisplayMode new_mode = ui->getDisplayMode() == IColor::Inverted ? IColor::Normal : IColor::Inverted;
    ui->setDisplayMode(new_mode);
}


void MainWindow::toggleHoles()
{
    ui->getActiveLayout()->setHoles(!ui->getActiveLayout()->hasHoles());
}


void MainWindow::toggleShadow()
{
    ui->getActiveLayout()->setShadow(!ui->getActiveLayout()->hasShadow());
}


void MainWindow::createMenus(){
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(tr("&New..."), this, &MainWindow::newDocument, QKeySequence::New);
    fileMenu->addAction(tr("&Open..."), this, &MainWindow::open, QKeySequence::Open);
    fileMenu->addAction(tr("&Save As..."), this, &MainWindow::save, QKeySequence::SaveAs);
    fileMenu->addAction(tr("&Print"), this, &MainWindow::print, QKeySequence::Print);
    fileMenu->addAction(tr("E&xit"), this, &MainWindow::close, QKeySequence::Quit);

    QMenu* helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(tr("A&bout"), this, &MainWindow::about);
    helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);

    QMenu* view = menuBar()->addMenu("&View");
    view->addAction(tr("Add V&iew"), this, &MainWindow::addView);
    view->addAction(tr("Convert to E&ndless Document"), this, &MainWindow::convertToEndless);
    view->addAction(tr("Convert to P&aged Document"), this, &MainWindow::convertToPages);
    view->addAction("Invert View", this, &MainWindow::invertView, QKeySequence("Ctrl+I"));
    view->addAction(tr("Toggle S&eamless View"), this, &MainWindow::toggleCropWorkArea);
    view->addAction("Toggle Hole Punches", this, &MainWindow::toggleHoles);
    view->addAction("Toggle Page Shad&ows", this, &MainWindow::toggleShadow);
}
