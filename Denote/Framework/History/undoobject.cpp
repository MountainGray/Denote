#include "undoobject.h"
#include "Framework/History/historymanager.h"

UndoObject::UndoObject(HistoryManager* manager)
{
    this->manager = manager;
    manager->addObject(this);
}

UndoObject::~UndoObject()
{

}
