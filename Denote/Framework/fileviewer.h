#ifndef FILEVIEWER_H
#define FILEVIEWER_H

#include <QFileSystemModel>
#include <QTreeView>
#include <QStyledItemDelegate>

class UI;

class FileViewer: public QTreeView
{
    Q_OBJECT
public:
    FileViewer(UI* ui);

private slots:
    void openDoc(const QModelIndex &index);

private:
    UI* ui;
    QFileSystemModel* browser;
};

#endif // FILEVIEWER_H





class Delegate: public QStyledItemDelegate
{
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    Delegate();
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};


