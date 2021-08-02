#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QGraphicsScene>

class PageLayoutScene;
class Page;
class UI;
class HistoryManager;
class DocumentSummaryView;

class Document
{
public:
    Document(UI* ui, bool endless = false);
    ~Document();

public:
    void addLayout(PageLayoutScene* layout){layouts.append(layout);}
    void removeLayout(PageLayoutScene* layout){layouts.removeAll(layout);}
    QList<PageLayoutScene*> getLayouts(){return layouts;}
    void updateAllLayouts();

    void addPage(Page* page, int index = -1);
    void removePage(Page* page);
    void movePage(Page* page, int new_index);
    QList<Page*> getPages(){return pages;}

    UI* getUI(){return ui;}
    HistoryManager* getHistoryManager(){return history_manager;}
    DocumentSummaryView* getSummaryView(){return summary_view;}
    void updateAll(QRectF update_area = QRectF());

    void focusDoc();
    void print();

    void convertToEndless();
    void convertToPages();
    bool isEndless(){return endless;}
    void updateEndlessLength(bool ignore_views = false);

    void CropWorkArea(bool crop);
    bool isWorkAreaCropped(){return crop_work_area;}

private:
    QList<Page*> pages;
    UI* ui;
    QList<PageLayoutScene*> layouts;
    HistoryManager* history_manager;
    DocumentSummaryView* summary_view;
    bool endless;
    bool crop_work_area = false;
};

#endif // DOCUMENT_H
