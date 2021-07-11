#ifndef PAGELAYOUTSCENE_H
#define PAGELAYOUTSCENE_H

//Holds the current layout of pages for that viewport
//All tools are only added to the active scene

#include <QGraphicsScene>

class Document;
class Page;
class PagePortal;

class PageLayoutScene : public QGraphicsScene
{
public:
    PageLayoutScene(QGraphicsView* viewport, Document* doc);

public:
    void updatePageLayout();
    void addPortal(Page* page);
    void removePortal(Page* page);
    QList<PagePortal*> getPortals(){return portals;}
    void setAutoLayout(bool b);

private:
    QGraphicsView* viewport;
    Document* doc;
    QList<PagePortal*> portals;

    const int y_padding = 30;

    bool auto_layout = false;
};

#endif // PAGELAYOUTSCENE_H
