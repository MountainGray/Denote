#include "historymanager.h"
#include "Framework/History/undoobject.h"
#include "Ui/ui.h"
#include "Framework/document.h"


HistoryManager::HistoryManager(Document* doc)
{
    this->doc = doc;
    UndoObject* start = new HistoryStart(this);
    start->setText("Document Creation");
    addItem(start);
    connect(this, &QListWidget::itemPressed, this, &HistoryManager::setHistory);
}


void HistoryManager::addObject(UndoObject *object)
{
    foreach(UndoObject* old, undone_stack){
        removeItemWidget(old);
        delete old;
    }
    undone_stack.clear();
    addItem(object);
    object->setBackground(light);
    object->setSelected(true);
    active_stack.append(object);
}


void HistoryManager::undo()
{
    if(not active_stack.isEmpty()){
        UndoObject* object = active_stack.takeLast();
        object->undo();
        object->setBackground(dark);
        undone_stack.append(object);
        if(not active_stack.isEmpty()) active_stack.last()->setSelected(true);
        doc->updateAll(object->updateArea());
        doc->updateEndlessLength();
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
        doc->updateAll(object->updateArea());
        doc->updateEndlessLength();
    }
}


void HistoryManager::setHistory(QListWidgetItem* item)
{
    int old_index = active_stack.length()-1;
    int new_index = row(item);
    int undos = old_index-new_index;

    if(undos > 0){
        for(int i = 0; i < undos;  i++) undo();
    } else if(undos < 0) {
        for(int i = 0; i < -undos; i++) redo();
    } else return;

    //terribly inefficient ?
}
