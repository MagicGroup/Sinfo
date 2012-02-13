#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "treeview.h"
#include "thread.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    TreeView *view;
    QString getit;
protected:
    void resizeEvent(QResizeEvent *);
protected slots:
    void showMenu(const QPoint & pos);
private slots:
    void serviceStart();
    void serviceStop();
    void updateinfo();
    void serviceStartit();
    void serviceStopit();
    void updateit();
private:
     QVBoxLayout *layout;
     Thread *m_thread;
 };

#endif // MAINWINDOW_H
