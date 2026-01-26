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
                   int nN,
                   int nE,
                   int npc);
    void setFile(char* inputPath);
    void loadAndRun(const QString& path);
    ~MainWindow();

private slots:
    void on_btnTest1_4_4_clicked();
    void on_btnTest2_4_4_MixGrid_clicked();
    void on_btnTest3_31_31_kwadrat_clicked();
    void on_btnWlasna_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
