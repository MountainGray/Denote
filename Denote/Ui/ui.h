#ifndef UI_H
#define UI_H

#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

class Tool;
class Document;

class UI
{
public:
    UI();
public:
    void changeTool(Tool *tool);
    Tool* getTool();

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void tabletPress(QTabletEvent *event);
    void tabletMove(QTabletEvent *event);
    void tabletRelease(QTabletEvent *event);
    //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    //void keyPressEvent(QKeyEvent *event);
    //void wheelEvent(QGraphicsSceneWheelEvent *);

    Document* getDocument();
    void addDocument(Document*);

private:
    Tool *tool;
    Document* document;
};

#endif // UI_H
