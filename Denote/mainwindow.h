#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QMenuBar>
#include <QApplication>
#include <QDockWidget>

class Document;
class DocumentView;
class UI;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    bool save();
    void open();
    void about();

private:
    void createMenus();
    QList<QDockWidget *> subWindows;
    UI* ui;


};
#endif // MAINWINDOW_H
