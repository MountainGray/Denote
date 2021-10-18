#include "undocreation.h"
#include "Graphics/pageitem.h"


UndoCreation::UndoCreation(HistoryManager *manager, PageItem *created, QString text) : UndoObject(manager)
{
    setText(text);
    this->created.append(created);
}


UndoCreation::UndoCreation(HistoryManager *manager, QList<PageItem*> created, QString text) : UndoObject(manager)
{
    setText(text);
    this->created = created;
}


UndoCreation::~UndoCreation()
{
    foreach(PageItem* item, created){
        delete item;
    }
}


void UndoCreation::undo()
{
    foreach(PageItem* item, created){
        item->removeItem();
    }
}


void UndoCreation::redo()
{
    foreach(PageItem* item, created){
        item->recoverItem();
    }
}


QRectF UndoCreation::updateArea()
{
    QRectF area;
    foreach(PageItem* item, created){
        area = area.united(item->boundingRect());
    }
    return area;
}
