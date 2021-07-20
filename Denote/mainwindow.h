#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QMenuBar>
#include <QApplication>
#include <QDockWidget>

class Document;
class DocumentInteractionFrame;
class DocumentSummaryFrame;
class DocumentSummaryView;
class UI;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    UI* getUI(){return this->ui;}
    void addSubWindow(QDockWidget* widget, Qt::DockWidgetArea area = Qt::DockWidgetArea::BottomDockWidgetArea);
    void setSummary(DocumentSummaryView* summary_view);

private slots:
    void newDocument();
    bool save();
    void open();
    void about();
    void addView();

private:
    void createMenus();
    QList<QDockWidget *> subWindows;
    UI* ui;
    QList<DocumentInteractionFrame*> views;
    DocumentSummaryFrame* summary_frame;
};
#endif // MAINWINDOW_H
