#include "historymanagerviewer.h"
#include "Framework/History/historymanager.h"

#include <QKeyEvent>


HistoryManagerViewer::HistoryManagerViewer()
{

}


void HistoryManagerViewer::keyPressEvent(QKeyEvent *event)
{
    if(history_manager == nullptr) return;

    if(event->key() & Qt::Key_Z and event->modifiers() & Qt::KeyboardModifier::ControlModifier){
        if(event->modifiers() & Qt::KeyboardModifier::ShiftModifier){
            history_manager->redo();
        } else{
            history_manager->undo();
        }
    }
}


void HistoryManagerViewer::addHistoryManager(HistoryManager *manager)
{
    QStackedWidget::addWidget(manager);
    setCurrentWidget(manager);
    history_manager = manager;
}


void HistoryManagerViewer::setHistoryManager(HistoryManager *manager)
{
    if(indexOf(manager) == -1){
        addWidget(manager);
    } else {
        setCurrentWidget(manager);
    }
}
