#ifndef ERASER_H
#define ERASER_H

#include "tool.h"

#include <QGraphicsItem>
#include <QSlider>
#include <QGridLayout>
#include "Framework/undoobject.h"

class UI;

class Eraser : public Tool, public QGraphicsItem, public QObject{
public:
    Eraser(UI* ui);

public:
    void documentProximityEvent(QEvent* event) override;
    void drawPressEvent(ToolEvent event) override;
    void drawMoveEvent(ToolEvent event) override;
    void drawReleaseEvent(ToolEvent event) override;

    void activate() override;
    void deactivate() override;

    void paintPreset(QPaintEvent *event) override;

public:
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int type() const override {return TypeEraser;}

public:
    void setWidth(float width);
    float getWidth(){return width;}

private slots:
    void updateWidth(int width);

private:
    float width;
    QRectF bounds;
    bool visible = false;
    bool erasing = false;
    QList<QGraphicsItem*> erased;

private:
    QSlider *width_slider;
    QGridLayout *menu_layout;

};


class EraserUndo : public UndoObject
{
public:
    EraserUndo(HistoryManager* manager, QList<QGraphicsItem*> erased);

public:
    void undo() override;
    void redo() override;

private:
    QList<QGraphicsItem*> erased;
};


#endif // ERASER_H
