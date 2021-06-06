#include "test.h"

#include <QDebug>
#include <QMouseEvent>
#include <QTabletEvent>

test::test() : QWidget()
{

}


void test::tabletEvent(QTabletEvent *event)
{
    if(event->type() == QTabletEvent::TabletPress){
        qDebug() << "tablet press";
    } else if(event->type() == QTabletEvent::TabletMove){
        qDebug() << "tablet move";
    } else if(event->type() == QTabletEvent::TabletRelease){
        qDebug() << "tablet release";
    }
    event->accept();
}


void test::mousePressEvent(QMouseEvent *event)
{
    if(event->deviceType() == QInputDevice::DeviceType::Mouse){
        qDebug() << "mouse press";
    }
}


void test::mouseMoveEvent(QMouseEvent *event)
{
    if(event->deviceType() == QInputDevice::DeviceType::Mouse){
        qDebug() << "mouse move";
    }
}



void test::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->deviceType() == QInputDevice::DeviceType::Mouse){
        qDebug() << "mouse release";
    }
}

void test::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->deviceType() == QInputDevice::DeviceType::Mouse){
        qDebug() << "mouse double";
    }
}
