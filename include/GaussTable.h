#pragma once

#include "config.h"
#include "grid.h"
#include <cmath>
#include <array>

using namespace std;
using namespace config;

struct ElemUniv;
struct element;

struct GaussTable2pt {
    static const array<double, 2> x;
    static const array<double, 2> w;

    static double integral1D_local(double (*f)(double));
    static double integral2D_local(double (*f)(double, double));

    static double integral1D_global(double (*f)(double), double x1, double x2);
    static double integral2D_global(double (*f)(double, double), ElemUniv d, element e);

    static array<array<double, 4>, 4> integral2D_H(element e);
};

struct GaussTable3pt {
    static const array<double, 3> x;
    static const array<double, 3> w;

    static double integral1D_local(double (*f)(double));
    static double integral2D_local(double (*f)(double, double));

    static double integral1D_global(double (*f)(double), double x1, double x2);
    static double integral2D_global(double (*f)(double, double), ElemUniv d, element e);
    
    static array<array<double, 4>, 4> integral2D_H(element e);
};

struct GaussTable4pt {
    static const array<double, 4> x;
    static const array<double, 4> w;

    static double integral1D_local(double (*f)(double));
    static double integral2D_local(double (*f)(double, double));

    static double integral1D_global(double (*f)(double), double x1, double x2);
    static double integral2D_global(double (*f)(double, double), ElemUniv d, element e);

    static array<array<double, 4>, 4> integral2D_H(element e);
};