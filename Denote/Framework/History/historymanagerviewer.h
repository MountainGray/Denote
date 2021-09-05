#ifndef HISTORYMANAGERVIEWER_H
#define HISTORYMANAGERVIEWER_H

#include "mainwindow.h"
#include <QStackedWidget>

class HistoryManager;

class HistoryManagerViewer : public QStackedWidget
{
public:
    HistoryManagerViewer();

public:
    void keyPressEvent(QKeyEvent* event) override;
    void addHistoryManager(HistoryManager* manager);
    void setHistoryManager(HistoryManager* manager);

private:
    HistoryManager* history_manager;
};

#endif // HISTORYMANAGERVIEWER_H
