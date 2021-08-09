#ifndef DOCUMENTVIEW_H
#define DOCUMENTVIEW_H

#include <QGraphicsView>
#include "Graphics/pagelayoutscene.h"
#include "Ui/ui.h"
#include "Tools/tool.h"
#include "Graphics/pageportal.h"

class Document;
class PageLayoutScene;

class DocumentView : public QGraphicsView
{
    Q_OBJECT
public:
    DocumentView(Document* doc);
    ~DocumentView();

public slots:
    void setScale(float new_scale);
    void scaleBy(float scale_factor);

public:
    float getScale(){return view_scale;}
    QTransform getViewInverse(){return view_inverse;}
    QPointF getPageInverse(){return page_inverse;}
    PageLayoutScene* getPageLayoutScene(){return page_layout_scene;}
    Document* getDoc(){return doc;}
    void focusDoc();
<<<<<<< Updated upstream
    void resetGL();
=======
>>>>>>> Stashed changes

protected:
    Document* doc;
    PageLayoutScene* page_layout_scene;
    float view_scale = 1;
    QTransform view_inverse;
    QPointF page_inverse;
};

#endif // DOCUMENTVIEW_H
