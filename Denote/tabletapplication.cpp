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
