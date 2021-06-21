#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QDockWidget>
#include <QMainWindow>
#include <QEvent>

class SubWindow : public QDockWidget {
    Q_OBJECT
public:
    SubWindow(QMainWindow *parent = nullptr);
    ~SubWindow();

protected:
    void changeEvent(QEvent *event) override;

private slots:
    void makeTopLevel(bool);

private:
    bool active;
    QMainWindow *mainWindow;
    QWidget *titlebar;
};

#endif // SUBWINDOW_H
