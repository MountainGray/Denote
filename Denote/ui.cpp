#include "ui.h"
#include "tool.h"

UI::UI()
{

}

void UI::changeTool(Tool *tool){
    this->tool = tool;
}

Tool* UI::getTool(){
    return this->tool;
}
