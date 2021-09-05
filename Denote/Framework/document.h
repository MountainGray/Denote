#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "Framework/serializable.h"
#include <QRectF>

class PageLayoutScene;
class Page;
class UI;
class HistoryManager;
class DocumentSummaryView;

class Document: public QObject, public Serializable
{
    Q_OBJECT
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

    void serializeRead(QDataStream &in) override;
    void serializeWrite(QDataStream &out) override;

    void setName(QString name);
    QString getName(){return doc_name;}

private:
    QList<Page*> pages;
    UI* ui;
    QList<PageLayoutScene*> layouts;
    HistoryManager* history_manager;
    DocumentSummaryView* summary_view;
    bool endless;
    QString doc_name = "Untitled";
};

#endif // DOCUMENT_H
