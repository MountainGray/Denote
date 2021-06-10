#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "Framework/documentview.h"
#include "Ui/ui.h"

#include <QGraphicsScene>


class Page;
class UI;

class Document : public QGraphicsScene{
public:
    Document(UI* ui, QObject* parent = 0);
    ~Document();

    void addPage(Page* page);
    bool removePage(int i);
    UI* getUI(){return ui;}

public:
    void deleteItems(QList<QGraphicsItem*> items);


protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    QPixmap background;
    DocumentView* activeView;
    QList<Page*> pages;
    UI* ui;
};

#endif // DOCUMENT_H
