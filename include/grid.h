#pragma once

#include "GaussTable.h"
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cmath>

#define D 2   // liczba wymiarów (1D = 1, 2D = 2, 3D = 3)
#define NPC 9 // liczba punktow calkowania (dla 1D: 2, 3, 4, ...; dla 2D: 4, 9, 16, ...)

using namespace std; 

struct node;
struct ElemUniv;
struct Jakobian;
struct element;
struct grid;
struct GlobalData;

struct node{
    int id;
    double x;
    double y;
};

struct ElemUniv {
    array<array<double, 4>, NPC> N_KsiEta;      // funkcje kształtu, od ksi i eta
    array<array<double, 4>, NPC> dN_dKsi;       // pochodne funkcji ksztaltu N, po ksi
    array<array<double, 4>, NPC> dN_dEta;       // pochodne funkcji ksztaltu N, po eta

    void calculateShapeFunctions();
    void calculateDerivatives();  // liczenie całek do Jakobianu (dla wszystkich punktów)
    void print();
};

struct Jakobian {
    array<array<double, 2>, 2> J;  // macierz jakobianu
    array<array<double, 2>, 2> J1; // macierz odwrotna jakobianu
    double detJ;     // wyznacznik jakobianu
};

struct HMatrix {
    array<array<double, 4>, 4> H_elem; // macierz H dla elementu (suma po punktach calkowania)
    array<array<double, 4>, 4> H_npc;      // macierz H dla danego punktu calkowania
    array<double, 4> dN_dx;
    array<double, 4> dN_dy;
};

struct element{
    int id;
    array<node*, 4> nodes;
    array<Jakobian, NPC> Jacobian;
    array<HMatrix, NPC> H_local;

    void calculateJacobian(ElemUniv d); // liczy jakobiany dla wszystkich punktów całkowania
    void calculateHMatrix(ElemUniv d, GlobalData data);  // liczy macierze H dla wszystkich punktów całkowania
    void print();      // można podać id do wyświetlania, albo nie
};

struct grid{
    int nE;
    int nN;
    vector<element> elements;
    vector<node> nodes;

    vector<vector<double>> H_global{}; // globalna macierz H
    
    void calculateGlobalHMatrix(); // agregacja
    void print();
    void printGlobalHMatrix();
};

struct GlobalData {
    double SimulationTime;
    double SimulationStepTime;
    double Conductivity;
    double Alfa;
    double Tot;
    double InitialTemp;
    double Density;
    double SpecificHeat;
    int npc = NPC;
    int dimension = D;
    int nN;
    int nE;

    void print();
};
