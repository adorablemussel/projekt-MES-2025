#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::setValues(double SimulationTime,
                      double SimulationStepTime,
                      double Conductivity,
                      double Alfa,
                      double Tot,
                      double InitialTemp,
                      double Density,
                      double SpecificHeat,
                      int npc,
                      int dimension,
                      int nN,
                      int nE)
{
    ui->txtSimulationTime->setText(QString::number(SimulationTime));
    ui->txtSimulationStepTime->setText(QString::number(SimulationStepTime));
    ui->txtConductivity->setText(QString::number(Conductivity));
    ui->txtAlfa->setText(QString::number(Alfa));
    ui->txtTot->setText(QString::number(Tot));
    ui->txtInitialTemp->setText(QString::number(InitialTemp));
    ui->txtDensity->setText(QString::number(Density));
    ui->txtSpecificHeat->setText(QString::number(SpecificHeat));
    ui->txtNpc->setText(QString::number(npc));
    ui->txtDimension->setText(QString::number(dimension));
    ui->txtNn->setText(QString::number(nN));
    ui->txtNe->setText(QString::number(nE));
}

MainWindow::~MainWindow()
{
    delete ui;
}

