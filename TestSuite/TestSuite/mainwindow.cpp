#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Test Suite");

    angular_vel_str = "0 m/s";
    ui->angular_vel_label->setText(angular_vel_str.c_str());

    x +=1;

    connect(ui->pushButton, &QPushButton::clicked, this, [this]() {
        counter ++;
        angular_vel_str = std::to_string(counter) + " /s";
        //ui->angular_vel_label->setText(std::string() counter+ " /s");
        ui->angular_vel_label->setText( angular_vel_str.c_str());

    });

    connect(ui->pushButton_2, &QPushButton::clicked, this, [this]() {
        if(counter<=0)
            return;
        counter --;
        angular_vel_str = std::to_string(counter) + " /s";
        //ui->angular_vel_label->setText(std::string() counter+ " /s");
        ui->angular_vel_label->setText( angular_vel_str.c_str());

    });


}

MainWindow::~MainWindow()
{
    delete ui;
}
