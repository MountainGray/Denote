#ifndef DOCUMENTVIEW_H
#define DOCUMENTVIEW_H

#include "subwindow.h"

#include <QObject>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsView>
#include "mainwindow.h"

class Document;
class DocumentGraphics;

class DocumentView : public SubWindow{
    Q_OBJECT
    
public:
    DocumentView(MainWindow *parent, Document* doc);

public:
    void setScale(float scale);

private:
    QList<Document*> docs;
    DocumentGraphics* graphics;    
};

#endif // DOCUMENTVIEW_H
