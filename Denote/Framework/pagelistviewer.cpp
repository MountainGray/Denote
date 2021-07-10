#include "pagelistviewer.h"
#include "pagelist.h"
#include "Ui/ui.h"

#include <QtOpenGLWidgets/QOpenGLWidget>

PageListViewer::PageListViewer(MainWindow *parent, Document* doc) : SubWindow(parent)
{
    pages = new PageList(this, doc);
    parent->getUI()->addGraphicsView(pages);

    QOpenGLWidget *gl = new QOpenGLWidget();
    QSurfaceFormat format;
    format.setSamples(5);
    gl->setFormat(format);
    pages->setViewport(gl);
    setWidget(pages);

    active_doc = doc;

    setMinimumSize(80,150);
}
