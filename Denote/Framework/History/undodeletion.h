#ifndef UNDODELETION_H
#define UNDODELETION_H

#include "Framework/History/undoobject.h"
#include "Framework/pageitem.h"

class UndoDeletion : public UndoObject
{
public:
    UndoDeletion(HistoryManager* manager, PageItem* deleted, QString text);
    UndoDeletion(HistoryManager* manager, QList<PageItem*> deleted, QString text);
    ~UndoDeletion();
    void undo() override;
    void redo() override;

private:
    QList<PageItem*> deleted;
};

#endif // UNDODELETION_H
