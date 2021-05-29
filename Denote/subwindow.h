#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QDockWidget>
#include <QMainWindow>

class SubWindow : public QDockWidget {
    Q_OBJECT
public:
    explicit SubWindow(QMainWindow *parent = nullptr, QWidget *child = nullptr);
    virtual ~SubWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    bool active;
    QMainWindow *mainWindow;
};

#endif // SUBWINDOW_H
