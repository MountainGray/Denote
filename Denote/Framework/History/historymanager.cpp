#include "historymanager.h"
#include "Framework/History/undoobject.h"
#include <QKeyEvent>
#include "Ui/ui.h"
#include "Framework/document.h"


HistoryManager::HistoryManager(MainWindow* parent) : SubWindow(parent)
{
    this->parent = parent;
    history = new QListWidget();
    UndoObject* start = new HistoryStart(this);
    start->setText("Document Creation");
    history->addItem(start);
    setWidget(history);
    connect(history, &QListWidget::itemPressed, this, &HistoryManager::setHistory);
}


void HistoryManager::addObject(UndoObject *object)
{
    foreach(UndoObject* old, undone_stack){
        history->removeItemWidget(old);
        delete old;
    }
    undone_stack.clear();
    history->addItem(object);
    object->setBackground(light);
    object->setSelected(true);
    active_stack.append(object);
}


void HistoryManager::keyPressEvent(QKeyEvent *event)
{
    if(event->key() & Qt::Key_Z and event->modifiers() & Qt::KeyboardModifier::ControlModifier){
        if(event->modifiers() & Qt::KeyboardModifier::ShiftModifier){
            redo();
        } else{
            undo();
        }
        parent->getUI()->getActiveDocument()->updateAll();
    }
}


void HistoryManager::undo()
{
    if(not active_stack.isEmpty()){
        UndoObject* object = active_stack.takeLast();
        object->undo();
        object->setBackground(dark);
        undone_stack.append(object);
        if(not active_stack.isEmpty()) active_stack.last()->setSelected(true);
    }
}


void HistoryManager::redo()
{
    if(not undone_stack.isEmpty()){
        UndoObject* object = undone_stack.takeLast();
        object->redo();
        object->setBackground(light);
        active_stack.append(object);
        object->setSelected(true);
    }
}


void HistoryManager::setHistory(QListWidgetItem* item)
{
    int old_index = active_stack.length()-1;
    int new_index = history->row(item);
    int undos = old_index-new_index;

    if(undos > 0){
        for(int i = 0; i < undos;  i++) undo();
    } else if(undos < 0) {
        for(int i = 0; i < -undos; i++) redo();
    } else return;

    parent->getUI()->getActiveDocument()->updateAll();

    //terribly inefficient ?
}
