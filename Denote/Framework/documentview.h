#ifndef DOCUMENTVIEW_H
#define DOCUMENTVIEW_H

#include "subwindow.h"

#include <QObject>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsView>

class Document;
class DocumentGraphics;

class DocumentView : public SubWindow{
    Q_OBJECT
    
public:
    DocumentView(QMainWindow *parent, Document* doc);

public:
    void setScale(float scale);

private:
    QList<Document*> docs;
    DocumentGraphics* graphics;    
};

#endif // DOCUMENTVIEW_H
