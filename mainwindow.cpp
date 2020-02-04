#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task.h"
#include <fstream>

void init_potok(potok *a, double p)
{
    a->pt = p;
    a->enable = true;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Построение сцены, абсциссы и ординаты
    scene = new QGraphicsScene(ui->graphicsView);
    QPen pen(Qt::gray);
    scene->addLine(-190, 0,190,0,pen);//x
    scene->addLine(0,-190,0,190,pen);//y
    scene->addText("0");

    //Добавляем обозначение времени к сцене
    QGraphicsTextItem * tm = new QGraphicsTextItem;
    tm->setPos(185,0);
    tm->setPlainText("t");
    scene->addItem(tm);

    //Выводим в виджет
    ui->graphicsView->setScene(scene);

    //Инициализируем отдельно потоки
    a = new potok;
    b = new potok;
    c = new potok;
    init_potok(a, 3);
    init_potok(b, 1);
    init_potok(c, 1);

    //Установка минимальных значений потока в интерфейс
    ui->doubleSpinBox->setValue(3);
    ui->doubleSpinBox_2->setValue(1);
    ui->doubleSpinBox_3->setValue(1);

    //Инициализация автообновления в положение false
    this->onl = false;
}

void MainWindow::init_scene()
{

    // Перерисовка сцены для корректной работы Автообновления
    QPen pen(Qt::gray);
    scene->addLine(-190, 0,190,0,pen);//x
    scene->addLine(0,-190,0,190,pen);//y
    scene->addText("0");

    QGraphicsTextItem * tm = new QGraphicsTextItem;
    tm->setPos(185,0);
    tm->setPlainText("t");
    scene->addText("0");
    scene->addItem(tm);

    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void draw(MainWindow &main) //Функция отрисовки синусоидной
{
    //Два значения для отрисовки линии
    double y;
    double y1;
    //Два значения для отрисовки линии
    double xf;
    double xf1;
    //Копирование значений потоков
    double a;
    double b;
    double c;
    //Размеры пикселей
    int px;
    int py;
    QPen pen(Qt::red);

    //Установка значений потока и проверка их доступности
    y = 0;
    if (main.a->enable == false)
        a = 0;
    else
        a = main.a->pt;
    if (main.b->enable == false)
        b = 1;
    else
        b = main.b->pt;
    if (main.c->enable == false)
        c = 1;
    else
        c = main.c->pt;

   // формула для получения размеров пикселя
    px = ((main.ui->graphicsView->width() / 2) - 10) / main.ui->spinBox_2->value();
    py =  ((main.ui->graphicsView->height() / 2) - 10) / int(b + a);
    //установка макс.значения Ординаты
    main.ui->spinBox->setValue(int(b + a));

    //Проход по всем пикселям для отрисовки кривой
    for (double x=-185; x < 186; x++)
    {
        //Координаты иксов для текущего и след. значения
        xf = x / px;
        xf1 = (x + 1) / px;
        //координаты игрек для текущего и след. значения
        y = (a + b * sin(c * xf)) * (-1);
        y1 = (a + b * sin(c * xf1)) * (-1);
        //возможность отрисовать только точки, без линий
//        double rad = 1;
//        scene->addEllipse(x-rad, (y * py)-rad, rad*2.0, rad*2.0, QPen(), QBrush(Qt::SolidPattern));
        //создании линии от текущего до следующего
        main.scene->addLine(x,y * py,x+1,y1 * py,pen);
    }
    main.ui->graphicsView->setScene(main.scene);
}

void writefile(potok &a, potok &b, potok &c)
{
    std::ofstream fout; // создаём объект класса ofstream для записи
    fout.open("testfile.txt", std::ios::app);  // открываем файл для записи в конец

    //Запись в файл текущих потоков
    if (a.enable == true)
        fout << "A:" << a.pt << ";";
    else
        fout << "A:x;";
    if (b.enable == true)
        fout << "B:" << b.pt << ";";
    else
        fout << "B:x;";
    if (c.enable == true)
        fout << "C:" << c.pt << ";";
    else
        fout << "C:x;";
    fout << std::endl;
    fout.close();                          // закрываем файл
}

void MainWindow::on_pushButton_clicked()
{
    //Удаление и создании новой сцены для того, что бы не показывался мусор
    delete scene;
    scene = new QGraphicsScene(ui->graphicsView);
    init_scene();
    draw(*this);
    writefile(*a, *b, *c);
}

//Блок включения и выключения потоков

void MainWindow::on_checkBox_clicked()
{
    if (a->enable == true)
    {
        a->enable = false;
    }
    else
        a->enable = true;
}

void MainWindow::on_checkBox_2_clicked()
{
    if (b->enable == true)
        b->enable = false;
    else
        b->enable = true;
}

void MainWindow::on_checkBox_3_clicked()
{
    if (c->enable == true)
        c->enable = false;
    else
        c->enable = true;
}

//Запись новых значений потока в память при его изменении

void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    this->a->pt=arg1;
}

void MainWindow::on_doubleSpinBox_2_valueChanged(double arg1)
{
    this->b->pt=arg1;
}

void MainWindow::on_doubleSpinBox_3_valueChanged(double arg1)
{
    this->c->pt=arg1;
}

//Подключение и управление дополнительным потоком программы для Автообновления синусоиды

void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    QThread* thread = nullptr;
    task* tsk = nullptr;

    if (arg1 == 2)
    {
        thread = new QThread( );
        tsk = new task();

        thr = thread;
        dt = tsk;
        dt->stop=0;

        dt->grc = ui->spinBox_3->value();

        dt->moveToThread(thread);

        //Соединение сигналов со слотами для работы второго потока программы
        connect(thr, SIGNAL(started()), dt, SLOT(doWork()));
        connect(dt, SIGNAL(workFinished()), thr, SLOT(quit()));
        connect(dt, SIGNAL(timedraw()), this, SLOT(on_pushButton_clicked()));

        // Авто очистка памяти при завершении потока
        connect(dt, SIGNAL(workFinished()), dt, SLOT(deleteLater()));
        connect(thr, SIGNAL(finished()), thr, SLOT(deleteLater()));

        thread->start();
    }
    //Остановка потока с его последующим самозакрытием
    else
    {
        if (thr && thr->isRunning() == true)
        {
            dt->stop=1;
        }
    }
}
