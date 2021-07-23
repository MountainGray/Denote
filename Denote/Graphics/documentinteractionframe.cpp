#include "documentinteractionframe.h"
#include "mainwindow.h"
#include "Framework/document.h"
#include "documentinteractionview.h"



DocumentInteractionFrame::DocumentInteractionFrame(MainWindow* parent, Document* doc) : SubWindow(parent)
{
    setMinimumSize(150,150);

    empty_widget = new QLabel();
    empty_widget->setAlignment(Qt::AlignCenter);
    empty_widget->setText("No Documents are Open");

    tab_widget = new QTabWidget();

    addDocument(doc);

    connect(this, &QDockWidget::topLevelChanged, this, &DocumentInteractionFrame::resetGL);
    connect(tab_widget, &QTabWidget::currentChanged, this, &DocumentInteractionFrame::focusCurrentDoc);
}


DocumentInteractionFrame::~DocumentInteractionFrame()
{
    for(int i = 0; i < tab_widget->count(); i++){
        DocumentInteractionView* view = static_cast<DocumentInteractionView*>(tab_widget->widget(i));
        if(view != nullptr){
            delete view;
        }
    }
    delete tab_widget;
}


void DocumentInteractionFrame::setScale(float scale)
{
    Q_UNUSED(scale);
    //viewport->setScale(scale);
}


void DocumentInteractionFrame::addDocument(Document *doc)
{
    if(doc == nullptr and tab_widget->count() == 0){
        setWidget(empty_widget);

    } else if (doc != nullptr){
        DocumentInteractionView* new_viewport = new DocumentInteractionView(doc);
        tab_widget->addTab(new_viewport, QString("New Document %1").arg(tab_widget->count()));
        setWidget(tab_widget);
        doc->focusDoc();
    }
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


void DocumentInteractionFrame::resetGL()
{
    for(int i = 0; i < tab_widget->count(); i++){
        DocumentInteractionView* view = static_cast<DocumentInteractionView*>(tab_widget->widget(i));
        if(view != nullptr){
            view->resetGL();
        }
    }
}


void DocumentInteractionFrame::focusCurrentDoc()
{
    DocumentInteractionView* view = static_cast<DocumentInteractionView*>(tab_widget->currentWidget());
    if(view != nullptr){
        view->getDoc()->focusDoc();
    }
}
