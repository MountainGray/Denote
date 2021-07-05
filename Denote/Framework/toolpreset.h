#ifndef TOOLPRESET_H
#define TOOLPRESET_H

#include <QWidget>

class Tool;

class ToolPreset : public QWidget
{
public:
    ToolPreset(Tool* tool);

protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

private:
    Tool* tool;
};

#endif // TOOLPRESET_H

//TOOOOLL IS NEVER SET DUUUUH
