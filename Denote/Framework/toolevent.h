#ifndef TOOLEVENT_H
#define TOOLEVENT_H

#include <QMouseEvent>
#include <QTabletEvent>

class DocumentInteractionView;

class ToolEvent : public QTabletEvent
{
public:
    ToolEvent(QMouseEvent *event, DocumentInteractionView* view);
    ToolEvent(QTabletEvent *event, DocumentInteractionView* view);

public:
    QPointF layoutPos(){return layout_position;}
    QPointF pagePos(){return page_position;}

private:
    QPointF layout_position;
    QPointF page_position;
};

#endif // TOOLEVENT_H
