#include "documentsummaryframe.h"
#include "documentsummaryview.h"
#include "mainwindow.h"
#include "page.h"
#include "Framework/document.h"
#include "Graphics/pagelayoutscene.h"
#include "Graphics/pageportal.h"




DocumentSummaryFrame::DocumentSummaryFrame()
{
    setMinimumSize(35,150);

    stack = new QStackedWidget();

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

    frame_layout = new QGridLayout();
    frame_layout->setContentsMargins(0,0,0,0);
    frame_layout->addWidget(stack,0,0);
    frame_layout->addLayout(button_layout,1,0);
    setLayout(frame_layout);

    //empty not in use rn
    empty_widget = new QLabel();
    empty_widget->setAlignment(Qt::AlignCenter);
    empty_widget->setText("No Documents are Open");

    connect(new_button, &QPushButton::clicked, this, &DocumentSummaryFrame::addPage);
    connect(up_button, &QPushButton::clicked, this, &DocumentSummaryFrame::raisePage);
    connect(down_button, &QPushButton::clicked, this, &DocumentSummaryFrame::lowerPage);
}


DocumentSummaryFrame::~DocumentSummaryFrame()
{
    delete summary_view;
}


void DocumentSummaryFrame::addSummaryView(DocumentSummaryView *view)
{
    stack->addWidget(view);
    setSummaryView(view);
}


void DocumentSummaryFrame::setSummaryView(DocumentSummaryView* view)
{
    if(stack->indexOf(view) == -1){
        addSummaryView(view);
    } else {
        stack->setCurrentWidget(view);
        view->scaleToFit();
        summary_view = view;
    }
}


void DocumentSummaryFrame::addPage()
{
    if(summary_view == nullptr) return;

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
    foreach(PagePortal* portal, summary_view->getPageLayoutScene()->getPortals()){
        if(portal->isSelected()){
            index = summary_view->getDoc()->getPages().indexOf(portal->getPage()) + 1;
        }
    }
    summary_view->getDoc()->addPage(page, index);
}


void DocumentSummaryFrame::raisePage()
{
    if(summary_view == nullptr) return;

    foreach(PagePortal* portal, summary_view->getPageLayoutScene()->getPortals()){
        if(portal->isSelected()){
            int index = summary_view->getDoc()->getPages().indexOf(portal->getPage()) - 1;
            summary_view->getDoc()->movePage(portal->getPage(), index);
        }
    }
}


void DocumentSummaryFrame::lowerPage()
{
    if(summary_view == nullptr) return;

    foreach(PagePortal* portal, summary_view->getPageLayoutScene()->getPortals()){
        if(portal->isSelected()){
            int index = summary_view->getDoc()->getPages().indexOf(portal->getPage()) + 1;
            summary_view->getDoc()->movePage(portal->getPage(), index);
        }
    }
}
