#ifndef TEST_H
#define TEST_H

#include <qwidget.h>

class test : public QWidget
{
public:
    test();

protected:
    void tabletEvent(QTabletEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
};

#endif // TEST_H
