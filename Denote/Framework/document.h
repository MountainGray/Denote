#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QGraphicsScene>

class Page;
class UI;

class Document
{
public:
    Document(UI* ui);
    ~Document();

public:
    void addPage(Page* page, int index = -1);
    void removePage(Page* page);
    void movePage(Page* page, int new_index);
    QList<Page*> getPages(){return pages;}    
    UI* getUI(){return ui;}
    void updateAll();

private:
    QList<Page*> pages;
    UI* ui;
};

#endif // DOCUMENT_H
