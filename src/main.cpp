#include "mainwindow.h"

#include "readFromFile.h"
#include "grid.h"
#include "GaussTable.h"
#include "functions.h"

#include <QApplication>

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    // ((zmiana punktów całkowania i wymiarów w grid.h))
    grid mesh;
    GlobalData globalData;

    const char* inputPath = "grids/Test2_4_4_MixGrid.txt"; // trzeba sprawdzić czy jest w build/.../debug
    if (!readFromFile(inputPath, globalData, mesh)) {
        std::cerr << "Failed to read input file: " << inputPath << std::endl;
        return 1;
    }


    // lab 1.
    globalData.print();
    mesh.print();

    /*
    // lab 2.
    cout << "Calkowanie metoda Gaussa w 1D, 2 punkty: " << GaussTable2pt::integral1D_local(gaussFunction1) << endl;
    cout << "Calkowanie metoda Gaussa w 1D, 3 punkty: " << GaussTable3pt::integral1D_local(gaussFunction1) << endl;
    cout << "Calkowanie metoda Gaussa w 2D, 2 punkty: " << GaussTable2pt::integral2D_local(gaussFunction2) << endl;
    cout << "Calkowanie metoda Gaussa w 2D, 3 punkty: " << GaussTable3pt::integral2D_local(gaussFunction2) << endl;
    */

    // lab 3. + lab 4.
    ElemUniv shapeFuns;
    shapeFuns.calculateShapeFunctions();
    shapeFuns.calculateDerivatives();
    shapeFuns.print();

    for (int i = 0; i < 9; i++){
        mesh.element[i].calculateJakobian(shapeFuns);
        mesh.element[i].calculateHMatrix(shapeFuns, globalData);
        mesh.element[i].print(i+1);

        cout << "Calka powierzchniowa: ";
        if (NPC == 4){
            cout << GaussTable2pt::integral2D_global(gaussFunction2, shapeFuns, mesh.element[i]) << endl;
            cout << endl;
        }
        else if (NPC == 9){
            cout << GaussTable3pt::integral2D_global(gaussFunction2, shapeFuns, mesh.element[i]) << endl;
            cout << endl;
        }
        else {cout << "Bledna liczba punktow calkowania dla liczenia calki\n";}

        cout << "Macierz H calkowana powierzchniowo:\n";
        if (NPC == 4){
            array<array<double, 4>, 4> H_global = GaussTable2pt::integral2D_H(mesh.element[i]);
            for (int r = 0; r < 4; r++){
                for (int c = 0; c < 4; c++){
                    cout << H_global[r][c] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
        else if (NPC == 9){
            array<array<double, 4>, 4> H_global = GaussTable3pt::integral2D_H(mesh.element[i]);
            for (int r = 0; r < 4; r++){
                for (int c = 0; c < 4; c++){
                    cout << H_global[r][c] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
        else {cout << "Bledna liczba punktow calkowania dla liczenia macierzy H\n";}
    }


    // Qt section
    QApplication a(argc, argv);
    MainWindow w;
    w.setValues(globalData.SimulationTime, globalData.SimulationStepTime, globalData.Conductivity, globalData.Alfa, globalData.Tot, globalData.InitialTemp, globalData.Density, globalData.SpecificHeat, globalData.npc, globalData.dimension, globalData.nN, globalData.nE);
    w.show();

    return a.exec();
}
