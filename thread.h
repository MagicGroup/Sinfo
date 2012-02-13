#ifndef THREAD_H
#define THREAD_H
#include <QtGui>

class Thread : public QThread
{
    Q_OBJECT
public:
    Thread();
    QStringList items,explains;
    int status[100];
protected:
    void run();
};
#endif // THREAD_H
