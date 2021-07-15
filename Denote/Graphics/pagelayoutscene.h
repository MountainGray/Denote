#ifndef PAGELAYOUTSCENE_H
#define PAGELAYOUTSCENE_H

//Holds the current layout of pages for that viewport
//All tools are only added to the active scene

#include <QGraphicsScene>
#include <QGraphicsView>

class Document;
class Page;
class PagePortal;

enum LayoutType {SingleColumn, FitToView};

class PageLayoutScene : public QGraphicsScene
{
public:
    PageLayoutScene(QGraphicsView* viewport, Document* doc);

public:
    void updatePageLayout();
    void addPortal(Page* page, int index = -1);
    void removePortal(Page* page);
    void movePortal(int old_index, int new_index);
    QList<PagePortal*> getPortals(){return portals;}
    void setLayoutType(LayoutType type){layout_type = type;}

private:
    QGraphicsView* viewport;
    Document* doc;
    QList<PagePortal*> portals;
    LayoutType layout_type = SingleColumn;

    const int page_padding = 20;
    const int view_padding = 100;
};

#endif // PAGELAYOUTSCENE_H
