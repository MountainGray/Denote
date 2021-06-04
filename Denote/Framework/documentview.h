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

protected:
    //void tabletEvent(QTabletEvent *event) override;
    //void paintEvent(QPaintEvent *event) override;
    //void resizeEvent(QResizeEvent *event) override;

private:
    QList<Document*> docs;
    DocumentGraphics* graphics;
    float scale = 1;
    float rotation = 0;
    
};

#endif // DOCUMENTVIEW_H
