#ifndef DOCUMENTSUMMARYFRAME_H
#define DOCUMENTSUMMARYFRAME_H

//Frame to hold document summary view and future other widgets

#include "Framework/subwindow.h"

#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>

class MainWindow;
class Document;
class DocumentSummaryView;

class DocumentSummaryFrame : public SubWindow
{
public:
    DocumentSummaryFrame(MainWindow* parent, Document* doc);

private slots:
    void addPage();
    void raisePage();
    void lowerPage();

private:
    Document* doc;
    DocumentSummaryView* viewport;
    QComboBox* page_combo;
    QGridLayout* frame_layout;
    QGridLayout* button_layout;
    QWidget* frame_widget;
    QPushButton* new_button;
    QPushButton* up_button;
    QPushButton* down_button;
};

#endif // DOCUMENTSUMMARYFRAME_H
