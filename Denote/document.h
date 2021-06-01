#ifndef DOCUMENT_H
#define DOCUMENT_H


#include "documentview.h"

#include <QGraphicsScene>


class Document : public QGraphicsScene{
public:
    Document();
    ~Document();


protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    QPixmap background;
    DocumentView* activeView;
};

#endif // DOCUMENT_H
