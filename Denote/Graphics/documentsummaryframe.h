#ifndef DOCUMENTSUMMARYFRAME_H
#define DOCUMENTSUMMARYFRAME_H

//Frame to hold document summary view and future other widgets

#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QStackedWidget>

class DocumentSummaryView;

class DocumentSummaryFrame : public QWidget
{
    Q_OBJECT
public:
    DocumentSummaryFrame();
    ~DocumentSummaryFrame();

public:
    void addSummaryView(DocumentSummaryView* view);
    void setSummaryView(DocumentSummaryView* view);
    //DocumentSummaryView* getView(){return viewport;}

private slots:
    void addPage();
    void raisePage();
    void lowerPage();

private:
    QStackedWidget* stack;
    DocumentSummaryView* summary_view = nullptr;

    QGridLayout* frame_layout;
    QLabel* empty_widget;//not in use rn
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
