#ifndef TABLETAPPLICATION_H
#define TABLETAPPLICATION_H

#include <QApplication>

class UI;

class TabletApplication : public QApplication
{    
public:
    using QApplication::QApplication;

    bool event(QEvent *event) override;
    void setUI(UI *ui){this->ui = ui;}

    void setupStyleSheet();

private:
    UI *ui = nullptr;
};

#endif // TABLETAPPLICATION_H
