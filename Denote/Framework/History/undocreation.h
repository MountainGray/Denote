#ifndef UNDOCREATION_H
#define UNDOCREATION_H

#include "Framework/History/undoobject.h"

class PageItem;

class UndoCreation : public UndoObject
{
public:
    UndoCreation(HistoryManager* manager, PageItem* created, QString text);
    UndoCreation(HistoryManager* manager, QList<PageItem*> created, QString text);
    ~UndoCreation();
    void undo() override;
    void redo() override;
    QRectF updateArea() override;

private:
    QList<PageItem*> created;
};

#endif // UNDOCREATION_H
