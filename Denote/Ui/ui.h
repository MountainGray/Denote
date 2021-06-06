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
    void setTool(Tool *tool);
    Tool* getTool();
    Document* getDocument();
    void addDocument(Document*);

public:
    void tabletPressEvent(QTabletEvent *event);
    void tabletMoveEvent(QTabletEvent *event);
    void tabletReleaseEvent(QTabletEvent *event);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    Tool *tool;
    Document* document;
};

#endif // UI_H
