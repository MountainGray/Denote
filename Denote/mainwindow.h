#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QMenuBar>
#include <QApplication>
#include <QDockWidget>

class Document;
class DocumentInteractionFrame;
class UI;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    UI* getUI(){return this->ui;}
    QList<DocumentInteractionFrame*> getViews(){return views;}
    void addSubWindow(QDockWidget* widget, Qt::DockWidgetArea area = Qt::DockWidgetArea::BottomDockWidgetArea);

private slots:
    void newDocument();
    void save();
    void open();
    void about();
    void addView();
    void convertToEndless();
    void convertToPages();
    void toggleCropWorkArea();
    void print();
    void invertView();
    void toggleHoles();
    void toggleShadow();

private:
    void createMenus();
    UI* ui;
    QList<DocumentInteractionFrame*> views;
};
#endif // MAINWINDOW_H
