#ifndef DOCUMENTINTERACTIONVIEW_H
#define DOCUMENTINTERACTIONVIEW_H

//QGraphicsView that has its own page layout which is connected to the same document
//Handles inputs to add strokes to the appropriate page

#include <QGraphicsView>

class Document;
class PageLayoutScene;

class DocumentInteractionView : public QGraphicsView
{
    Q_OBJECT
public:
    DocumentInteractionView(Document* doc);

public:
    void setScale(float new_scale);
    PageLayoutScene* getPageLayoutScene(){return page_layout_scene;}
    QTransform getViewInverse(){return view_inverse;}
    QPointF getPageInverse(){return page_inverse;}

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void tabletEvent(QTabletEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;


private:
    Document* doc;
    QTransform view_inverse;
    QPointF page_inverse;
    PageLayoutScene* page_layout_scene;
};

#endif // DOCUMENTINTERACTIONVIEW_H
