#include "undodeletion.h"


UndoDeletion::UndoDeletion(HistoryManager *manager, PageItem *deleted, QString text) : UndoObject(manager)
{
    setText(text);
    this->deleted.append(deleted);
}


UndoDeletion::UndoDeletion(HistoryManager* manager, QList<PageItem*> deleted, QString text) : UndoObject(manager)
{
    setText(text);
    this->deleted = deleted;
}


UndoDeletion::~UndoDeletion()
{

}


void UndoDeletion::undo()
{
    foreach(PageItem* item, deleted){
        item->recoverItem();
    }
}


void UndoDeletion::redo()
{
    foreach(PageItem* item, deleted){
        item->removeItem();
    }
}


QRectF UndoDeletion::updateArea()
{
    QRectF area;
    foreach(PageItem* item, deleted){
        area = area.united(item->boundingRect());
    }
    return area;
}
