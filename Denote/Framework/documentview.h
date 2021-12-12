#ifndef DOCUMENTVIEW_H
#define DOCUMENTVIEW_H

#include <QGraphicsView>

#include "Graphics/pagelayoutscene.h"
#include "Ui/ui.h"
#include "Tools/tool.h"
#include "Graphics/pageportal.h"

class Document;
class PageLayoutScene;
class PenStroke;
class OffscreenOpenGL;

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
    void scaleToFit();

    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    void forcePaint(QPaintEvent *event){ paintEvent(event);}

    bool force = true;

    void cacheScene(QRect rect = QRect());

    void setCachedStroke(PenStroke* stroke){this->stroke = stroke;}
    void clearCachedStroke();

    void setNormal(){normal = true;}



private:
    void paintCachedStroke(QPainter* painter);

protected:
    Document* doc;
    PageLayoutScene* page_layout_scene;
    float view_scale = 1;
    QTransform view_inverse;
    QPointF page_inverse;

private:
    static const int view_padding = 4;

    OffscreenOpenGL* gl;
    QImage *image = new QImage();
    PenStroke* stroke = nullptr;

    bool normal = false;
};

#endif // DOCUMENTVIEW_H
