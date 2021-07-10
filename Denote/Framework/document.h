#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "Framework/documentview.h"
#include "Ui/ui.h"

#include <QGraphicsScene>

class Page;
class UI;
class PageLayout;

class Document : public QGraphicsScene{
public:
    Document(UI* ui, QObject* parent = 0);
    ~Document();

public:
    void addPage(Page* page);
    bool removePage(int i);
    UI* getUI(){return ui;}
    QList<Page*> getPages(){return pages;}
    void setPages(QList<Page*> pages){ this->pages = pages;}
    QRectF getDocBounds();
    void updateActivePage();
    Page* getActivePage(){return active_page;}
    void removeItems(QList<QGraphicsItem*> items);
    void updateSceneRect();
    void updatePages();

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    DocumentView* active_view;
    QList<Page*> pages;
    Page* active_page;
    PageLayout* page_layout;
    UI* ui;
};

#endif // DOCUMENT_H
