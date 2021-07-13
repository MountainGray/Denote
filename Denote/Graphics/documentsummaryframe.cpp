#include "documentsummaryframe.h"
#include "documentsummaryview.h"
#include "mainwindow.h"
#include "page.h"
#include "Framework/document.h"

#include <QtOpenGLWidgets/QOpenGLWidget>



DocumentSummaryFrame::DocumentSummaryFrame(MainWindow *parent, Document* doc) : SubWindow(parent)
{
    this->doc = doc;
    viewport = new DocumentSummaryView(doc);

    QOpenGLWidget *gl = new QOpenGLWidget();
    QSurfaceFormat format;
    format.setSamples(5);
    gl->setFormat(format);
    viewport->setViewport(gl);

    setMinimumSize(80,150);

    page_combo = new QComboBox();
    page_combo->addItems({"Engineering", "Graph", "Lines", "LinesMargin", "Staves"});
    page_combo->setCurrentIndex(0);

    new_button = new QPushButton("New Page");

    menu_layout = new QGridLayout();
    menu_layout->addWidget(viewport,0,0);
    menu_layout->addWidget(page_combo,1,0);
    menu_layout->addWidget(new_button,2,0);

    menu_widget = new QWidget();
    menu_widget->setLayout(menu_layout);
    setWidget(menu_widget);

    connect(new_button, &QPushButton::clicked, this, &DocumentSummaryFrame::addPage);
}


void DocumentSummaryFrame::addPage()
{
    Page* page = new Page();
    if(page_combo->currentText() == "Engineering"){
        page->setBackgroundType(BackgroundType::Engineering);
    } else if(page_combo->currentText() == "Graph"){
        page->setBackgroundType(BackgroundType::Graph);
    } else if(page_combo->currentText() == "Lines"){
        page->setBackgroundType(BackgroundType::Lines);
    } else if(page_combo->currentText() == "LinesMargin"){
        page->setBackgroundType(BackgroundType::LinesMargin);
    } else if(page_combo->currentText() == "Staves"){
        page->setBackgroundType(BackgroundType::Staves);
    } else {
        page->setBackgroundType(BackgroundType::Engineering);
    }
    doc->addPage(page);
}
