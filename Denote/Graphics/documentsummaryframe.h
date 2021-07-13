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

private:
    Document* doc;
    DocumentSummaryView* viewport;
    QComboBox* page_combo;
    QGridLayout* menu_layout;
    QWidget* menu_widget;
    QPushButton* new_button;
};

#endif // DOCUMENTSUMMARYFRAME_H
