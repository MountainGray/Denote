#ifndef DOCUMENTINTERACTIONFRAME_H
#define DOCUMENTINTERACTIONFRAME_H

//general frame to hold interactive viewport and future widgets (tabbed doc mode)

#include "Framework/subwindow.h"
#include <QLabel>
#include <QTabWidget>

class Document;
class DocumentInteractionView;
class MainWindow;

class DocumentInteractionFrame : public SubWindow
{
    Q_OBJECT
public:
    DocumentInteractionFrame(MainWindow* parent, Document* doc = nullptr);
    ~DocumentInteractionFrame();

public:
    void setScale(float scale);
    void addDocument(Document* doc);
    void setDocument(Document* doc);

private slots:
    void resetGL();
    void focusCurrentDoc();

private:
    QLabel* empty_widget;
    QTabWidget* tab_widget;
};

#endif // DOCUMENTINTERACTIONFRAME_H
