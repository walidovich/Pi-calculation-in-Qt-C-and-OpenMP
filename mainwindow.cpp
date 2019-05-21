#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <omp.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->startCalculationBtn, SIGNAL(clicked()), this, SLOT(calculatePi()));
    connect(ui->resetBtn, SIGNAL(clicked()), this, SLOT(resetValues()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculatePi()
{
    // Gives the program control when requesting specific number of threads
    omp_set_dynamic(0);

    int num_threads= ui->numberCpuCoresLineEdit->text().toInt();
    int num_steps= ui->numberStepsLineEdit->text().toInt();
    double x=0.0;
    double sum = 0.0;

    // Setting the number of running threads
    omp_set_num_threads(num_threads);

    #pragma omp parallel for private(x) reduction(+:sum)
    for (int i=0; i<num_steps; i++)
    {
        x=(i+0.5)/(double)num_steps;
        sum = sum + 4.0/(1.0+x*x);
    }

    double pi=sum/(double)num_steps;
    QString result= QString::number(pi, 'g', 10);
    ui->piLabel->setText(result);
}

void MainWindow::resetValues()
{
    ui->numberCpuCoresLineEdit->setText("");
    ui->numberStepsLineEdit->setText("");
    ui->piLabel->setText("");
}
