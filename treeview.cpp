#include "treeview.h"

TreeView::TreeView(QWidget * parent) : QTreeView()
{
        model = new QStandardItemModel(1,4);
        model->setHeaderData(0, Qt::Horizontal, tr("服务"));
        model->setHeaderData(1, Qt::Horizontal, tr("状态"));
        model->setHeaderData(2, Qt::Horizontal, tr("说明"));
        model->setHeaderData(3,Qt::Horizontal,"");
        this->setSortingEnabled(true);
        this->header()->setClickable(true);
        this->header()->setSortIndicatorShown(true);
        this->setEditTriggers(NoEditTriggers);
        //this->header()->setResizeMode(QHeaderView::ResizeToContents);
        QFile file("/opt/Sinfo/service.ini");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
	  qDebug()<<"No find /opt/Sinfo/service.ini";
        return;
	}
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString tmp_str=in.readLine();
            QStringList tmp_list;
            tmp_list=tmp_str.split(tr("："));
            items.append(tmp_list.at(0));
            if(tmp_list.size()>0)
            {
            explains.append(tmp_list.at(1));
             }
     }
        file.close();
        int i;
        for (i=0;i < items.size();i++)
        {
            QStandardItem *item=new QStandardItem(items.at(i));
            item->setIcon(QIcon("/opt/kde4/share/icons/oxygen/48x48/actions/code-class.png"));
            model->setItem(i,0,item);
        }

        for(i=0;i<items.size();i++)
        {
           QStandardItem *item=new QStandardItem(tr("未知"));
           item->setIcon(QIcon("/opt/kde4/share/icons/oxygen/48x48/actions/dialog-cancel.png"));
           model->setItem(i,1,item);          
        }
         for (i=0;i < items.size();i++)
        {
            QStandardItem *item=new QStandardItem(explains.at(i));
            item->setIcon(QIcon("/opt/kde4/share/icons/oxygen/48x48/actions/draw-triangle2.png"));
            model->setItem(i,2,item);
        }
        setModel(model);
        this->setColumnWidth(0,180);
        this->setColumnWidth(1,70);
        this->setColumnWidth(2,850);
        this->setColumnWidth(3,30);
        this->sortByColumn(0,Qt::AscendingOrder);
        setParent(parent);
    }
/*this->header()->setSortIndicatorShown(true); // optional
this->header()->setClickable(true);
setSelectionBehavior(QAbstractItemView::SelectItems);
this->setSelectionMode(QAbstractItemView::SingleSelection);
setColumnHidden(1, true);
setContextMenuPolicy(Qt::CustomContextMenu);
*/

/*QList<QStandardItem*> TreeView::returnTheItems()
{
        return model->findItems("*", Qt::MatchWildcard | Qt::MatchRecursive);
}

void TreeView::iterateOverItems()
{
        QList<QStandardItem*> list = returnTheItems();

        foreach (QStandardItem* item, list) {
                qDebug() << item->text();
        }
}
*/
void TreeView::mouseDoubleClickEvent(QMouseEvent *)
{
        this->sortByColumn(currentIndex().column());        
   }

