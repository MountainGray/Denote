#ifndef DOCUMENTGRAPHICS_H
#define DOCUMENTGRAPHICS_H

#include <QGraphicsView>
#include <QWheelEvent>

class Document;
class DocumentView;

class DocumentGraphics : public QGraphicsView{
    Q_OBJECT
public:
    explicit DocumentGraphics(DocumentView *view, Document *doc);

protected:
    void wheelEvent(QWheelEvent *e) override;
    //void tabletEvent(QTabletEvent *event) override;//used for tablet events only
    //void mousePressEvent(QMouseEvent *event) override;
    //void mouseMoveEvent(QMouseEvent *event) override;
    //void mouseReleaseEvent(QMouseEvent *event) override;

private:
    DocumentView *view;
    Document *doc;
    float scale = 1;
    float rotation = 0;
};

#endif // DOCUMENTGRAPHICS_H
