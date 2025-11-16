#include "GaussTable.h"

using namespace std;

// Tabela Gaussa dla 2 punktów
const double GaussTable2pt::x[2] = {
    -sqrt(1.0/3.0),
     sqrt(1.0/3.0)
};
const double GaussTable2pt::w[2] = {
    1.0,
    1.0
};
    double GaussTable2pt::integral1D_local(double (*f)(double)){
        double sum = 0.0;
        sum += w[0] * f(x[0]);
        sum += w[1] * f(x[1]);
        return sum;
    }
    double GaussTable2pt::integral2D_local(double (*f)(double, double)){
        double sum = 0.0;
        sum += w[0]*w[0]*f(x[0],x[0]);
        sum += w[1]*w[0]*f(x[1],x[0]);
        sum += w[1]*w[1]*f(x[1],x[1]);
        sum += w[0]*w[1]*f(x[0],x[1]);
        return sum;
    }
    double GaussTable2pt::integral1D_global(double (*f)(double), double x1, double x2){
        // 0. tworzę sumę
        double sum = 0.0;

        // 1. liczę jakobian
        double detJ = (x2 - x1)/2;

        // 2. znajduję punkty całkowania x[0], x[1] dla układu globalnego za pomocą funkcji kształtu
        double xpc1_global = x1 * ((1 - x[0]) / 2) + x2 * ((1 + x[0]) / 2);
        double xpc2_global = x1 * ((1 - x[1]) / 2) + x2 * ((1 + x[1]) / 2);

        // 3. znajduję wagi dla dwóch punktów w[0], w[1]
        // double w1_global = w[0] * detJ;
        // double w2_global = w[1] * detJ;
        // robię to w sumowaniu

        // 4. policzyć wartość funkcji dla punktów globalnych całkowania
        double fxpc1_global = f(xpc1_global);
        double fxpc2_global = f(xpc2_global);

        // 5. liczymy całkę i dodajemy do sumy
        sum += fxpc1_global*w[0]*detJ + fxpc2_global*w[1]*detJ;

        return sum;
    }
    double GaussTable2pt::integral2D_global(double (*f)(double, double), ElemUniv d, element e){
        if (NPC != 4){
            cerr << "GaussTable2pt::integral2D_global: Ilosc punktow calkowania nie jest rowna 4" << endl;
            exit(EXIT_FAILURE);
        }
        else {
            double sum = 0.0;
            double xpc_global;
            double ypc_global;
            double w1;
            double w2;

            for (int i = 0; i < 4; i++){
                xpc_global = e.ID[0]->x * d.N_KsiEta[i][0] + e.ID[1]->x * d.N_KsiEta[i][1] + e.ID[2]->x * d.N_KsiEta[i][2] + e.ID[3]->x * d.N_KsiEta[i][3];
                ypc_global = e.ID[0]->y * d.N_KsiEta[i][0] + e.ID[1]->y * d.N_KsiEta[i][1] + e.ID[2]->y * d.N_KsiEta[i][2] + e.ID[3]->y * d.N_KsiEta[i][3];

                switch (i){
                    case 0:
                        w1 = w[0];
                        w2 = w[0];
                        break;
                    case 1:
                        w1 = w[1];
                        w2 = w[0];
                        break;
                    case 2:
                        w1 = w[1];
                        w2 = w[1];
                        break;
                    case 3:
                        w1 = w[0];
                        w2 = w[1];
                    default:
                        break;
                }

                sum += f(xpc_global, ypc_global) * e.jakobian[i].detJ * w1 * w2;
            }

            return sum;
        }
    };
    array<array<double, 4>, 4> GaussTable2pt::integral2D_H(element e){
        if (NPC != 4){
            cerr << "GaussTable2pt::integral2D_H: Ilosc punktow calkowania nie jest rowna 4" << endl;
            exit(EXIT_FAILURE);
        }
        else {
            double w1, w2;
            //tworzę macierz zerową
            array<array<double, 4>, 4> sum = {0,0,0,0,
                                            0,0,0,0,
                                            0,0,0,0,
                                            0,0,0,0};

            for (int i = 0; i < 4; i++){
                switch (i){
                    case 0:
                        w1 = w[0];
                        w2 = w[0];
                        break;
                    case 1:
                        w1 = w[1];
                        w2 = w[0];
                        break;
                    case 2:
                        w1 = w[1];
                        w2 = w[1];
                        break;
                    case 3:
                        w1 = w[0];
                        w2 = w[1];
                    default:
                        break;
                }

                for (int j = 0; j < 4; j++){
                    for (int k = 0; k < 4; k++){
                        sum[j][k] += e.macierzH[i].H[j][k] * w1 * w2;
                    }
                }
            }

            return sum;
        }
    };

