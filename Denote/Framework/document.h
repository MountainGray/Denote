#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QGraphicsScene>

class PageLayoutScene;
class Page;
class UI;

class Document
{
public:
    Document(UI* ui);
    ~Document();

public:
    void addLayout(PageLayoutScene* layout){layouts.append(layout);}
    void removeLayout(PageLayoutScene* layout){layouts.removeAll(layout);}
    QList<PageLayoutScene*> getLayouts(){return layouts;}

    void addPage(Page* page, int index = -1);
    void removePage(Page* page);
    void movePage(Page* page, int new_index);
    QList<Page*> getPages(){return pages;}

    UI* getUI(){return ui;}
    void updateAll();

private:
    QList<Page*> pages;
    UI* ui;
    QList<PageLayoutScene*> layouts;
};

#endif // DOCUMENT_H
