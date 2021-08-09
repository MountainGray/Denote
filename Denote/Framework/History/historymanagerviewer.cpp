#include "historymanagerviewer.h"
#include "Framework/History/historymanager.h"

#include <QKeyEvent>

<<<<<<< Updated upstream
<<<<<<< Updated upstream

HistoryManagerViewer::HistoryManagerViewer(MainWindow* parent) : SubWindow(parent)
{
    this->parent = parent;
=======
HistoryManagerViewer::HistoryManagerViewer()
{

>>>>>>> Stashed changes
=======
HistoryManagerViewer::HistoryManagerViewer()
{

>>>>>>> Stashed changes
}


void HistoryManagerViewer::keyPressEvent(QKeyEvent *event)
{
    if(history_manager == nullptr) return;

    if(event->key() & Qt::Key_Z and event->modifiers() & Qt::KeyboardModifier::ControlModifier){
        if(event->modifiers() & Qt::KeyboardModifier::ShiftModifier){
            history_manager->redo();
        } else{
            history_manager->undo();
        }
    }
}


<<<<<<< Updated upstream
<<<<<<< Updated upstream
void HistoryManagerViewer::setHistoryManager(HistoryManager *history_manager)
{
    this->history_manager = history_manager;
    setWidget(history_manager);
=======
void HistoryManagerViewer::addHistoryManager(HistoryManager *manager)
{
=======
void HistoryManagerViewer::addHistoryManager(HistoryManager *manager)
{
>>>>>>> Stashed changes
    QStackedWidget::addWidget(manager);
    setCurrentWidget(manager);
    history_manager = manager;
}


void HistoryManagerViewer::setHistoryManager(HistoryManager *manager)
{
    if(indexOf(manager) == -1){
        addWidget(manager);
    } else {
        setCurrentWidget(manager);
    }
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
}
