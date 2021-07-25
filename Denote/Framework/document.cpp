#include "document.h"
#include "Graphics/pagelayoutscene.h"
#include "Ui/ui.h"
#include "Graphics/page.h"
#include "Graphics/pageportal.h"
#include "Framework/History/historymanager.h"
#include "Framework/History/historymanagerviewer.h"
#include "Graphics/documentsummaryview.h"
#include "Graphics/documentsummaryframe.h"


Document::Document(UI* ui){
    this->ui = ui;

    history_manager = new HistoryManager(this);
    summary_view = new DocumentSummaryView(this);

    ui->setActiveDocument(this);
}


Document::~Document(){

}


void Document::addPage(Page *page, int index){
    if(index == -1 or index > pages.length()) index = pages.length();

    //add the page to the documents data
    pages.insert(index,page);

    //create a page_portal between the page_layout and page
    foreach(PageLayoutScene* page_layout, layouts){
        new PagePortal(page, page_layout, index);
        page_layout->updatePageLayout();
    }
}


void Document::removePage(Page *page){

    //remove the page from the documents data
    pages.removeAll(page);

    //remove the page_portal between the page_layout and page
    foreach(PagePortal* portal, page->getPortals()){
        delete portal;
    }
    foreach(PageLayoutScene* page_layout, layouts){
        page_layout->updatePageLayout();
    }
}


void Document::movePage(Page *page, int new_index)
{
    if(new_index >= 0 and new_index < pages.length()){
        int old_index = pages.indexOf(page);
        pages.move(old_index, new_index);
        foreach(PageLayoutScene* page_layout, layouts){
            page_layout->portals.move(old_index, new_index);
            page_layout->updatePageLayout();
        }
    }
}


void Document::updateAll(QRectF update_area)
{
    foreach(Page* page, pages){
        page->updatePortals(update_area);
    }
}


void Document::focusDoc()
{
    ui->setActiveDocument(this);
    ui->getHistoryManagerViewer()->setHistoryManager(history_manager);
    ui->getSummaryFrame()->setView(summary_view);
}


#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#include <QPrinter>
#endif

#include <QFileDialog>
#include <QDesktopServices>

void Document::print()
{
#if defined(QT_PRINTSUPPORT_LIB)

    QString file_name = QFileDialog::getSaveFileName(this->getUI()->getMain(),QObject::tr("Save as PDF"),"",QObject::tr("PDF Files (*.pdf)"));
    if(file_name.isNull()) return;

    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(file_name);
    printer.setFullPage(true);

    QPainter painter;

    for(int i = 0; i < pages.length(); i++){
        Page* page = pages.at(i);
        printer.setPageSize(QPageSize(page->getPageSize(),QPageSize::Point,"",QPageSize::SizeMatchPolicy::ExactMatch));
        if(i == 0) painter.begin(&printer);
        else printer.newPage();
        page->render(&painter);
    }
    painter.end();
    QDesktopServices::openUrl(QUrl::fromLocalFile(file_name));

#endif
}

