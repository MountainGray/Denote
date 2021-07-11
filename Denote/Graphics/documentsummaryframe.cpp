#include "documentsummaryframe.h"
#include "documentsummaryview.h"
#include "mainwindow.h"

#include <QtOpenGLWidgets/QOpenGLWidget>


DocumentSummaryFrame::DocumentSummaryFrame(MainWindow *parent, Document* doc) : SubWindow(parent)
{
    this->doc = doc;
    viewport = new DocumentSummaryView(doc);

    QOpenGLWidget *gl = new QOpenGLWidget();
    QSurfaceFormat format;
    format.setSamples(5);
    gl->setFormat(format);
    viewport->setViewport(gl);
    setWidget(viewport);

    setMinimumSize(80,150);
}
