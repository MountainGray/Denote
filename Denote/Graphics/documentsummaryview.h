#ifndef DOCUMENTSUMMARYVIEW_H
#define DOCUMENTSUMMARYVIEW_H

//Static viewport of page layout scene, only allows reordering of pages.

#include <QGraphicsView>

class Document;
class PageLayoutScene;

class DocumentSummaryView : public QGraphicsView
{
public:
    DocumentSummaryView(Document* doc);

public:
    PageLayoutScene* getPageLayoutScene(){return page_layout_scene;}

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    Document* doc;
    PageLayoutScene* page_layout_scene;

    const int x_padding = 4;
};

#endif // DOCUMENTSUMMARYVIEW_H
