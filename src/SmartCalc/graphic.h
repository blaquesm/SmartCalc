#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QDialog>
#include <QVector>

namespace Ui {
class Graphic;
}

class Graphic : public QDialog
{
    Q_OBJECT

public:
    explicit Graphic(QWidget *parent = nullptr);
    ~Graphic();

private:
    Ui::Graphic *ui;
    double xBegin, xEnd, h, X;
    int N;

    QVector<double> x,y;
};

#endif // GRAPHIC_H
