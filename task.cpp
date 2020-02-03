#include "task.h"
#include <QDebug>
#include "Windows.h"


task::task()
{

}

task::~task()
{

}

void task::doWork()
{
    //Цикл автообновления, зависит от частоты
    while (stop == 0)
    {
        emit timedraw(); //Сигнал построения графика и записи в файл
        Sleep(1000/(this->grc));
    }
    emit workFinished();
}
