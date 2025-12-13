#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setValues(double SimulationTime,
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
                   int nE);
    void setFile(char* inputPath);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
