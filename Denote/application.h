#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

class UI;

class Application : public QApplication
{    
public:
    Application(int, char**);

public:
    bool event(QEvent *event) override;
    void setUI(UI *ui){this->ui = ui;}

private:
    void setupStyleSheet();

private:
    UI *ui = nullptr;
};

#endif // APPLICATION_H
