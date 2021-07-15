#include "historymanager.h"
#include "Framework/undoobject.h"
#include <QKeyEvent>

HistoryManager::HistoryManager()
{

}


void HistoryManager::addObject(UndoObject *object)
{
    foreach(UndoObject* old, undone_stack){
        delete old;
    }
    undone_stack.clear();
    active_stack.append(object);
}


void HistoryManager::keyPressEvent(QKeyEvent *event)
{
    if(event->key() & Qt::Key_Z and event->modifiers() & Qt::KeyboardModifier::ControlModifier){
        if(event->modifiers() & Qt::KeyboardModifier::ShiftModifier){
            if(not undone_stack.isEmpty()){
                UndoObject* object = undone_stack.takeLast();
                object->redo();
                active_stack.append(object);
            }
        } else{
            if(not active_stack.isEmpty()){
                UndoObject* object = active_stack.takeLast();
                object->undo();
                undone_stack.append(object);
            }
        }
    }
}
