#include "documentsummaryframe.h"
#include "documentsummaryview.h"
#include "mainwindow.h"
#include "page.h"
#include "Framework/document.h"
#include "Graphics/pagelayoutscene.h"
#include "Graphics/pageportal.h"


DocumentSummaryFrame::DocumentSummaryFrame(MainWindow *parent) : SubWindow(parent)
{
    setMinimumSize(50,150);

    page_combo = new QComboBox();
    page_combo->addItems({"Engineering", "Graph", "Lines", "LinesMargin", "Staves"});
    page_combo->setCurrentIndex(0);

    new_button = new QPushButton("New Page");
    up_button = new QPushButton("Up");
    down_button = new QPushButton("Down");

    button_layout = new QGridLayout();
    button_layout->addWidget(page_combo,0,0);
    button_layout->addWidget(new_button,1,0);
    button_layout->addWidget(up_button,0,1);
    button_layout->addWidget(down_button,1,1);

    frame_layout = new QGridLayout();

    frame_widget = new QWidget();
    frame_widget->setLayout(frame_layout);

    empty_widget = new QLabel();
    empty_widget->setAlignment(Qt::AlignCenter);
    empty_widget->setText("No Documents are Open");
    setWidget(empty_widget);

    connect(new_button, &QPushButton::clicked, this, &DocumentSummaryFrame::addPage);
    connect(up_button, &QPushButton::clicked, this, &DocumentSummaryFrame::raisePage);
    connect(down_button, &QPushButton::clicked, this, &DocumentSummaryFrame::lowerPage);
    connect(this, &QDockWidget::topLevelChanged, this, &DocumentSummaryFrame::resetGL);
}


DocumentSummaryFrame::~DocumentSummaryFrame()
{
    delete viewport;
}


void DocumentSummaryFrame::setView(DocumentSummaryView* view)
{
    if(frame_layout->isEmpty()){
        frame_layout->addWidget(view,0,0);
        frame_layout->addLayout(button_layout,1,0);
        setWidget(frame_widget);
    } else {
        frame_layout->removeWidget(viewport);
        frame_layout->addWidget(view,0,0);
    }
    viewport = view;
    viewport->getPageLayoutScene()->updatePageLayout();
}


void DocumentSummaryFrame::addPage()
{
    if(viewport != nullptr){
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
        int index = -1;
        foreach(PagePortal* portal, viewport->getPageLayoutScene()->getPortals()){
            if(portal->isSelected()){
                index = viewport->getDoc()->getPages().indexOf(portal->getPage()) + 1;
            }
        }
        viewport->getDoc()->addPage(page, index);
    }
}


void DocumentSummaryFrame::raisePage()
{
    if(viewport != nullptr){
        foreach(PagePortal* portal, viewport->getPageLayoutScene()->getPortals()){
            if(portal->isSelected()){
                int index = viewport->getDoc()->getPages().indexOf(portal->getPage()) - 1;
                viewport->getDoc()->movePage(portal->getPage(), index);
            }
        }
    }
}


void DocumentSummaryFrame::lowerPage()
{
    if(viewport != nullptr){
        foreach(PagePortal* portal, viewport->getPageLayoutScene()->getPortals()){
            if(portal->isSelected()){
                int index = viewport->getDoc()->getPages().indexOf(portal->getPage()) + 1;
                viewport->getDoc()->movePage(portal->getPage(), index);
            }
        }
    }
}


void DocumentSummaryFrame::resetGL()
{
    viewport->resetGL();
}
