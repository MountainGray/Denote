#ifndef HISTORYMANAGERVIEWER_H
#define HISTORYMANAGERVIEWER_H

#include "Framework/subwindow.h"
#include "mainwindow.h"

class HistoryManager;

class HistoryManagerViewer : public SubWindow
{
public:
    HistoryManagerViewer(MainWindow* parent);

public:
    void keyPressEvent(QKeyEvent* event) override;
    void setHistoryManager(HistoryManager* history_manager);

private:
    MainWindow* parent;
    HistoryManager* history_manager = nullptr;
};

#endif // HISTORYMANAGERVIEWER_H
