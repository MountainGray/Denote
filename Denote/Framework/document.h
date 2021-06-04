#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QGraphicsScene>

#include "Framework/documentview.h"


class Page;
class UI;

class Document : public QGraphicsScene{
public:
    Document(UI* ui, QObject* parent = 0);
    ~Document();

    void addPage(Page* page);
    bool removePage(int i);
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

    QList<Page*> pages;
};

#endif // DOCUMENT_H
