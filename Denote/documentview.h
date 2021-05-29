#ifndef DOCUMENTVIEW_H
#define DOCUMENTVIEW_H

#include "subwindow.h"

#include <QObject>


class Document;

class DocumentView : public SubWindow{
    Q_OBJECT
    
public:
    DocumentView();
    DocumentView(Document* doc);

protected:
    //void tabletEvent(QTabletEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    //void resizeEvent(QResizeEvent *event) override;
    Document* doc;

    
};

#endif // DOCUMENTVIEW_H
