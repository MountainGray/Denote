#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QListWidget>

class UndoObject;
class Document;

class HistoryManager : public QListWidget
{
    Q_OBJECT;
public:
    HistoryManager(Document* doc);

public:
    void addObject(UndoObject* object);
    void undo();
    void redo();

private slots:
    void setHistory(QListWidgetItem* item);

private:
    Document* doc;
    QList<UndoObject*> active_stack;
    QList<UndoObject*> undone_stack;
    QBrush dark = QBrush(QColor("grey"));
    QBrush light = QBrush(QColor("white"));
};


#include "Framework/History/undoobject.h"

class HistoryStart : public UndoObject
{
public:
    HistoryStart(HistoryManager* manager) : UndoObject(manager){}
    void undo() override{}
    void redo() override{}
};

#endif // HISTORYMANAGER_H
