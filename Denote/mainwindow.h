#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QMenuBar>
#include <QApplication>

class Document;
class DocumentView;
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

    QWidget *main_widget = nullptr;

};
#endif // MAINWINDOW_H
