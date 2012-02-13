#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{  
 // m_textEdit = new QTextEdit(this);
  QTextCodec::setCodecForTr(QTextCodec::codecForName("GB18030"));
  this->setWindowTitle(tr("Magic LInux 服务管理器"));
  this->setWindowIcon(QIcon("/opt/kde4/share/icons/oxygen/48x48/places/repository.png"));
   view=new TreeView(this);
   resize(800,600);
   view->setGeometry(QRect(0,0,800,600));
   //view->setGeometry(QRect(0,0,QApplication::desktop()->width(), QApplication::desktop()->height()));
   view->setContextMenuPolicy(Qt::CustomContextMenu);
      connect(view,SIGNAL(customContextMenuRequested(const QPoint &)),this,SLOT(showMenu(const QPoint &)));
   QTimer::singleShot(1000,this,SLOT(updateinfo()));

 }

MainWindow::~MainWindow()
{

}
void MainWindow::showMenu(const QPoint & pos)
{
    static QMenu * menu = 0;
    QModelIndex index0 = view->currentIndex();
    //qDebug() << view->currentIndex().data().toString();
    if(!menu)
    {
        menu = new QMenu(this->view);
        menu->addAction(tr("开启"),this,SLOT(serviceStartit()));
        menu->addAction(tr("停止"),this,SLOT(serviceStopit()));
        menu->addAction(tr("刷新"),this,SLOT(updateit()));
    }
    menu->popup(this->view->mapToGlobal(pos+QPoint(0,20)));
}

void MainWindow::serviceStart()
{
    //QAction * action = qobject_cast<QAction*>(sender());
    //qDebug() << action->text() << "clicked";
   QString program,serviceName;
   int status=256;
   int row;
   row=view->currentIndex().row();
   QModelIndex index0=view->model->index(row,0);
   serviceName= index0.data().toString();
   program="service "+serviceName+" start;chkconfig "+serviceName+" --level 5 on";
   system(program.toAscii().data());
   program="service "+serviceName+" status>/dev/null";
   status=system(program.toAscii().data());
   if(serviceName=="ntpdate")
   {status=0;}
   if(serviceName=="bluetooth")
   {status=0;}
   if(serviceName=="readahead_early")
   {status=0;}
   if(serviceName=="readahead_later")
   {status=0;}
   if(serviceName=="lm_sensors")
   {status=0;}
   if(serviceName=="fuse")
   {status=0;}
   if(status==0)
   {
      view->model->setData(view->model->index(row,1),tr("开启"));
      view->model->item(row,1)->setIcon(QIcon("/opt/kde4/share/icons/oxygen/48x48/actions/dialog-ok-apply.png"));
       }
}

void MainWindow::serviceStop()
{
QString program,serviceName;
int status=0;
int row;
row=view->currentIndex().row();
QModelIndex index0=view->model->index(row,0);
serviceName= index0.data().toString();
program="service "+serviceName+" stop;chkconfig "+serviceName+" --level 5 off";
system(program.toAscii().data());
program="pgrep "+serviceName+">/dev/null";
status=system(program.toAscii().data());
if(serviceName=="xfs")
{status=256;}
if(status==256)
    {
      view->model->setData(view->model->index(row,1),tr("关闭"));
       view->model->item(row,1)->setIcon(QIcon("/opt/kde4/share/icons/oxygen/48x48/actions/dialog-close.png"));
    }
}
void MainWindow::serviceStartit()
{
 QTimer::singleShot(1000,this,SLOT(serviceStart()));
}
void MainWindow::serviceStopit()
{
 QTimer::singleShot(1000,this,SLOT(serviceStop()));
}
void MainWindow::updateit()
{
 QTimer::singleShot(1000,this,SLOT(updateinfo()));
}
 void MainWindow::resizeEvent(QResizeEvent *)
{
    view->resize(this->size());
}
 void MainWindow::updateinfo()
 {
    m_thread = new Thread();
    m_thread->start();
    m_thread->wait();
    m_thread->terminate();
    int i;
     QString info;
     for(i=0;i<view->items.size();i++)
     {
         QIcon icon;
         switch(m_thread->status[i])
         {
             case 0:
             info=tr("开启");
             icon.addFile("/opt/kde4/share/icons/oxygen/48x48/actions/dialog-ok-apply.png");
             break;
             case 256:
             info=tr("关闭");
             icon.addFile("/opt/kde4/share/icons/oxygen/48x48/actions/dialog-close.png");
             break;
             default:
             info=tr("未知");
             icon.addFile("/opt/kde4/share/icons/oxygen/48x48/actions/dialog-cancel.png");
             break;
          }
        //view->model->setData(view->model->index(i,1),info);
        view->model->item(i,1)->setIcon(icon);
        view->model->item(i,1)->setText(info);
        view->model->item(i,0)->setText(m_thread->items.at(i));
        view->model->item(i,2)->setText(m_thread->explains.at(i));
        }
     view->sortByColumn(1,Qt::AscendingOrder);
}

