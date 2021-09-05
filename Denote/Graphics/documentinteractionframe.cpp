#include "documentinteractionframe.h"
#include "mainwindow.h"
#include "Framework/document.h"
#include "documentinteractionview.h"
#include "Graphics/pagelayoutscene.h"
#include "Graphics/page.h"

#include <QAction>
#include <QActionGroup>
#include <QToolButton>
#include <QLabel>

DocumentInteractionFrame::DocumentInteractionFrame(UI* ui, Document* doc)
{
    this->ui = ui;
    setMinimumSize(100,100);
    setupWidgets();

    addDocument(doc);
    setCurrentDocument(doc);
}


DocumentInteractionFrame::~DocumentInteractionFrame()
{
    delete tabs;
    delete view_stack;
}


void DocumentInteractionFrame::setScale(float scale)
{
    if(viewports.isEmpty()) return;
    viewports.at(tabs->currentIndex())->setScale(scale/100);
}


void DocumentInteractionFrame::addDocument(Document *doc)
{
    if (doc == nullptr) return;
    DocumentInteractionView* new_viewport = new DocumentInteractionView(doc, this);

    view_stack->addWidget(new_viewport);
    viewports.append(new_viewport);
    tabs->addTab(doc->getName());
    doc->focusDoc();
}


void DocumentInteractionFrame::setCurrentDocument(Document *doc)
{
    if(doc == nullptr) return;

    for(int i = 0; i < viewports.length(); i++){
        if(viewports.at(i)->getDoc() == doc){
            setCurrentIndex(i);
            return;
        }
    }
}


void DocumentInteractionFrame::setCurrentIndex(int i)
{
    if(i < 0 or i > viewports.size()) return;

    tabs->setCurrentIndex(i);
    view_stack->setCurrentWidget(viewports.at(i));
    viewports.at(i)->getDoc()->focusDoc();
    updateLayoutType();
    updateScaleSlider();
}


void DocumentInteractionFrame::updateDocNames(Document* doc)
{
    if(doc == nullptr) return;

    for(int i = 0; i < viewports.length(); i++){
        if(viewports.at(i)->getDoc() == doc){
            tabs->setTabText(i,viewports.at(i)->getDoc()->getName());
        }
    }
}


void DocumentInteractionFrame::updateScaleSlider()
{
    scale->setValue(viewports.at(tabs->currentIndex())->getScale()*100);
}


void DocumentInteractionFrame::tabMoved(int from, int to)
{
    viewports.swapItemsAt(from,to);
}


void DocumentInteractionFrame::setLayoutType(QAction* layout)
{
    if(viewports.isEmpty())return;
    viewports.at(tabs->currentIndex())->getPageLayoutScene()->setLayoutType(layout->data().value<PageLayoutScene::LayoutType>());
}


void DocumentInteractionFrame::addNewDocument()
{
    Document *doc = new Document(ui);

    Page* new_page = new Page();
    doc->addPage(new_page);

    addDocument(doc);
    setCurrentDocument(doc);
}


void DocumentInteractionFrame::showTabContextMenu(const QPoint &point)
{
    if (point.isNull()) return;

    QMenu menu(this);

    QAction* close = new QAction("Close Document");
    menu.addAction(close);
    connect(close, &QAction::triggered, this, &DocumentInteractionFrame::closeTab);

    menu.exec(tabs->mapToGlobal(point));
}


void DocumentInteractionFrame::closeTab()
{
    int i = tabs->currentIndex();
    tabs->removeTab(i);
    view_stack->removeWidget(viewports.at(i));
    delete viewports.at(i);
    viewports.remove(i);
}


void DocumentInteractionFrame::setupWidgets()
{
    //stacked widget
    view_stack = new QStackedWidget();

    //tab bar
    tabs = new QTabBar();
    tabs->setShape(QTabBar::RoundedSouth);
    tabs->setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);
    tabs->setExpanding(true);
    tabs->setMovable(true);
    tabs->setContextMenuPolicy(Qt::CustomContextMenu);

    QToolButton* new_tab = new QToolButton();
    new_tab->setIcon(QIcon(":/icons/AddTab.png"));

    //layout types
    QAction* vertical = new QAction();
    vertical->setIcon(QIcon(":/icons/Vertical.png"));
    vertical->setData(int(PageLayoutScene::Vertical));
    vertical->setCheckable(true);

    QAction* horizontal = new QAction();
    horizontal->setIcon(QIcon(":/icons/Horizontal.png"));
    horizontal->setData(int(PageLayoutScene::Horizontal));
    horizontal->setCheckable(true);

    QAction* seamless = new QAction();
    seamless->setIcon(QIcon(":/icons/Seamless.png"));
    seamless->setData(int(PageLayoutScene::Seamless));
    seamless->setCheckable(true);

    QAction* ftv = new QAction();
    ftv->setIcon(QIcon(":/icons/FitToView.png"));
    ftv->setData(int(PageLayoutScene::FitToView));
    ftv->setCheckable(true);
    ftv->setChecked(true);

    QActionGroup* group = new QActionGroup(this);
    group->setExclusive(true);
    group->addAction(vertical);
    group->addAction(horizontal);
    group->addAction(seamless);
    group->addAction(ftv);

    layouts = new QToolBar("Views");
    layouts->setMovable(false);
    layouts->setContentsMargins(0,0,0,0);
    layouts->addAction(ftv);
    layouts->addAction(vertical);
    layouts->addAction(seamless);
    layouts->addAction(horizontal);
    layouts->setIconSize(QSize(15,15));//originally 20x20

    scale = new QSlider(Qt::Orientation::Horizontal);
    scale->setRange(20,500);
    scale->setFixedWidth(200);

    //setup button layout
    QHBoxLayout* button_layout = new QHBoxLayout();
    button_layout->setContentsMargins(0,0,0,0);
    button_layout->setSpacing(0);
    button_layout->addWidget(tabs);
    button_layout->addSpacing(5);
    button_layout->addWidget(new_tab);
    button_layout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding));
    button_layout->addWidget(layouts);
    button_layout->addWidget(scale);

    //setup frame layout
    QVBoxLayout* frame_layout = new QVBoxLayout();
    frame_layout->setContentsMargins(0,0,0,0);
    frame_layout->setSpacing(0);
    frame_layout->addWidget(view_stack);
    frame_layout->addLayout(button_layout);

    setLayout(frame_layout);

    connect(tabs, &QTabBar::currentChanged, this, &DocumentInteractionFrame::setCurrentIndex);
    connect(tabs, &QTabBar::tabMoved, this, &DocumentInteractionFrame::tabMoved);
    connect(tabs, &QTabBar::customContextMenuRequested, this, &DocumentInteractionFrame::showTabContextMenu);
    connect(scale, &QSlider::sliderMoved, this, &DocumentInteractionFrame::setScale);
    connect(layouts, &QToolBar::actionTriggered, this, &DocumentInteractionFrame::setLayoutType);
    connect(new_tab, &QToolButton::clicked, this, &DocumentInteractionFrame::addNewDocument);
}


void DocumentInteractionFrame::updateLayoutType()
{
    PageLayoutScene::LayoutType type = viewports.at(tabs->currentIndex())->getPageLayoutScene()->getLayoutType();
    foreach(QAction* action, layouts->actions()){
        if(action->data().toInt() == type){
            action->setChecked(true);
            return;
        }
    }
}
