#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_1_clicked()
{
    QString str = ui->label->text();
    if(str == "output"){
        str = "";
    }
    str.append("1");
    ui->label->setText(str);
}

void MainWindow::on_btn_2_clicked()
{
    QString str = ui->label->text();
    if(str == "output"){
        str = "";
    }
    str.append("2");
    ui->label->setText(str);
}

void MainWindow::on_btn_3_clicked()
{
    QString str = ui->label->text();
    if(str == "output"){
        str = "";
    }
    str.append("3");
    ui->label->setText(str);
}

void MainWindow::on_btn_4_clicked()
{
    QString str = ui->label->text();
    if(str == "output"){
        str = "";
    }
    str.append("4");
    ui->label->setText(str);
}

void MainWindow::on_btn_5_clicked()
{
    QString str = ui->label->text();
    if(str == "output"){
        str = "";
    }
    str.append("5");
    ui->label->setText(str);
}

void MainWindow::on_btn_6_clicked()
{
    QString str = ui->label->text();
    if(str == "output"){
        str = "";
    }
    str.append("6");
    ui->label->setText(str);
}

void MainWindow::on_btn_7_clicked()
{
    QString str = ui->label->text();
    if(str == "output"){
        str = "";
    }
    str.append("7");
    ui->label->setText(str);
}

void MainWindow::on_btn_8_clicked()
{
    QString str = ui->label->text();
    if(str == "output"){
        str = "";
    }
    str.append("8");
    ui->label->setText(str);
}

void MainWindow::on_btn_9_clicked()
{
    QString str = ui->label->text();
    if(str == "output"){
        str = "";
    }
    str.append("9");
    ui->label->setText(str);
}

void MainWindow::on_btn_0_clicked()
{
    QString str = ui->label->text();
    if(str == "output"){
        str = "";
    }
    str.append("0");
    ui->label->setText(str);
}

void MainWindow::on_btn_add_clicked()
{
    QString str = ui->label->text();
    if(str == "output"){
        str = "";
    }
    str.append("+");
    ui->label->setText(str);
}

void MainWindow::on_btn_sub_clicked()
{
    QString str = ui->label->text();
    if(str == "output"){
        str = "";
    }
    str.append("-");
    ui->label->setText(str);
}

void MainWindow::on_btn_mul_clicked()
{
    QString str = ui->label->text();
    if(str == "output"){
        str = "";
    }
    str.append("*");
    ui->label->setText(str);
}

void MainWindow::on_btn_div_clicked()
{
    QString str = ui->label->text();
    if(str == "output"){
        str = "";
    }
    str.append("/");
    ui->label->setText(str);
}

void MainWindow::on_btn_del_clicked()
{
    QString str = ui->label->text();
    if(str == "output"){
        str = "";
    }
    if(str != ""){
        str.chop(1);
    }
    ui->label->setText(str);
}

void MainWindow::on_btn_equal_clicked()
{
    QString str = ui->label->text();
    if(str == "output"){
        str = "";
    }
    str.append("=");
    ui->label->setText(str);
}
