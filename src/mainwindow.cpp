#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simulation.h"

#include <QDir>
#include <QString>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>


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
                      int nN,
                      int nE,
                      int npc)
{
    ui->txtSimulationTime->setText(QString::number(SimulationTime));
    ui->txtSimulationStepTime->setText(QString::number(SimulationStepTime));
    ui->txtConductivity->setText(QString::number(Conductivity));
    ui->txtAlfa->setText(QString::number(Alfa));
    ui->txtTot->setText(QString::number(Tot));
    ui->txtInitialTemp->setText(QString::number(InitialTemp));
    ui->txtDensity->setText(QString::number(Density));
    ui->txtSpecificHeat->setText(QString::number(SpecificHeat));
    ui->txtNn->setText(QString::number(nN));
    ui->txtNe->setText(QString::number(nE));
    ui->txtNpc->setText(QString::number(npc));
}

void MainWindow::setFile(char *inputPath){
    QString path = QString(inputPath);
    const QString base = QFileInfo(path).fileName();

    ui->btnTest1_4_4->setStyleSheet("");
    ui->btnTest2_4_4_MixGrid->setStyleSheet("");
    ui->btnTest3_31_31_kwadrat->setStyleSheet("");
    ui->btnWlasna->setStyleSheet("");

    if (path == "grids/Test1_4_4.txt" || base == "Test1_4_4.txt") {
        ui->btnTest1_4_4->setStyleSheet("background-color: green; color: white;");
    }
    else if (path == "grids/Test2_4_4_MixGrid.txt" || base == "Test2_4_4_MixGrid.txt") {
        ui->btnTest2_4_4_MixGrid->setStyleSheet("background-color: green; color: white;");
    }
    else if (path == "grids/Test3_31_31_kwadrat.txt" || base == "Test3_31_31_kwadrat.txt") {
        ui->btnTest3_31_31_kwadrat->setStyleSheet("background-color: green; color: white;");
    }
    else{
        ui->btnWlasna->setStyleSheet("background-color: green; color: white;");
    }
}

void MainWindow::loadAndRun(const QString& path) {
    grid mesh;
    GlobalData globalData;

    bool success = runSimulation(path.toStdString(), globalData, mesh, DEBUG_MODE);
    if (!success) {
        QMessageBox::critical(this, "Blad", "Nie udalo sie wczytac pliku: " + path);
        return;
    }

    setValues(globalData.SimulationTime,
              globalData.SimulationStepTime,
              globalData.Conductivity,
              globalData.Alfa,
              globalData.Tot,
              globalData.InitialTemp,
              globalData.Density,
              globalData.SpecificHeat,
              globalData.nN,
              globalData.nE,
              globalData.npc);
    setFile(path.toStdString().data());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnTest1_4_4_clicked()
{
    loadAndRun("grids/Test1_4_4.txt");
}
void MainWindow::on_btnTest2_4_4_MixGrid_clicked()
{
    loadAndRun("grids/Test2_4_4_MixGrid.txt");
}
void MainWindow::on_btnTest3_31_31_kwadrat_clicked()
{
    loadAndRun("grids/Test3_31_31_kwadrat.txt");
}
void MainWindow::on_btnWlasna_clicked()
{
    const QString startDir = QCoreApplication::applicationDirPath();
    const QString path = QFileDialog::getOpenFileName(this, "Wybierz plik z siatka", startDir, "Pliki tekstowe (*.txt);;Wszystkie pliki (*)");
    if (!path.isEmpty()) {
        loadAndRun(path);
    }
}
