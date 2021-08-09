#ifndef DOCUMENTSUMMARYFRAME_H
#define DOCUMENTSUMMARYFRAME_H

//Frame to hold document summary view and future other widgets

<<<<<<< Updated upstream
<<<<<<< Updated upstream
#include "Framework/subwindow.h"

=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>

<<<<<<< Updated upstream
<<<<<<< Updated upstream
class MainWindow;
=======

>>>>>>> Stashed changes
class DocumentSummaryView;

class DocumentSummaryFrame : public QWidget
{
    Q_OBJECT
public:
<<<<<<< Updated upstream
    DocumentSummaryFrame(MainWindow* parent);
=======

class DocumentSummaryView;

class DocumentSummaryFrame : public QWidget
{
    Q_OBJECT
public:
    DocumentSummaryFrame();
>>>>>>> Stashed changes
=======
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
<<<<<<< Updated upstream
    void resetGL();
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes

private:
    DocumentSummaryView* viewport = nullptr;

    QGridLayout* frame_layout;
    QLabel* empty_widget;
<<<<<<< Updated upstream
<<<<<<< Updated upstream
    QWidget* frame_widget;
=======
>>>>>>> Stashed changes
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
