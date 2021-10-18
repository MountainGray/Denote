#ifndef PAGELAYOUTSCENE_H
#define PAGELAYOUTSCENE_H

//Holds the current layout of pages for that viewport
//All tools are only added to the active scene

#include <QGraphicsScene>
#include "Framework/document.h"
#include <QTabletEvent>

class Page;
class PagePortal;
class DocumentView;

class PageLayoutScene : public QGraphicsScene
{
    friend PagePortal;
public:
    enum LayoutType {Vertical, Horizontal, Seamless, FitToView};
    static constexpr QColor BACKGROUND = QColor(30,33,33);

    PageLayoutScene(Document* doc, DocumentView* viewport);
    ~PageLayoutScene();

public:
    Document* getDoc(){return doc;}
    DocumentView* getView(){return viewport;}

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
    DocumentView* viewport;
    QList<PagePortal*> portals;
    PagePortal* focused_portal = nullptr;
    LayoutType layout_type = Vertical;
    QRectF last_focused_portal_bounds;
    bool holes = true;
    bool shadow = true;
    bool interactive = true;

    bool _isInBackgroundUpdate;
};

#endif // PAGELAYOUTSCENE_H
