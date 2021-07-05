#include "Framework/documentview.h"
#include "Framework/documentgraphics.h"

#include <QtOpenGLWidgets/QOpenGLWidget>


DocumentView::DocumentView(QMainWindow *parent, Document *doc) : SubWindow(parent){
    graphics = new DocumentGraphics(this, doc);

    QOpenGLWidget *gl = new QOpenGLWidget();
    QSurfaceFormat format;
    format.setSamples(5);
    gl->setFormat(format);
    graphics->setViewport(gl);

    setWidget(graphics);
    docs.append(doc);

    setMinimumSize(150,150);
}


void DocumentView::setScale(float scale)
{
    graphics->setScale(scale);
}
