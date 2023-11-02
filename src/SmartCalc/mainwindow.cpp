#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <graphic.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(x()));

    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(operators()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(operators()));
    connect(ui->pushButton_dilenie, SIGNAL(clicked()), this, SLOT(operators()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operators()));
    connect(ui->pushButton_pov, SIGNAL(clicked()), this, SLOT(operators()));
    connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(operators()));

    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));

    connect(ui->pushButton_drop, SIGNAL(clicked()), this, SLOT(drop()));

    connect(ui->pushButton_skob, SIGNAL(clicked()), this, SLOT(skob()));

    connect(ui->pushButton_unar, SIGNAL(clicked()), this, SLOT(unar()));

    connect(ui->pushButton_clean, SIGNAL(clicked()), this, SLOT(clean()));
    connect(ui->pushButton_clean_2, SIGNAL(clicked()), this, SLOT(clean()));

    connect(ui->pushButton_eq, SIGNAL(clicked()), this, SLOT(eq()));

    connect(ui->pushButton_graphic, SIGNAL(clicked()), this, SLOT(graphic()));





         //connect(ui->pushButton_eq, SIGNAL(clicked()), this, SLOT(operators()));
    //connect(ui->pushButton_skob, SIGNAL(clicked()), this, SLOT(operators()));
    //connect(ui->pushButton_unar, SIGNAL(clicked()), this, SLOT(operators()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
bool MainWindow::IsOperator(QChar symbol){
    return(symbol == '+' || symbol == '-' || symbol == '*'
           || symbol == '/' || symbol == '^' || symbol == 'd');
}

int MainWindow::FirstDigit(QString string_digit, int id_x)
{
    bool stop = true;
    while(id_x >= 0 && stop ) {
        if(string_digit.at(id_x).isDigit() || string_digit.at(id_x) == '.' ){

            id_x--;
        }
        else {
              stop = false;
        }
    }
    return id_x;
}
void MainWindow::operators()
{
    QString text;
     QPushButton *button = (QPushButton*)sender();
     if(ui->lineEdit_result->hasFocus()){
         text =  ui->lineEdit_result->text();
        if(!text.isEmpty() && text.back() != '(')
        {
            if(text == "ERROR"){
                text.clear();
            }
            else if(IsOperator(text.back())){
                if(text.back() == 'd'){
                    text.chop(3);
                }
                else
                    text.chop(1);
            }
            text += button->text();
            ui->lineEdit_result->setText(text);
        }
  }
}

void MainWindow::functions()
{
    QString text;
    QPushButton *button = (QPushButton*)sender();
    if(ui->lineEdit_result->hasFocus()){
        text =  ui->lineEdit_result->text();
        if(text == "ERROR"){
            text.clear();
        }
        else if(!text.isEmpty() && (text.endsWith(')') || text.endsWith('X') || text.endsWith('.') || text.back().isDigit())){
            text += "*";
        }
        text += button->text() + "(";
        ui->lineEdit_result->setText(text);
  }
}

void MainWindow::drop()
{
    QString text;
    int curent_char = 0;
     text =  ui->lineEdit_result->hasFocus() ? ui->lineEdit_result->text() : ui->lineEdit_2->text();
     if(text == "ERROR")
         text.clear();
     if(text.isEmpty() || (!text.isEmpty() && (text.back() == '(' || IsOperator(text.back())))){
         text += "0.";
     }
     else if(!text.isEmpty() && text.back() == ')'){
         text += "*0.";
     }
     else if (!text.isEmpty() && text.back().isDigit()){
         curent_char = 0;
         for(int i = text.length() -1; i >= 0 ; i--){
             if(!text.at(i).isDigit() && text.at(i) != QChar('.'))
                 curent_char = i;
         }
         if(!text.right(curent_char - 1).contains(".")){
             text += ".";
         }
     }
     if (ui->lineEdit_result->hasFocus()) {
         ui->lineEdit_result->setText(text);
     } else{
         ui->lineEdit_2->setText(text);
     }
}

void MainWindow::skob()
{
    QString text;
    if(ui->lineEdit_result->hasFocus()){
         text =  ui->lineEdit_result->text();
         if(text == "ERROR")
             text.clear();
         if(text.isEmpty()){
             text += '(';
         }
         else if(text.count('(') - text.count(')') == 0){
             if(!IsOperator(text.back())){
                 text += '*';
             }
              text += "(";
         }
         else {
             if(!IsOperator(text.back()) && text.back() != '('){
                 text += ')';
             }
             else
                 text += '(';
         }
         ui->lineEdit_result->setText(text);
    }
}

