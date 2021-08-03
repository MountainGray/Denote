#include "documentsummaryframe.h"
#include "documentsummaryview.h"
#include "mainwindow.h"
#include "page.h"
#include "Framework/document.h"
#include "Graphics/pagelayoutscene.h"
#include "Graphics/pageportal.h"


DocumentSummaryFrame::DocumentSummaryFrame(MainWindow *parent) : SubWindow(parent)
{
    setMinimumSize(35,150);

    page_combo = new QComboBox();
    page_combo->addItems({"Engineering", "Graph", "Lines", "LinesMargin", "Staves"});
    page_combo->setCurrentIndex(0);

    new_button = new QPushButton("New Page");
    up_button = new QPushButton("Up");
    down_button = new QPushButton("Down");
    page_width = new QSpinBox();
    page_height = new QSpinBox();
    page_width->setMaximum(10000);
    page_height->setMaximum(10000);
    page_width->setValue(850);
    page_height->setValue(1100);

    button_layout = new QGridLayout();
    button_layout->addWidget(page_combo,0,0);
    button_layout->addWidget(new_button,1,0);
    button_layout->addWidget(up_button,2,0);
    button_layout->addWidget(down_button,3,0);
    button_layout->addWidget(page_width,4,0);
    button_layout->addWidget(page_height,5,0);

    frame_widget = new QWidget();
    setWidget(frame_widget);

    frame_layout = new QGridLayout();
    frame_widget->setLayout(frame_layout);

    empty_widget = new QLabel();
    empty_widget->setAlignment(Qt::AlignCenter);
    empty_widget->setText("No Documents are Open");
    frame_layout->addWidget(empty_widget,0,0);

    connect(new_button, &QPushButton::clicked, this, &DocumentSummaryFrame::addPage);
    connect(up_button, &QPushButton::clicked, this, &DocumentSummaryFrame::raisePage);
    connect(down_button, &QPushButton::clicked, this, &DocumentSummaryFrame::lowerPage);
    connect(this, &QDockWidget::topLevelChanged, this, &DocumentSummaryFrame::resetGL);
}


DocumentSummaryFrame::~DocumentSummaryFrame()
{
    delete viewport;
}


void DocumentSummaryFrame::setView(DocumentSummaryView* new_viewport)
{
    if(new_viewport == nullptr) return;

    if(frame_layout->count() == 1){//empty
        delete empty_widget;
        frame_layout->addWidget(new_viewport,0,0);
        frame_layout->addLayout(button_layout,1,0);
    } else {
        frame_layout->removeWidget(viewport);
        viewport->setVisible(false);
        frame_layout->addWidget(new_viewport,0,0);
        new_viewport->setVisible(true);
    }
    viewport = new_viewport;
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
        page->setPageSize(page_width->value(),page_height->value());
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
