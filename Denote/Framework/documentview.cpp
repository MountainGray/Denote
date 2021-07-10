#include "Framework/documentview.h"
#include "Framework/documentgraphics.h"

#include <QtOpenGLWidgets/QOpenGLWidget>
#include "Ui/ui.h"

DocumentView::DocumentView(MainWindow *parent, Document *doc) : SubWindow(parent){
    graphics = new DocumentGraphics(this, doc);
    parent->getUI()->addGraphicsView(graphics);

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
