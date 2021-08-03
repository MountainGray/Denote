#ifndef PAGELAYOUTSCENE_H
#define PAGELAYOUTSCENE_H

//Holds the current layout of pages for that viewport
//All tools are only added to the active scene

#include <QGraphicsScene>
#include <QGraphicsView>
#include "Framework/document.h"

class Page;
class PagePortal;

class PageLayoutScene : public QGraphicsScene
{
    friend PagePortal;
public:
    enum LayoutType {Vertical, Seamless, FitToView};
    static constexpr QColor BACKGROUND = QColor(30,33,33);

    PageLayoutScene(Document* doc, QGraphicsView* viewport);
    ~PageLayoutScene();

public:
    Document* getDoc(){return doc;}
    QGraphicsView* getView(){return viewport;}

    void setLayoutType(LayoutType type);
    LayoutType getLayoutType(){return layout_type;}
    void updatePageLayout();

    void setFocusedPortal(PagePortal* portal);
    QList<PagePortal*> getPortals(){return portals;}

    void setHoles(bool holes);
    bool hasHoles(){return holes;}
    void setShadow(bool shadow);
    bool hasShadow(){return shadow;}

    void setInteractive(bool interactive){this->interactive = interactive;}
    bool isInteractive(){return interactive;}

private:
    friend void Document::movePage(Page* page, int new_index);

private:
    Document* doc;
    QGraphicsView* viewport;
    QList<PagePortal*> portals;
    PagePortal* focused_portal = nullptr;
    LayoutType layout_type = Vertical;
    QRectF last_focused_portal_bounds;
    bool holes = true;
    bool shadow = true;
    bool interactive = true;
};

#endif // PAGELAYOUTSCENE_H
