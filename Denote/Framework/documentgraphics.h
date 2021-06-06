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
    void tabletEvent(QTabletEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *e) override;

private:
    QTabletEvent* mapToDoc(QTabletEvent *event);

private:
    DocumentView *view;
    Document *doc;
    float scale = 1;
    float rotation = 0;
};

#endif // DOCUMENTGRAPHICS_H
