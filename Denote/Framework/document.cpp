#include "document.h"
#include "Graphics/pagelayoutscene.h"
#include "Ui/ui.h"
#include "Graphics/page.h"
#include "Graphics/pageportal.h"
#include "Framework/History/historymanager.h"
#include "Framework/History/historymanagerviewer.h"
#include "Graphics/documentsummaryview.h"
#include "Graphics/documentsummaryframe.h"
#include "Graphics/documentinteractionframe.h"
<<<<<<< Updated upstream
<<<<<<< Updated upstream
=======
#include "mainwindow.h"
>>>>>>> Stashed changes
=======
#include "mainwindow.h"
>>>>>>> Stashed changes


#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#include <QPrinter>
#endif

#include <QFileDialog>
#include <QDesktopServices>


Document::Document(UI* ui, bool endless){
    this->ui = ui;
    this->endless = endless;

    history_manager = new HistoryManager(this);
    summary_view = new DocumentSummaryView(this);

    ui->setActiveDocument(this);
<<<<<<< Updated upstream
<<<<<<< Updated upstream
=======
    ui->getHistoryManagerViewer()->addWidget(history_manager);
>>>>>>> Stashed changes
=======
    ui->getHistoryManagerViewer()->addWidget(history_manager);
>>>>>>> Stashed changes
    focusDoc();
}


Document::~Document(){

}


void Document::updateAllLayouts()
{
    foreach(PageLayoutScene* page_layout, layouts){
        page_layout->updatePageLayout();
    }
}


void Document::addPage(Page *page, int index){
    page->setDisplayMode(ui->getDisplayMode());
    convertToPages();

    if(index == -1 or index > pages.length()) index = pages.length();

    //add the page to the documents data
    pages.insert(index,page);

    //create a page_portal between the page_layout and page
    foreach(PageLayoutScene* page_layout, layouts){
        new PagePortal(page, page_layout, index);
        page_layout->updatePageLayout();
    }
    if(ui->getActiveLayout() != nullptr and not ui->getActiveLayout()->getPortals().isEmpty()){
        ui->setActivePortal(ui->getActiveLayout()->getPortals().at(0));
    }
    ui->setActivePage(page);
}


void Document::removePage(Page *page){

    //remove the page from the documents data
    pages.removeAll(page);

    //remove the page_portal between the page_layout and page
    foreach(PagePortal* portal, page->getPortals()){
        delete portal;
    }
    updateAllLayouts();

    delete page;
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
    updateAllLayouts();
}


void Document::focusDoc()
{
    ui->setActiveDocument(this);
    ui->getHistoryManagerViewer()->setHistoryManager(history_manager);
    ui->getSummaryFrame()->setView(summary_view);
}


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
<<<<<<< Updated upstream
<<<<<<< Updated upstream
=======
        qDebug() << QPageSize(page->getPageSize(),QPageSize::Point,"",QPageSize::SizeMatchPolicy::ExactMatch).size(QPageSize::Inch);
>>>>>>> Stashed changes
=======
        qDebug() << QPageSize(page->getPageSize(),QPageSize::Point,"",QPageSize::SizeMatchPolicy::ExactMatch).size(QPageSize::Inch);
>>>>>>> Stashed changes
        if(i == 0) painter.begin(&printer);
        else printer.newPage();
        page->render(&painter);
    }
    painter.end();
    QDesktopServices::openUrl(QUrl::fromLocalFile(file_name));

#endif
}


void Document::convertToEndless()
{
    if(endless or pages.isEmpty()) return;

    Page* new_page = new Page();
    new_page->setBackgroundType(LinesMargin);

    int y_offset = 0;

    foreach(Page* page, pages){
        foreach(QGraphicsItem* item, page->items()){
            new_page->addItem(item);
            item->moveBy(0,y_offset);
        }
        y_offset += page->getHeight();
        removePage(page);
    }

    endless = true;
    addPage(new_page);
    new_page->findLowestObject();
    updateEndlessLength();
}


void Document::convertToPages()
{
    if(!endless or pages.length() != 1) return;

    updateEndlessLength(true);
    endless = false;

    const int new_height = 1100;

    Page* first_page = pages.at(0);
    int y_offset = 0;

    while(true){
        QList<QGraphicsItem*> area_items = first_page->items(QRect(0,y_offset,first_page->getWidth(),new_height));
        if(y_offset+new_height >= first_page->getPageBounds().bottom() and area_items.length() == 0) break;

        Page* new_page = new Page();
        new_page->setBackgroundType(Engineering);
        new_page->setPageSize(850,new_height);
        addPage(new_page);

        foreach(QGraphicsItem* item, area_items){
            new_page->addItem(item);
            item->moveBy(0,-y_offset);
        }

        y_offset += new_height;
    }

    removePage(first_page);
    updateAllLayouts();
}


void Document::updateEndlessLength(bool ignore_views)
{
    if(!endless or pages.length() != 1) return;

    int lowest = 0;
    Page* page = pages.at(0);

    if(!ignore_views){
        foreach(PageLayoutScene* layout, layouts){
            if(layout->isInteractive()){
                int view_bottom = layout->getView()->mapToScene(layout->getView()->rect()).boundingRect().bottom();
                if(view_bottom > lowest) lowest = view_bottom;
            }
        }
    }
    if(page->getLowestPoint() > lowest) lowest = page->getLowestPoint();

    const int change_length = 1100;
    int full_length = (std::ceil(lowest/change_length)+1)*change_length;

    if(page->getHeight() != full_length){
        page->setPageSize(page->getWidth(),full_length);
        updateAllLayouts();
    }
}


void Document::serializeRead(QDataStream &in)
{
    size_t num_pages;
    in >> num_pages;
    in >> endless;

    for(size_t i = 0; i < num_pages; i++){
        Page* new_page = new Page();
        new_page->serializeRead(in);
        addPage(new_page);
    }
}


void Document::serializeWrite(QDataStream &out)
{
    out << pages.length();
    out << endless;
    foreach(Page* page, pages){
        page->serializeWrite(out);
    }
}


void Document::setName(QString name)
{
    doc_name = name;
    foreach(DocumentInteractionFrame* frame, ui->getMain()->getViews()){
        frame->updateDocNames();
    }
}
