#ifndef DOCUMENTINTERACTIONFRAME_H
#define DOCUMENTINTERACTIONFRAME_H

//general frame to hold interactive viewport and future widgets (tabbed doc mode)

<<<<<<< Updated upstream
#include "Framework/subwindow.h"
=======
>>>>>>> Stashed changes
#include <QLabel>
#include <QTabWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QSlider>

class Document;
class DocumentInteractionView;
<<<<<<< Updated upstream
class MainWindow;

class DocumentInteractionFrame : public SubWindow
{
    Q_OBJECT
public:
    DocumentInteractionFrame(MainWindow* parent, Document* doc = nullptr);
=======

class DocumentInteractionFrame : public QWidget
{
    Q_OBJECT
public:
    DocumentInteractionFrame(Document* doc = nullptr);
>>>>>>> Stashed changes
    ~DocumentInteractionFrame();

public slots:
    void setScale(float scale);

public:
    void addDocument(Document* doc);
    void setDocument(Document* doc);
    void updateDocNames();
    void resetScale();

private slots:
<<<<<<< Updated upstream
    void resetGL();
=======
>>>>>>> Stashed changes
    void focusCurrentDoc();
    void setHoles(bool holes);
    void setShadows(bool shadows);
    void setVertical();
    void setHorizontal();
    void setSeamless();
    void setFTV();

private:
<<<<<<< Updated upstream
    QLabel* empty_widget;
    QWidget* layout_widget;
=======
    QLabel* empty_widget;//not in use currently
>>>>>>> Stashed changes
    QTabWidget* tab_widget;
    QGridLayout* frame_layout;
    DocumentInteractionView* current_view = nullptr;

    QSlider* slider;
};

#endif // DOCUMENTINTERACTIONFRAME_H
