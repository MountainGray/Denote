#ifndef UNDOOBJECT_H
#define UNDOOBJECT_H

#include <QListWidgetItem>

class HistoryManager;

class UndoObject : public QListWidgetItem
{
public:
    UndoObject(HistoryManager* manager);
    virtual ~UndoObject();
    virtual void undo() = 0;
    virtual void redo() = 0;

protected:
    HistoryManager* manager;//not sure if needed
    QString action_type;
};

#endif // UNDOOBJECT_H
