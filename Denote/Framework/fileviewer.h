#ifndef FILEVIEWER_H
#define FILEVIEWER_H

#include <QFileSystemModel>
#include <QTreeView>

class FileViewer: public QTreeView
{
public:
    FileViewer();

private:
    QFileSystemModel* browser;
};

#endif // FILEVIEWER_H
