#pragma once

#include "grid.h"
#include <cmath>
#include <array>

using namespace std;

// forward deklaracje
struct ElemUniv;
struct element;

struct GaussTable2pt {
    static const double x[2];
    static const double w[2];

    static double integral1D_local(double (*f)(double));
    static double integral2D_local(double (*f)(double, double));

    static double integral1D_global(double (*f)(double), double x1, double x2);
    static double integral2D_global(double (*f)(double, double), ElemUniv d, element e);
    static array<array<double, 4>, 4> integral2D_H(element e);
};

struct GaussTable3pt {
    static const double x[3];
    static const double w[3];

    static double integral1D_local(double (*f)(double));
    static double integral2D_local(double (*f)(double, double));

    static double integral1D_global(double (*f)(double), double x1, double x2);
    static double integral2D_global(double (*f)(double, double), ElemUniv d, element e);
    static array<array<double, 4>, 4> integral2D_H(element e);
};