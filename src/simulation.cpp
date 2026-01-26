#include "simulation.h"
#include <array>
#include <vector>

bool runSimulation(const std::string& inputPath, GlobalData& globalData, grid& mesh, bool debug){
    if (!readFromFile(inputPath, globalData, mesh)) {
        std::cerr << "Nie udalo sie wczytac pliku: " << inputPath << std::endl;
        return false;
    }

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

    mesh.calculateGlobalHMatrix(system);
    mesh.calculateGlobalHbcMatrix(system);
    mesh.calculateGlobalPVector(system);
    mesh.calculateGlobalCMatrix(system);

    if (debug){
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
    }

    system.solveSimulation(globalData);
    return true;
}