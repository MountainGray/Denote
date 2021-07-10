#ifndef PAGELIST_H
#define PAGELIST_H

#include <QGraphicsView>
#include <QWheelEvent>

class Page;
class Document;
class PageListViewer;

class PageList : public QGraphicsView{
    Q_OBJECT
public:
    explicit PageList(PageListViewer *view, Document *doc);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    Page* selected_page;
    PageListViewer *view;
    Document *doc;
};

#endif // PAGELIST_H
