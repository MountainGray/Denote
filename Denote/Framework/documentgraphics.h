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

public:
    QTransform getInverse(){return inverse;}

public:
    void setScale(float view_scale);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void tabletEvent(QTabletEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    DocumentView *view;
    Document *doc;
    QTransform inverse;
};

#endif // DOCUMENTGRAPHICS_H
