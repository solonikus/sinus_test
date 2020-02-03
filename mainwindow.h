#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QThread>
#include <cmath>
#include "task.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct potok
{
    double pt;
    bool enable;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init_scene();

    friend void draw(MainWindow &main);
    MainWindow* getmw(){return this;}
private slots:
    void on_pushButton_clicked();

    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_3_clicked();

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_doubleSpinBox_3_valueChanged(double arg1);

    void on_checkBox_4_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    potok *a;
    potok *b;
    potok *c;
    bool onl;
    QThread *thr;
    task *dt;
};

#endif // MAINWINDOW_H
