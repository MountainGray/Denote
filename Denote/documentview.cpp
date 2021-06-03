#include "documentview.h"
#include "documentgraphics.h"


DocumentView::DocumentView(QMainWindow *parent, Document *doc) : SubWindow(parent){
    graphics = new DocumentGraphics(this, doc);
    setWidget(graphics);
    docs.append(doc);

    setMinimumSize(200,200);
}
