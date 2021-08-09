#ifndef DOCUMENTSUMMARYFRAME_H
#define DOCUMENTSUMMARYFRAME_H

//Frame to hold document summary view and future other widgets

<<<<<<< Updated upstream
#include "Framework/subwindow.h"

=======
>>>>>>> Stashed changes
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>

<<<<<<< Updated upstream
class MainWindow;
class DocumentSummaryView;

class DocumentSummaryFrame : public SubWindow
{
    Q_OBJECT
public:
    DocumentSummaryFrame(MainWindow* parent);
=======

class DocumentSummaryView;

class DocumentSummaryFrame : public QWidget
{
    Q_OBJECT
public:
    DocumentSummaryFrame();
>>>>>>> Stashed changes
    ~DocumentSummaryFrame();

public:
    void setView(DocumentSummaryView* view);
    DocumentSummaryView* getView(){return viewport;}

private slots:
    void addPage();
    void raisePage();
    void lowerPage();
<<<<<<< Updated upstream
    void resetGL();
=======
>>>>>>> Stashed changes

private:
    DocumentSummaryView* viewport = nullptr;

    QGridLayout* frame_layout;
    QLabel* empty_widget;
<<<<<<< Updated upstream
    QWidget* frame_widget;
=======
>>>>>>> Stashed changes
    QGridLayout* button_layout;

    QComboBox* page_combo;
    QPushButton* new_button;
    QPushButton* up_button;
    QPushButton* down_button;
    QSpinBox* page_width;
    QSpinBox* page_height;

};

#endif // DOCUMENTSUMMARYFRAME_H