// Tabela Gaussa dla 3 punktów
const double GaussTable3pt::x[3] = {
    -sqrt(3.0/5.0),
    0.0,
    sqrt(3.0/5.0)
};
const double GaussTable3pt::w[3] = {
    5.0/9.0,
    8.0/9.0,
    5.0/9.0
};
    double GaussTable3pt::integral1D_local(double (*f)(double)){
        double sum = 0.0;
        sum += w[0] * f(x[0]);
        sum += w[1] * f(x[1]);
        sum += w[2] * f(x[2]);
        return sum;
    }
    double GaussTable3pt::integral2D_local(double (*f)(double, double)){
        double sum = 0.0;
        // sum += w[0]*w[0]*f(x[0],x[0]);
        // sum += w[1]*w[0]*f(x[1],x[0]);
        // sum += w[2]*w[0]*f(x[2],x[0]);
        // sum += w[1]*w[0]*f(x[1],x[0]);
        // ...
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                sum += w[i]*w[j]*f(x[i],x[j]);
            }
        }
        return sum;
    }
    double GaussTable3pt::integral1D_global(double (*f)(double), double x1, double x2){
        // 0. tworzę sumę
        double sum = 0.0;

        // 1. liczę jakobian
        double detJ = (x2 - x1)/2;

        // 2. znajduję punkty całkowania x[0], x[1], x[2] dla układu globalnego za pomocą funkcji kształtu
        double xpc1_global = x1 * ((1 - x[0]) / 2) + x2 * ((1 + x[0]) / 2);
        double xpc2_global = x1 * ((1 - x[1]) / 2) + x2 * ((1 + x[1]) / 2);
        double xpc3_global = x1 * ((1 - x[2]) / 2) + x2 * ((1 + x[2]) / 2);

        // 3. znajduję wagi dla trzech punktów w[0], w[1], w[2]
        // robię to w sumowaniu

        // 4. policzyć wartość funkcji dla punktów globalnych całkowania
        double fxpc1_global = f(xpc1_global);
        double fxpc2_global = f(xpc2_global);
        double fxpc3_global = f(xpc3_global);

        // 5. liczymy całkę i dodajemy do sumy
        sum += fxpc1_global*w[0]*detJ + fxpc2_global*w[1]*detJ + fxpc3_global*w[2]*detJ;

        return sum;
    }
    double GaussTable3pt::integral2D_global(double (*f)(double, double), ElemUniv d, element e){
        if (NPC != 9){
            cerr << "GaussTable3pt::integral2D_global: Ilosc punktow calkowania nie jest rowna 9" << endl;
            exit(EXIT_FAILURE);
        }
        else {
            double sum = 0.0;
            double xpc_global;
            double ypc_global;
            double w1;
            double w2;

            for (int i = 0; i < 9; i++){
                xpc_global = e.ID[0]->x * d.N_KsiEta[i][0] + e.ID[1]->x * d.N_KsiEta[i][1] + e.ID[2]->x * d.N_KsiEta[i][2] + e.ID[3]->x * d.N_KsiEta[i][3];
                ypc_global = e.ID[0]->y * d.N_KsiEta[i][0] + e.ID[1]->y * d.N_KsiEta[i][1] + e.ID[2]->y * d.N_KsiEta[i][2] + e.ID[3]->y * d.N_KsiEta[i][3];

                switch (i){
                    case 0:
                        w1 = w[0];
                        w2 = w[0];
                        break;
                    case 1:
                        w1 = w[1];
                        w2 = w[0];
                        break;
                    case 2:
                        w1 = w[2];
                        w2 = w[0];
                        break;
                    case 3:
                        w1 = w[0];
                        w2 = w[1];
                        break;
                    case 4:
                        w1 = w[1];
                        w2 = w[1];
                        break;
                    case 5:
                        w1 = w[2];
                        w2 = w[1];
                        break;
                    case 6:
                        w1 = w[0];
                        w2 = w[2];
                        break;
                    case 7:
                        w1 = w[1];
                        w2 = w[2];
                        break;
                    case 8:
                        w1 = w[2];
                        w2 = w[2];
                        break;
                    default:
                        break;
                }

                sum += f(xpc_global, ypc_global) * e.jakobian[i].detJ * w1 * w2;
            }

            return sum;
        }
    }
    array<array<double, 4>, 4> GaussTable3pt::integral2D_H(element e){
        if (NPC != 9){
            cerr << "GaussTable3pt::integral2D_H: Ilosc punktow calkowania nie jest rowna 9" << endl;
            exit(EXIT_FAILURE);
        }
        else {
            double w1, w2;
            //tworzę macierz zerową
            array<array<double, 4>, 4> sum = {0,0,0,0,
                                            0,0,0,0,
                                            0,0,0,0,
                                            0,0,0,0};

            for (int i = 0; i < 9; i++){
                switch (i){
                    case 0:
                        w1 = w[0];
                        w2 = w[0];
                        break;
                    case 1:
                        w1 = w[1];
                        w2 = w[0];
                        break;
                    case 2:
                        w1 = w[2];
                        w2 = w[0];
                        break;
                    case 3:
                        w1 = w[0];
                        w2 = w[1];
                        break;
                    case 4:
                        w1 = w[1];
                        w2 = w[1];
                        break;
                    case 5:
                        w1 = w[2];
                        w2 = w[1];
                        break;
                    case 6:
                        w1 = w[0];
                        w2 = w[2];
                        break;
                    case 7:
                        w1 = w[1];
                        w2 = w[2];
                        break;
                    case 8:
                        w1 = w[2];
                        w2 = w[2];
                        break;
                    default:
                        break;
                }

                for (int j = 0; j < 4; j++){
                    for (int k = 0; k < 4; k++){
                        sum[j][k] += e.macierzH[i].H[j][k] * w1 * w2;
                    }
                }
            }

            return sum;
        }
    };
