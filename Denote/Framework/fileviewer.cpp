#include "fileviewer.h"

#include <QPainter>
#include "Ui/ui.h"
#include "mainwindow.h"


FileViewer::FileViewer(UI* ui)
{
    this->ui = ui;
    browser = new QFileSystemModel(this);
    browser->setRootPath("C:/Users/Lewis/Desktop/Denote");

    QStringList filters;
    filters << "*.denote";

    browser->setNameFilters(filters);
    browser->setNameFilterDisables(false);
    //browser->setFilter(QDir::Files);

    setModel(browser);
    setRootIndex(browser->index(browser->rootPath()));

    //setItemDelegate(new Delegate());

    //setStyleSheet("QTreeView{font-size: 16px; outline:none;}");// font-weight:bold}");
    hideColumn(1);
    hideColumn(2);
    hideColumn(3);

    connect(this, &QTreeView::doubleClicked, this, &FileViewer::openDoc);
}


void FileViewer::openDoc(const QModelIndex &index)
{
    ui->getMain()->openDocument(browser->filePath(index));
}






Delegate::Delegate()
{

}


void Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (option.state & QStyle::State_MouseOver)
        painter->fillRect(option.rect, option.palette.highlight());

    painter->drawText(QPointF(5,25+option.rect.y()),index.data().toString());
}


QSize Delegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::sizeHint(option,index);
}
