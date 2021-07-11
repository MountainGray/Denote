#include "documentinteractionframe.h"
#include "mainwindow.h"
#include "Framework/document.h"
#include "documentinteractionview.h"
#include <QtOpenGLWidgets/QOpenGLWidget>


DocumentInteractionFrame::DocumentInteractionFrame(MainWindow* parent, Document* doc) : SubWindow(parent)
{
    this->doc = doc;
    viewport = new DocumentInteractionView(doc);

    QOpenGLWidget *gl = new QOpenGLWidget();
    QSurfaceFormat format;
    format.setSamples(5);
    gl->setFormat(format);
    viewport->setViewport(gl);
    setWidget(viewport);

    setMinimumSize(150,150);
}


void DocumentInteractionFrame::setScale(float scale)
{
    viewport->setScale(scale);
}


