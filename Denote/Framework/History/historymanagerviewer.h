#ifndef HISTORYMANAGERVIEWER_H
#define HISTORYMANAGERVIEWER_H

<<<<<<< Updated upstream
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
=======
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
>>>>>>> Stashed changes
    HistoryManager* history_manager = nullptr;
};

#endif // HISTORYMANAGERVIEWER_H
