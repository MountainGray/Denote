#include "historymanagerviewer.h"
#include "Framework/History/historymanager.h"

#include <QKeyEvent>


HistoryManagerViewer::HistoryManagerViewer(MainWindow* parent) : SubWindow(parent)
{
    this->parent = parent;
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


void HistoryManagerViewer::setHistoryManager(HistoryManager *history_manager)
{
    this->history_manager = history_manager;
    setWidget(history_manager);
}
