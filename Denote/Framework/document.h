#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QGraphicsScene>

class Page;
class UI;
class PageLayoutScene;

class Document
{
public:
    Document(UI* ui);
    ~Document();

public:
    void addPage(Page* page, int index = -1);
    void removePage(Page* page);
    QList<Page*> getPages(){return pages;}
    void addPageLayout(PageLayoutScene* page_layout);
    void removePageLayout(PageLayoutScene* page_layout);
    UI* getUI(){return ui;}

private:
    QList<Page*> pages;
    QList<PageLayoutScene*> page_layouts;
    UI* ui;
};

#endif // DOCUMENT_H
