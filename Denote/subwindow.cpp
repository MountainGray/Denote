#include "subwindow.h"


SubWindow::SubWindow(QMainWindow *parent, QWidget *child) : QDockWidget(parent), mainWindow(parent){
    setWidget(child);
}

SubWindow::~SubWindow(){

}

void SubWindow::paintEvent(QPaintEvent *event){

}
