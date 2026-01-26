#pragma once

#include "GaussTable.h"
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <algorithm>

static constexpr int D = 2;    // liczba wymiarów (1D = 1, 2D = 2, 3D = 3)
static constexpr int NPC = 9; // liczba punktow calkowania (dla 1D: 2, 3, 4, ...; dla 2D: 4, 9, 16, ...)

using namespace std;

struct node;
struct ElemUniv;
struct JMatrix;
struct element;
struct grid;
struct GlobalData;

struct node{
    int id;
    double x;
    double y;
    bool BC = false;
};

struct ElemUniv {
    array<array<double, 4>, NPC> N_KsiEta;
    array<array<double, 4>, NPC> dN_dKsi;
    array<array<double, 4>, NPC> dN_dEta;

    struct Surface {
        int npc1D = sqrt(NPC);
        vector<double> w;
        array<vector<double>, 4> N;
    };
    array<Surface, 4> surface;

    void calculateShapeFunctions();
    void calculateDerivatives();
    void calculateSurfaceFunctions();
    void print();
};

struct JMatrix {
    array<array<double, 2>, 2> J;
    array<array<double, 2>, 2> J1;
    double detJ;
};

struct HMatrix {
    array<array<double, 4>, 4> H_elem;
    array<array<double, 4>, 4> H_npc;
    array<double, 4> dN_dx;
    array<double, 4> dN_dy;
};

struct element{
    int id;
    array<node*, 4> nodes;
    array<JMatrix, NPC> Jacobian;
    array<HMatrix, NPC> H_local;
    array<array<double, 4>, 4> Hbc_local;
    array<double, 4> P_local;
    array<array<double, 4>, 4> C_local;

    void calculateJacobian(const ElemUniv& d);
    void calculateLocalHMatrix(const ElemUniv& d, const GlobalData& data);
    void calculateLocalHbcMatrix(const ElemUniv& d, const GlobalData& data);
    void calculateLocalPVector(const ElemUniv& d, const GlobalData& data);
    void calculateLocalCMatrix(const ElemUniv& d, const GlobalData& data);
    void print();
};

struct SystemOfEquation{
    vector<double> t{};
    vector<vector<double>> H_global{};
    vector<double> P_global{};
    vector<vector<double>> C_global{};

    vector<double> solveGauss(vector<vector<double>>& A, vector<double>& b);
    void solveSimulation(const GlobalData& data);
    void printSteps(int step, int totalSteps, double currentTime, const vector<double>& temperatures);
    void printTemeperatures(int step, double currentTime ,const vector<double>& temperatures);
};

struct grid{
    int nE;
    int nN;
    vector<element> elements;
    vector<node> nodes;

    void calculateGlobalHMatrix(SystemOfEquation& system);
    void calculateGlobalHbcMatrix(SystemOfEquation& system);
    void calculateGlobalPVector(SystemOfEquation& system);
    void calculateGlobalCMatrix(SystemOfEquation& system);
    void print();
    void printGlobalHMatrix(SystemOfEquation& system);
    void printGlobalPVector(SystemOfEquation& system);
    void printGlobalCMatrix(SystemOfEquation& system);
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
