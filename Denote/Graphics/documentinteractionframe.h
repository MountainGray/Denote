#ifndef DOCUMENTINTERACTIONFRAME_H
#define DOCUMENTINTERACTIONFRAME_H

//general frame to hold interactive viewport and future widgets (tabbed doc mode)

#include "Framework/subwindow.h"

class Document;
class DocumentInteractionView;
class MainWindow;

class DocumentInteractionFrame : public SubWindow
{
    Q_OBJECT
public:
    DocumentInteractionFrame(MainWindow* parent, Document* doc);

public:
    void setScale(float scale);

private:
    Document* doc;
    DocumentInteractionView* viewport;

};

#endif // DOCUMENTINTERACTIONFRAME_H
