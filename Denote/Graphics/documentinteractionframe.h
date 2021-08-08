#ifndef DOCUMENTINTERACTIONFRAME_H
#define DOCUMENTINTERACTIONFRAME_H

//general frame to hold interactive viewport and future widgets (tabbed doc mode)

#include "Framework/subwindow.h"
#include <QLabel>
#include <QTabWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QSlider>

class Document;
class DocumentInteractionView;
class MainWindow;

class DocumentInteractionFrame : public SubWindow
{
    Q_OBJECT
public:
    DocumentInteractionFrame(MainWindow* parent, Document* doc = nullptr);
    ~DocumentInteractionFrame();

public slots:
    void setScale(float scale);

public:
    void addDocument(Document* doc);
    void setDocument(Document* doc);
    void updateDocNames();
    void resetScale();

private slots:
    void resetGL();
    void focusCurrentDoc();
    void setHoles(bool holes);
    void setShadows(bool shadows);
    void setVertical();
    void setHorizontal();
    void setSeamless();
    void setFTV();

private:
    QLabel* empty_widget;
    QWidget* layout_widget;
    QTabWidget* tab_widget;
    QGridLayout* frame_layout;
    DocumentInteractionView* current_view = nullptr;

    QSlider* slider;
};

#endif // DOCUMENTINTERACTIONFRAME_H
