#ifndef DOCUMENTSUMMARYVIEW_H
#define DOCUMENTSUMMARYVIEW_H

//Static viewport of page layout scene, only allows reordering of pages.

#include "Framework/documentview.h"

class DocumentSummaryView : public DocumentView
{
    Q_OBJECT
public:
    DocumentSummaryView(Document* doc);
    ~DocumentSummaryView();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // DOCUMENTSUMMARYVIEW_H
