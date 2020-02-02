#ifndef TASK_H
#define TASK_H

#include <QObject>
#include "mainwindow.h"

class task : public QObject
{
Q_OBJECT
public:
    task();
    ~task();
public slots:
    // doWork must emit workFinished when it is done.
    void doWork();
signals:
    void workFinished();
public:
    MainWindow *mw;

};

#endif // TASK_H
