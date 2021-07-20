#ifndef DOCUMENTSUMMARYFRAME_H
#define DOCUMENTSUMMARYFRAME_H

//Frame to hold document summary view and future other widgets

#include "Framework/subwindow.h"

#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

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
    QComboBox* page_combo;
    QGridLayout* frame_layout;
    QGridLayout* button_layout;
    QWidget* frame_widget;
    QPushButton* new_button;
    QPushButton* up_button;
    QPushButton* down_button;
    QLabel* empty_widget;
};

#endif // DOCUMENTSUMMARYFRAME_H
