#ifndef PAGELAYOUTSCENE_H
#define PAGELAYOUTSCENE_H

//Holds the current layout of pages for that viewport
//All tools are only added to the active scene

#include <QGraphicsScene>
#include <QGraphicsView>
#include "Framework/document.h"

class Page;
class PagePortal;

enum LayoutType {SingleColumn, FitToView};
enum ViewType {Summary, Interaction};

class PageLayoutScene : public QGraphicsScene
{
    friend PagePortal;
public:
    PageLayoutScene(Document* doc, QGraphicsView* viewport, ViewType view_type);
    ~PageLayoutScene();

public:
    QGraphicsView* getView(){return viewport;}
    ViewType getViewType(){return view_type;}
    void updatePageLayout(bool force_endless_update = false);
    void setLayoutType(LayoutType type);
    void setFocusedPortal(PagePortal* portal);

    QList<PagePortal*> getPortals(){return portals;}

private:
    friend void Document::movePage(Page* page, int new_index);

private:
    QGraphicsView* viewport;
    ViewType view_type;
    Document* doc;
    QList<PagePortal*> portals;
    PagePortal* focused_portal = nullptr;
    LayoutType layout_type = SingleColumn;
    QRectF last_focused_portal_bounds;

    const int page_padding = 20;
    const int view_padding = 100;
};

#endif // PAGELAYOUTSCENE_H
