#include "tabletapplication.h"

#include "Ui/ui.h"
#include "Tools/tool.h"


bool TabletApplication::event(QEvent *event)
{
    if(event->type() == QEvent::TabletEnterProximity || event->type() == QEvent::TabletLeaveProximity){
        ui->getActiveTool()->tabletProximityEvent(event);
        return true;
    }
    return QApplication::event(event);
}


void TabletApplication::setupStyleSheet()
{
    return;
    setStyleSheet(
    "* {background-color: #101010 }" \
    "QWidget {color: #FFFFFF }" \
    "QTabBar {background-color: #101010 }" \
    "" \
    "" \
    );
}
