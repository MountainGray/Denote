#include "Framework/subwindow.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

SubWindow::SubWindow(QMainWindow *parent) : QDockWidget(parent){
    this->mainWindow = parent;
    connect(this, SIGNAL(topLevelChanged(bool)), this, SLOT(makeTopLevel(bool)));
    /*
    QLabel *label = new QLabel("Test",this);
    QPushButton *close = new QPushButton("X",this);
    QPushButton *minimize = new QPushButton("-",this);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(label);
    layout->addWidget(close);
    layout->addWidget(minimize);
    titlebar = new QWidget();
    titlebar->setLayout(layout);
    setTitleBarWidget(titlebar);
    */


}

SubWindow::~SubWindow(){

}

void SubWindow::changeEvent(QEvent *e){
    if (e->type() == QEvent::WindowStateChange){
        if(isMinimized()){
            hide();
        } else {
            QDockWidget::changeEvent(e);
        }
    }
}

void SubWindow::makeTopLevel(bool){
    return;
    if (isFloating()){
        setTitleBarWidget(nullptr);
        setWindowFlags(Qt::CustomizeWindowHint |
            Qt::Window |
            Qt::WindowMinimizeButtonHint |
            Qt::WindowMaximizeButtonHint |
            Qt::WindowCloseButtonHint
                        );
        show();

    } else {
        setTitleBarWidget(titlebar);
    }
}
