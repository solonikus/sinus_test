#ifndef ONLINE_H
#define ONLINE_H

#include <QObject>
#include "mainwindow.h"

class online:public QObject
{
    Q_OBJECT

public:
    online();

public slots:
    void online_mod();

public:
    MainWindow *main;
};

#endif // ONLINE_H
