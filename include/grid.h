#pragma once

#include "GaussTable.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#define D 2   // liczba wymiarów (1D = 1, 2D = 2, 3D = 3)
#define NPC 4 // liczba punktow calkowania (dla 1D: 2, 3, 4, ...; dla 2D: 4, 9, 16, ...)

using namespace std; 

struct node;
struct ElemUniv;
struct Jakobian;
struct element;
struct grid;
struct GlobalData;

struct node{
    double x;
    double y;
};

struct ElemUniv {
    double N_KsiEta[NPC][4];      // funkcje kształtu, od ksi i eta
    double dN_dKsi[NPC][4];       // pochodne funkcji ksztaltu N, po ksi
    double dN_dEta[NPC][4];       // pochodne funkcji ksztaltu N, po eta

    void calculateShapeFunctions();
    void calculateDerivatives();  // liczenie całek do Jakobianu (dla wszystkich punktów)
    void print();
};

struct Jakobian {
    double J[2][2];  // macierz jakobianu
    double J1[2][2]; // macierz odwrotna jakobianu
    double detJ;     // wyznacznik jakobianu
};

struct element{
    node* ID[4];
    Jakobian jakobian[NPC];

    void calculateJakobian(ElemUniv d); // liczy jakobiany dla wszystkich punktów całkowania
    void print(int elementID = 0);      // można podać id do wyświetlania, albo nie
};

struct grid{
    int nE;
    int nN;
    vector<element> element;
    vector<node> node;

    void print();
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
