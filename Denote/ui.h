#ifndef UI_H
#define UI_H

class Tool;

class UI
{
public:
    UI();
public:
    void changeTool(Tool *tool);
    Tool* getTool();
private:
    Tool *tool;
};

#endif // UI_H
