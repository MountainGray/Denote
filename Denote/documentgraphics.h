#ifndef DOCUMENTGRAPHICS_H
#define DOCUMENTGRAPHICS_H

#include <QGraphicsView>
#include <QWheelEvent>

class Document;
class DocumentView;

class DocumentGraphics : public QGraphicsView{
    Q_OBJECT
public:
    DocumentGraphics(DocumentView *view, Document *doc);

protected:
    void wheelEvent(QWheelEvent *e) override;

private:
    Document *doc;
    float scale = 1;
    float rotation = 0;
};

#endif // DOCUMENTGRAPHICS_H
