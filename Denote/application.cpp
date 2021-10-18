#include "application.h"

#include "Ui/ui.h"
#include "Tools/tool.h"


Application::Application(int argc, char** argv) : QApplication(argc, argv)
{
    setAttribute(Qt::AA_SynthesizeMouseForUnhandledTabletEvents, true);
    setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents, true);
    setAttribute(Qt::AA_CompressHighFrequencyEvents, true);
    setAttribute(Qt::AA_CompressTabletEvents, false);

    setupStyleSheet();
}


bool Application::event(QEvent *event)
{
    //Enter & Leave Proximity events are only sent to QApplications, forwarded to active tool
    if(event->type() == QEvent::TabletEnterProximity or event->type() == QEvent::TabletLeaveProximity){
        ui->getActiveTool()->tabletProximityEvent(event);//may change to TabletEvent in the future
        return true;
    }
    return QApplication::event(event);
}


void Application::setupStyleSheet()
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
