#ifndef HISTORYMANAGERVIEWER_H
#define HISTORYMANAGERVIEWER_H

<<<<<<< Updated upstream
<<<<<<< Updated upstream
#include "Framework/subwindow.h"
#include "mainwindow.h"
=======
#include <QStackedWidget>
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
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
=======
>>>>>>> Stashed changes
    HistoryManager* history_manager = nullptr;
};

#endif // HISTORYMANAGERVIEWER_H
