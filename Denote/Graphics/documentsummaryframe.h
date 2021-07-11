#ifndef DOCUMENTSUMMARYFRAME_H
#define DOCUMENTSUMMARYFRAME_H

//Frame to hold document summary view and future other widgets

#include "Framework/subwindow.h"

class MainWindow;
class Document;
class DocumentSummaryView;

class DocumentSummaryFrame : public SubWindow
{
public:
    DocumentSummaryFrame(MainWindow* parent, Document* doc);

private:
    Document* doc;
    DocumentSummaryView* viewport;
};

#endif // DOCUMENTSUMMARYFRAME_H
