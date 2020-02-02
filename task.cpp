#include "task.h"
#include <QDebug>


task::task()
{

}

task::~task()
{

}

void task::doWork()
{
    draw(*mw);
     qDebug() << "Hello!!!!";
}
