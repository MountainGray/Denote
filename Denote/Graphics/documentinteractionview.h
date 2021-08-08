#ifndef DOCUMENTINTERACTIONVIEW_H
#define DOCUMENTINTERACTIONVIEW_H

//QGraphicsView that has its own page layout which is connected to the same document
//Handles inputs to add strokes to the appropriate page

#include "Framework/documentview.h"

class DocumentInteractionFrame;

class DocumentInteractionView : public DocumentView
{
    Q_OBJECT
public:
    DocumentInteractionView(Document* doc, DocumentInteractionFrame* frame);
    ~DocumentInteractionView();

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

private slots:
    void scrollPositionChanged();

private:
    DocumentInteractionFrame* frame;
};

#endif // DOCUMENTINTERACTIONVIEW_H