void MainWindow::unar()
{
    QString text = ui->lineEdit_result->text();
       int last_digit_index{};

       if(ui->lineEdit_result->hasFocus()){
           text = ui->lineEdit_result->text();
           }
       else if(ui->lineEdit_2->hasFocus()){
            text = ui->lineEdit_2->text();
       }
       if (text == "error" || text == "inf" || text == "nan") {
          text .clear();
       }
       if (text.endsWith("(-")) {
          text.chop(2);
       }
       else if (text.endsWith("x")) {
           text.chop(1);
           text  += "(-x)";
       }
       else if (text.endsWith("(-x)")) {
           text.chop(4);
           text += "x";
        }
       else if (text.isEmpty() || (!text.isEmpty() && IsOperator(text.back().toLatin1())) || text.endsWith(")") || text.endsWith("(")) {
           if (text.endsWith(")")){
               text += "*";
           }
           text += "(-";
       }
       else if (!text.isEmpty() && (text.back().isDigit() || text.back() == '.')) {
           last_digit_index = FirstDigit(text, text.length() - 1);
           if (last_digit_index == -1 || !(text.at(last_digit_index ) == '-' &&
                                          text.at(last_digit_index - 1) == '(')) {
               text.insert(last_digit_index + 1, "(-");
           }
           else {
               text.remove(last_digit_index - 1, 2);
           }
       }
       if (ui->lineEdit_result->hasFocus()) {
           ui->lineEdit_result->setText(text);
       } else{
           ui->lineEdit_2->setText(text);
       }
}

void MainWindow::clean()
{
    QString text;
    QPushButton *button = (QPushButton*)sender();
    if(ui->lineEdit_result->hasFocus()){
        text = ui->lineEdit_result->text();
        }
    else if(ui->lineEdit_2->hasFocus()){
         text = ui->lineEdit_2->text();
    }
    if(button->text() == "AC") {
        text.clear();
    }
    else
        if(!text.isEmpty() && ((text.back() == '(' && text.at(text.length() - 2).isLetter()) || text.endsWith("mod"))) {
            text.chop(1);
            int i = text.length() - 1;
            while(i >= 0 && text.at(i).isLetter()){
                text.chop(1);
                i--;
            }
        }
        else {
            text.chop(1);
        }
    if(ui->lineEdit_result->hasFocus()){
       ui->lineEdit_result->setText(text);
        }
    else if(ui->lineEdit_2->hasFocus()){
        ui->lineEdit_2->setText(text);
    }

}

void MainWindow::on_pushButton_clicked()
{
    QString text;
    QPushButton *button = (QPushButton*)sender();
    text =  ui->lineEdit_result->hasFocus() ? ui->lineEdit_result->text() : ui->lineEdit_2->text();
    if(text == "ERROR"){
        text.clear();
    }
    else if(text.endsWith(')') || text.endsWith('X')){
        text += "*";
    }
    text += button->text();
    if (ui->lineEdit_result->hasFocus()) {
        ui->lineEdit_result->setText(text);
    } else{
        ui->lineEdit_2->setText(text);
    }
}

void MainWindow::x() {
  QString text;

  if (ui->lineEdit_result->hasFocus()) {
    text = ui->lineEdit_result->text();
    if (text == "error" || text == "nan"  || text == "inf") {
        text.clear();
    }
    if (!text.isEmpty() && !IsOperator(text.back())) {
        text += "*";
    }
    text += "X";
    ui->lineEdit_result->setText(text);
  }
}

void MainWindow::eq() {
  QString text;
//  if (ui->result->hasFocus()) {
//  text = ui->lineEdit_result->text();
//  if (text == "error" || text == "nan") text = "0";
//  ui->lineEdit_2->setText(text);
//  text.replace("mod", "%");
//  std::string str_string;
//  str_string = text.toStdString();
//  const char *str = str_string.c_str();
//  long double result_d;

//  if (s21_smart_calc(str, &result_d, ui->//lineEdit_3->text().toDouble()) == 0 &&
//      isnan(result_d) == 0 && isinf(result_d) == 0 && text.length() < 256)
//    ui->lineEdit_result->setText(QString::number(result_d, 'g', 15));
//  else
//    ui->lineEdit_result->setText("error");
  //  //}
}

void MainWindow::graphic()
{
    graph_q.show();
    //connect(this, &MainWindow::signal, graph_q, &Graphic::slot);

}

