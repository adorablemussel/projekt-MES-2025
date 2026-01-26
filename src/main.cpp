#include "readFromFile.h"
#include "grid.h"
#include "GaussTable.h"
#include "functions.h"

#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    // lab 1.
    // ((zmiana punktów całkowania i wymiarów w grid.h))
    grid mesh;
    GlobalData globalData;

    char* inputPath = "grids/Test3_31_31_kwadrat.txt"; // trzeba sprawdzić czy jest w build/.../debug
    if (!readFromFile(inputPath, globalData, mesh)) {
        std::cerr << "Failed to read input file: " << inputPath << std::endl;
        return 1;
    }


    
    // // lab 2.
    // cout << "Calkowanie metoda Gaussa w 1D, 2 punkty: " << GaussTable2pt::integral1D_local(gaussFunction1) << endl;
    // cout << "Calkowanie metoda Gaussa w 1D, 3 punkty: " << GaussTable3pt::integral1D_local(gaussFunction1) << endl;
    // cout << "Calkowanie metoda Gaussa w 2D, 2 punkty: " << GaussTable2pt::integral2D_local(gaussFunction2) << endl;
    // cout << "Calkowanie metoda Gaussa w 2D, 3 punkty: " << GaussTable3pt::integral2D_local(gaussFunction2) << endl;
    

    // lab 3. + lab 4.
    ElemUniv shapeFuns;
    shapeFuns.calculateShapeFunctions();
    shapeFuns.calculateDerivatives();
    shapeFuns.calculateSurfaceFunctions();

    for (int i = 0; i < mesh.nE; i++) {
        mesh.elements[i].calculateJacobian(shapeFuns);
        mesh.elements[i].calculateLocalHMatrix(shapeFuns, globalData);
        mesh.elements[i].calculateLocalHbcMatrix(shapeFuns, globalData);
        mesh.elements[i].calculateLocalPVector(shapeFuns, globalData);
        mesh.elements[i].calculateLocalCMatrix(shapeFuns, globalData);
    }

    SystemOfEquation system;

    // lab 5.
    mesh.calculateGlobalHMatrix(system);

    // lab 6.
    mesh.calculateGlobalHbcMatrix(system);

    // lab 7.
    mesh.calculateGlobalPVector(system);

    // lab 8.
    mesh.calculateGlobalCMatrix(system);

/*
    globalData.print();
    mesh.print();
    shapeFuns.print();

    for (int j = 0; j < mesh.nE; j++){
        mesh.elements[j].print();

        cout << "Calka powierzchniowa: ";
        if (NPC == 4){
            cout << GaussTable2pt::integral2D_global(gaussFunction2, shapeFuns, mesh.elements[j]) << endl;
            cout << endl;
        }
        else if (NPC == 9){
            cout << GaussTable3pt::integral2D_global(gaussFunction2, shapeFuns, mesh.elements[j]) << endl;
            cout << endl;
        }
        else if (NPC == 16){
            cout << GaussTable4pt::integral2D_global(gaussFunction2, shapeFuns, mesh.elements[j]) << endl;
            cout << endl;
        }
        else {cout << "Bledna liczba punktow calkowania dla liczenia calki\n";}

        cout << "Macierz H elementu calkowana powierzchniowo:\n";
        {
            const array<array<double, 4>, 4> &H_elem = mesh.elements[j].H_local[0].H_elem;
            for (int r = 0; r < 4; r++){
                for (int c = 0; c < 4; c++){
                    cout << H_elem[r][c] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }

    mesh.printGlobalHMatrix(system);
    mesh.printGlobalPVector(system);
    mesh.printGlobalCMatrix(system);
*/
    system.solveSimulation(globalData);
    


    // Qt section
    std::cout << std::flush;
    QApplication a(argc, argv);
    MainWindow w;
    w.setValues(globalData.SimulationTime, globalData.SimulationStepTime, globalData.Conductivity, globalData.Alfa, globalData.Tot, globalData.InitialTemp, globalData.Density, globalData.SpecificHeat, globalData.npc, globalData.dimension, globalData.nN, globalData.nE);
    w.setFile(inputPath);
    w.show();

    return a.exec();
    //return 0;
}
