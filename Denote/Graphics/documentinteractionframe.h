#ifndef DOCUMENTINTERACTIONFRAME_H
#define DOCUMENTINTERACTIONFRAME_H

//general frame to hold interactive viewport and future widgets (tabbed doc mode)

#include <QTabBar>
#include <QPushButton>
#include <QSlider>
#include <QStackedWidget>
#include <QBoxLayout>
#include <QToolBar>


class UI;
class Document;
class DocumentInteractionView;

class DocumentInteractionFrame : public QWidget
{
    Q_OBJECT
public:
    DocumentInteractionFrame(UI* ui, Document* doc = nullptr);
    ~DocumentInteractionFrame();

public:
    void addDocument(Document* doc);
    void setCurrentDocument(Document* doc);
    void updateDocNames(Document* doc);
    void updateScaleSlider();

public slots:
    void setScale(float scale);
    void setCurrentIndex(int i);

private:
    void setupWidgets();
    void updateLayoutType();

private slots:
    void tabMoved(int from, int to);
    void setLayoutType(QAction* layout);
    void addNewDocument();
    void showTabContextMenu(const QPoint &point);
    void closeTab();

private:
    UI* ui;
    QTabBar* tabs;
    QStackedWidget* view_stack;
    QList<DocumentInteractionView*> viewports;
    QSlider* scale;
    QToolBar* layouts;
};

#endif // DOCUMENTINTERACTIONFRAME_H
