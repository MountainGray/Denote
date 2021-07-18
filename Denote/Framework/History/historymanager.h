#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include "Framework/subwindow.h"
#include "mainwindow.h"
#include <QListWidget>

class UndoObject;

class HistoryManager : public SubWindow
{
public:
    HistoryManager(MainWindow* parent);

public:
    void addObject(UndoObject* object);
    void keyPressEvent(QKeyEvent* event) override;

private:
    void undo();
    void redo();

private slots:
    void setHistory(QListWidgetItem* item);

private:
    MainWindow* parent;
    QList<UndoObject*> active_stack;
    QList<UndoObject*> undone_stack;
    QListWidget* history;
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
