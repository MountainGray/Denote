#include "fileviewer.h"

FileViewer::FileViewer()
{
    browser = new QFileSystemModel(this);
    browser->setRootPath("C:/Users/Lewis/Desktop");

    QStringList filters;
    filters << "*.denote";

    browser->setNameFilters(filters);
    browser->setNameFilterDisables(false);
    browser->setFilter(QDir::Files);

    setModel(browser);
    setRootIndex(browser->index("C:/Users/Lewis/Desktop"));

    hideColumn(1);
    hideColumn(2);
    hideColumn(3);
}
