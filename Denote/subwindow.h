#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>

class SubWindow : public QWidget {
public:
    SubWindow();

public:
    void changeWindow();
    void splitWindow();
private:
    bool active;
};

#endif // SUBWINDOW_H
