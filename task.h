#ifndef TASK_H
#define TASK_H

#include <QObject>
//#include "mainwindow.h"

class task : public QObject
{
Q_OBJECT
public:
    task();
    ~task();

public slots:
    void doWork();
signals:
    void workFinished();
    void timedraw();
public:
    int grc;
    int stop;
};

#endif // TASK_H
