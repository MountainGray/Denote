#ifndef DOCUMENTINTERACTIONFRAME_H
#define DOCUMENTINTERACTIONFRAME_H

//general frame to hold interactive viewport and future widgets (tabbed doc mode)

#include <QLabel>
#include <QTabWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QSlider>

class Document;
class DocumentInteractionView;

class DocumentInteractionFrame : public QWidget
{
    Q_OBJECT
public:
    DocumentInteractionFrame(Document* doc = nullptr);
    ~DocumentInteractionFrame();

public slots:
    void setScale(float scale);

public:
    void addDocument(Document* doc);
    void setDocument(Document* doc);
    void updateDocNames();
    void resetScale();

private slots:
    void focusCurrentDoc();
    void setHoles(bool holes);
    void setShadows(bool shadows);
    void setVertical();
    void setHorizontal();
    void setSeamless();
    void setFTV();
    void removeTab(int index);

private:
    QWidget* layout_widget;
    QLabel* empty_widget;//not in use currently
    QTabWidget* tabs;
    QGridLayout* frame_layout;
    DocumentInteractionView* current_view = nullptr;

    QSlider* slider;
};

#endif // DOCUMENTINTERACTIONFRAME_H
