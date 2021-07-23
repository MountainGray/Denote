#ifndef DOCUMENTSUMMARYFRAME_H
#define DOCUMENTSUMMARYFRAME_H

//Frame to hold document summary view and future other widgets

#include "Framework/subwindow.h"

#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>

class MainWindow;
class DocumentSummaryView;

class DocumentSummaryFrame : public SubWindow
{
    Q_OBJECT
public:
    DocumentSummaryFrame(MainWindow* parent);
    ~DocumentSummaryFrame();

public:
    void setView(DocumentSummaryView* view);

private slots:
    void addPage();
    void raisePage();
    void lowerPage();
    void resetGL();

private:
    DocumentSummaryView* viewport = nullptr;

    QGridLayout* frame_layout;
    QLabel* empty_widget;
    QWidget* frame_widget;
    QGridLayout* button_layout;

    QComboBox* page_combo;
    QPushButton* new_button;
    QPushButton* up_button;
    QPushButton* down_button;
    QSpinBox* page_width;
    QSpinBox* page_height;

};

#endif // DOCUMENTSUMMARYFRAME_H
