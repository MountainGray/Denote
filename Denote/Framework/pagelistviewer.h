#ifndef PAGELISTVIEWER_H
#define PAGELISTVIEWER_H

#include "Framework/subwindow.h"
#include "mainwindow.h"

class Document;
class PageList;

class PageListViewer : public SubWindow{
    Q_OBJECT
public:
    PageListViewer(MainWindow *parent, Document* doc);

private:
    Document* active_doc;
    PageList* pages;
};

#endif // PAGELISTVIEWER_H
