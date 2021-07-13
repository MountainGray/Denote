#include "mainwindow.h"
#include "Framework/document.h"
#include "Graphics/documentinteractionframe.h"
#include "Graphics/documentsummaryframe.h"
#include "Framework/subwindow.h"
#include "Ui/ui.h"
#include "Graphics/page.h"
#include "Framework/toolmenuviewer.h"
#include "Tools/pen.h"
#include "Tools/fill.h"
#include "Tools/eraser.h"
#include "Framework/toollibrary.h"
#include "Tools/selectionbox.h"
#include "Tools/circleselect.h"
#include "Tools/lassoselect.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    createMenus();
    setWindowTitle(tr("Denote"));

    ToolLibrary *tool_library = new ToolLibrary(this);
    subWindows.append(tool_library);

    ToolMenuViewer *tool_menu_viewer = new ToolMenuViewer(this);
    subWindows.append(tool_menu_viewer);

    ui = new UI(tool_menu_viewer, tool_library);

    Document *doc = new Document(ui);
    ui->setActiveDocument(doc);

    Page *page1 = new Page();
    page1->setBackgroundType(Engineering);
    doc->addPage(page1);

    Page *page2 = new Page();
    page2->setBackgroundType(Staves);
    doc->addPage(page2);

    Page *page3 = new Page();
    page3->setBackgroundType(Graph);
    doc->addPage(page3);

    Page *page4 = new Page();
    page4->setBackgroundType(LinesMargin);
    page4->setPageSize(1100,850);
    doc->addPage(page4);

    Page *page5 = new Page();
    page5->setBackgroundType(Engineering);
    page5->setPageSize(1100,850);
    doc->addPage(page5);

    Page *page6 = new Page();
    page6->setBackgroundType(Graph);
    doc->addPage(page6);



    QMainWindow::setDockOptions(AllowNestedDocks | AnimatedDocks);

    DocumentInteractionFrame *interaction_frame = new DocumentInteractionFrame(this, doc);
    subWindows.append(interaction_frame);
    interaction_frame->setScale(1.2);

    DocumentSummaryFrame *summary_frame = new DocumentSummaryFrame(this, doc);
    subWindows.append(summary_frame);

    for(int i = 0; i < 5; i ++){
        Pen *pen = new Pen(ui);
        QColor color;
        color.setHsv(i*36,255,255);
        pen->setColor(color);
        pen->setWidth(i*2+4);
        ui->addTool(pen);
    }
    for(int i = 0; i < 4; i ++){
        Fill *fill = new Fill(ui);
        QColor color;
        color.setHsv(i*36,255,255);
        fill->setColor(color);
        ui->addTool(fill);
    }
    ui->addTool(new Eraser(ui));
    SelectionBox* box = new SelectionBox(ui);
    ui->addTool(box);
    ui->addTool(new CircleSelect(ui, box));
    ui->addTool(new LassoSelect(ui, box));

    addDockWidget(Qt::TopDockWidgetArea, tool_library);
    addDockWidget(Qt::BottomDockWidgetArea, summary_frame);
    addDockWidget(Qt::BottomDockWidgetArea, interaction_frame);
    addDockWidget(Qt::BottomDockWidgetArea, tool_menu_viewer);

    //resizeDocks(subWindows, {2000, 120, 1000, 100}, Qt::Orientation::Horizontal);

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


