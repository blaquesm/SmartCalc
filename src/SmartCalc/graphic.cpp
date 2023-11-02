#include "graphic.h"
#include "ui_graphic.h"

Graphic::Graphic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graphic)
{
    ui->setupUi(this);

    h = 0.1;
    xBegin = -3;
    xEnd = 3 +h;

    ui->widget->xAxis->setRange(-4, 4);
    ui->widget->xAxis->setRange(0, 9);
}

Graphic::~Graphic()
{
    delete ui;
}
