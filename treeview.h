#ifndef TREEVIEW_H
#define TREEVIEW_H

#endif // TREEVIEW_H
#include <QtGui>
class TreeView :public QTreeView
{
public:
        TreeView(QWidget * parent);
      //void iterateOverItems();
      //QList<QStandardItem*> returnTheItems();
        void mouseDoubleClickEvent(QMouseEvent *);
        QStringList items;
        QStringList explains;
        QStringList status0;
        QStringList status_str;
        QStandardItemModel *model;
};
