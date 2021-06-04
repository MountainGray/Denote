#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QGraphicsScene>

#include "documentview.h"


class UI;

class Document : public QGraphicsScene{
public:
    Document(UI* ui, QObject* parent = 0);
    ~Document();

public:
    void deleteItems(QList<QGraphicsItem*> items);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    //void keyPressEvent(QKeyEvent *event) override;

private:
    QPixmap background;
    DocumentView* activeView;
    UI* ui;

};

#endif // DOCUMENT_H
