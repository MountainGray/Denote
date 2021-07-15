#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QWidget>

class UndoObject;

class HistoryManager : public QWidget
{
public:
    HistoryManager();

public:
    void addObject(UndoObject* object);
    void keyPressEvent(QKeyEvent* event) override;

private:
    QList<UndoObject*> active_stack;
    QList<UndoObject*> undone_stack;
};

#endif // HISTORYMANAGER_H
