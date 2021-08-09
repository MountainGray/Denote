#include "documentinteractionframe.h"
#include "mainwindow.h"
#include "Framework/document.h"
#include "documentinteractionview.h"

#include <QPushButton>
#include <QButtonGroup>


DocumentInteractionFrame::DocumentInteractionFrame(Document* doc)
{
    setMinimumSize(150,150);

    empty_widget = new QLabel();
    empty_widget->setAlignment(Qt::AlignCenter);
    empty_widget->setText("No Documents are Open");

    tab_widget = new QTabWidget();

    tab_widget->setMovable(true);
    tab_widget->setTabsClosable(true);

    QPushButton* shadows = new QPushButton("Shadows");
    shadows->setCheckable(true);
    shadows->setChecked(true);

    QPushButton* holes = new QPushButton("Holes");
    holes->setCheckable(true);
    holes->setChecked(true);

    QPushButton* vertical = new QPushButton("Vertical");
    vertical->setCheckable(true);
    QPushButton* horizontal = new QPushButton("Horizontal");
    horizontal->setCheckable(true);
    QPushButton* seamless = new QPushButton("Seamless");
    seamless->setCheckable(true);
    QPushButton* ftv = new QPushButton("Fit to view");
    ftv->setCheckable(true);
    ftv->setChecked(true);


    QButtonGroup* group = new QButtonGroup();
    group->setExclusive(true);
    group->addButton(vertical);
    group->addButton(horizontal);
    group->addButton(seamless);
    group->addButton(ftv);

    slider = new QSlider(Qt::Orientation::Horizontal);
    slider->setRange(20,500);

    QGridLayout* button_layout = new QGridLayout();
    QSpacerItem* spacer = new QSpacerItem(1,1, QSizePolicy::Expanding);
    button_layout->addItem(spacer,0,0);
    button_layout->addWidget(shadows,0,1);
    button_layout->addWidget(holes,0,2);
    button_layout->addWidget(vertical,0,3);
    button_layout->addWidget(horizontal,0,4);
    button_layout->addWidget(seamless,0,5);
    button_layout->addWidget(ftv,0,6);
    button_layout->addWidget(slider,0,7);

    frame_layout = new QGridLayout();
    frame_layout->setContentsMargins(0,0,0,0);
    frame_layout->addWidget(tab_widget,0,0);
    frame_layout->addLayout(button_layout,1,0);

    layout_widget = new QWidget();
    layout_widget->setLayout(frame_layout);

    addDocument(doc);

    setLayout(frame_layout);

    addDocument(doc);

    setLayout(frame_layout);

    addDocument(doc);

    connect(tab_widget, &QTabWidget::currentChanged, this, &DocumentInteractionFrame::focusCurrentDoc);
    connect(holes, &QPushButton::clicked, this, &DocumentInteractionFrame::setHoles);
    connect(shadows, &QPushButton::clicked, this, &DocumentInteractionFrame::setShadows);
    connect(vertical, &QPushButton::clicked, this, &DocumentInteractionFrame::setVertical);
    connect(horizontal, &QPushButton::clicked, this, &DocumentInteractionFrame::setHorizontal);
    connect(seamless, &QPushButton::clicked, this, &DocumentInteractionFrame::setSeamless);
    connect(ftv, &QPushButton::clicked, this, &DocumentInteractionFrame::setFTV);
    connect(slider, &QSlider::sliderMoved, this, &DocumentInteractionFrame::setScale);

    resetScale();
}


DocumentInteractionFrame::~DocumentInteractionFrame()
{
    delete tab_widget;
}


void DocumentInteractionFrame::setScale(float scale)
{
    if(current_view != nullptr) current_view->setScale(scale/100);
}


void DocumentInteractionFrame::addDocument(Document *doc)
{
    if (doc == nullptr) return;

    DocumentInteractionView* new_viewport = new DocumentInteractionView(doc, this);
    //QString("Untitled %1").arg(tab_widget->count())
    tab_widget->addTab(new_viewport, doc->getName());
    doc->focusDoc();

}


void DocumentInteractionFrame::setDocument(Document *doc)
{
    for(int i = 0; i < tab_widget->count(); i++){
        DocumentInteractionView* view = static_cast<DocumentInteractionView*>(tab_widget->widget(i));
        if(view != nullptr and view->getDoc() == doc){
            tab_widget->setCurrentIndex(i);
            doc->focusDoc();
            break;
        }
    }
}


void DocumentInteractionFrame::updateDocNames()
{
    for(int i = 0; i < tab_widget->count(); i++){
        DocumentInteractionView* view = static_cast<DocumentInteractionView*>(tab_widget->widget(i));
        if(view != nullptr){
            tab_widget->setTabText(i,view->getDoc()->getName());
        }
    }
}


void DocumentInteractionFrame::resetScale()
{
    if(current_view != nullptr) slider->setValue(current_view->getScale()*100);
}


void DocumentInteractionFrame::focusCurrentDoc()
{
    DocumentInteractionView* view = static_cast<DocumentInteractionView*>(tab_widget->currentWidget());
    if(view != nullptr){
        view->getDoc()->focusDoc();
    }
    current_view = view;
    resetScale();
}


void DocumentInteractionFrame::setHoles(bool holes)
{
    if(current_view != nullptr) current_view->getPageLayoutScene()->setHoles(holes);
}


void DocumentInteractionFrame::setShadows(bool shadows)
{
    if(current_view != nullptr) current_view->getPageLayoutScene()->setShadow(shadows);
}


void DocumentInteractionFrame::setVertical()
{
    if(current_view != nullptr) current_view->getPageLayoutScene()->setLayoutType(PageLayoutScene::Vertical);
}


void DocumentInteractionFrame::setHorizontal()
{
    if(current_view != nullptr) current_view->getPageLayoutScene()->setLayoutType(PageLayoutScene::Horizontal);
}


void DocumentInteractionFrame::setSeamless()
{
    if(current_view != nullptr) current_view->getPageLayoutScene()->setLayoutType(PageLayoutScene::Seamless);
}


void DocumentInteractionFrame::setFTV()
{
    if(current_view != nullptr) current_view->getPageLayoutScene()->setLayoutType(PageLayoutScene::FitToView);
}
