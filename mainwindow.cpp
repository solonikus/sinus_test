#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    scene = new QGraphicsScene(ui->graphicsView);
    QPen pen(Qt::gray);
    scene->addLine(-190, 0,190,0,pen);//x
    scene->addLine(0,-190,0,190,pen);//y
    scene->addText("0");

    QGraphicsTextItem * tm = new QGraphicsTextItem;
    tm->setPos(185,0);
    tm->setPlainText("t");
    scene->addItem(tm);

    ui->graphicsView->setScene(scene);

    a = new potok;
    b = new potok;
    c = new potok;
    init_potok(a, 3);
    init_potok(b, 1);
    init_potok(c, 1);
    ui->doubleSpinBox->setValue(3);
    ui->doubleSpinBox_2->setValue(1);
    ui->doubleSpinBox_3->setValue(1);
}

void MainWindow::init_scene()
{
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

void draw(MainWindow &main)
{
    double y;
    double y1;
    double xf;
    double xf1;
    double a;
    double b;
    double c;
    int px;
    int py;
    QPen pen(Qt::red);

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
    px = ((main.ui->graphicsView->width() / 2) - 10) / main.ui->spinBox_2->value();
    py =  ((main.ui->graphicsView->height() / 2) - 10) / int(b + a);
    main.ui->spinBox->setValue(int(b + a));

    for (double x=-185; x < 186; x++)
    {
        xf = x / px;
        xf1 = (x + 1) / px;
        y = (a + b * sin(c * xf)) * (-1);
        y1 = (a + b * sin(c * xf1)) * (-1);
//        double rad = 1;
//        scene->addEllipse(x-rad, (y * py)-rad, rad*2.0, rad*2.0, QPen(), QBrush(Qt::SolidPattern));
        main.scene->addLine(x,y * py,x+1,y1 * py,pen);
    }
    main.ui->graphicsView->setScene(main.scene);
}


void MainWindow::on_pushButton_clicked()
{
//    scene->clear();
//    init_scene();
    delete scene;
    scene = new QGraphicsScene(ui->graphicsView);
    init_scene();
    draw(*this);
}

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

void MainWindow::on_checkBox_4_stateChanged(int arg1)
{

}
