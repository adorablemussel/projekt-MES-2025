#include "GaussTable.h"

using namespace std;

//Tabela Gaussa dla 2 punktów
const array<double, 2> GaussTable2pt::x = {
    -sqrt(1.0/3.0),
     sqrt(1.0/3.0)
};
const array<double, 2> GaussTable2pt::w = {
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
        double sum = 0.0;
        double detJ = (x2 - x1)/2;

        double xpc1_global = x1 * ((1 - x[0]) / 2) + x2 * ((1 + x[0]) / 2);
        double xpc2_global = x1 * ((1 - x[1]) / 2) + x2 * ((1 + x[1]) / 2);

        double fxpc1_global = f(xpc1_global);
        double fxpc2_global = f(xpc2_global);

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
                xpc_global = e.nodes[0]->x * d.N_KsiEta[i][0] + e.nodes[1]->x * d.N_KsiEta[i][1] + e.nodes[2]->x * d.N_KsiEta[i][2] + e.nodes[3]->x * d.N_KsiEta[i][3];
                ypc_global = e.nodes[0]->y * d.N_KsiEta[i][0] + e.nodes[1]->y * d.N_KsiEta[i][1] + e.nodes[2]->y * d.N_KsiEta[i][2] + e.nodes[3]->y * d.N_KsiEta[i][3];

                switch (i){
                    case 0: w1 = w[0]; w2 = w[0]; break;
                    case 1: w1 = w[1]; w2 = w[0]; break;
                    case 2: w1 = w[1]; w2 = w[1]; break;
                    case 3: w1 = w[0]; w2 = w[1]; break;
                    default: break;
                }

                sum += f(xpc_global, ypc_global) * e.Jacobian[i].detJ * w1 * w2;
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
            array<array<double, 4>, 4> sum = { 0 };

            for (int i = 0; i < 4; i++){
                switch (i){
                    case 0: w1 = w[0]; w2 = w[0]; break;
                    case 1: w1 = w[1]; w2 = w[0]; break;
                    case 2: w1 = w[1]; w2 = w[1]; break;
                    case 3: w1 = w[0]; w2 = w[1]; break;
                    default: break;
                }

                for (int j = 0; j < 4; j++){
                    for (int k = 0; k < 4; k++){
                        sum[j][k] += e.H_local[i].H_npc[j][k] * w1 * w2;
                    }
                }
            }

            return sum;
        }
    };

//Tabela Gaussa dla 3 punktów
const array<double, 3> GaussTable3pt::x = {
    -sqrt(3.0/5.0),
    0.0,
    sqrt(3.0/5.0)
};
const array<double, 3> GaussTable3pt::w = {
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

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                sum += w[i]*w[j]*f(x[i],x[j]);
            }
        }
        return sum;
    }
    double GaussTable3pt::integral1D_global(double (*f)(double), double x1, double x2){
        double sum = 0.0;

        double detJ = (x2 - x1)/2;

        double xpc1_global = x1 * ((1 - x[0]) / 2) + x2 * ((1 + x[0]) / 2);
        double xpc2_global = x1 * ((1 - x[1]) / 2) + x2 * ((1 + x[1]) / 2);
        double xpc3_global = x1 * ((1 - x[2]) / 2) + x2 * ((1 + x[2]) / 2);

        double fxpc1_global = f(xpc1_global);
        double fxpc2_global = f(xpc2_global);
        double fxpc3_global = f(xpc3_global);

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
                xpc_global = e.nodes[0]->x * d.N_KsiEta[i][0] + e.nodes[1]->x * d.N_KsiEta[i][1] + e.nodes[2]->x * d.N_KsiEta[i][2] + e.nodes[3]->x * d.N_KsiEta[i][3];
                ypc_global = e.nodes[0]->y * d.N_KsiEta[i][0] + e.nodes[1]->y * d.N_KsiEta[i][1] + e.nodes[2]->y * d.N_KsiEta[i][2] + e.nodes[3]->y * d.N_KsiEta[i][3];

                switch (i){
                    case 0: w1 = w[0]; w2 = w[0]; break;
                    case 1: w1 = w[1]; w2 = w[0]; break;
                    case 2: w1 = w[2]; w2 = w[0]; break;
                    case 3: w1 = w[0]; w2 = w[1]; break;
                    case 4: w1 = w[1]; w2 = w[1]; break;
                    case 5: w1 = w[2]; w2 = w[1]; break;
                    case 6: w1 = w[0]; w2 = w[2]; break;
                    case 7: w1 = w[1]; w2 = w[2]; break;
                    case 8: w1 = w[2]; w2 = w[2]; break;
                    default: break; 
                }

                sum += f(xpc_global, ypc_global) * e.Jacobian[i].detJ * w1 * w2;
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
            array<array<double, 4>, 4> sum = { 0 };

            for (int i = 0; i < 9; i++){
                switch (i){
                    case 0: w1 = w[0]; w2 = w[0]; break;
                    case 1: w1 = w[1]; w2 = w[0]; break;
                    case 2: w1 = w[2]; w2 = w[0]; break;
                    case 3: w1 = w[0]; w2 = w[1]; break;
                    case 4: w1 = w[1]; w2 = w[1]; break;
                    case 5: w1 = w[2]; w2 = w[1]; break;
                    case 6: w1 = w[0]; w2 = w[2]; break;
                    case 7: w1 = w[1]; w2 = w[2]; break;
                    case 8: w1 = w[2]; w2 = w[2]; break;
                    default: break;
                }

                for (int j = 0; j < 4; j++){
                    for (int k = 0; k < 4; k++){
                        sum[j][k] += e.H_local[i].H_npc[j][k] * w1 * w2;
                    }
                }
            }

            return sum;
        }
    };

//Tabela Gaussa dla 4 punktów
const array<double, 4> GaussTable4pt::x = {
    -sqrt((3.0/7.0) + (2.0/7.0) * sqrt(6.0 / 5.0)),
    -sqrt((3.0/7.0) - (2.0/7.0) * sqrt(6.0 / 5.0)),
     sqrt((3.0/7.0) - (2.0/7.0) * sqrt(6.0 / 5.0)),
     sqrt((3.0/7.0) + (2.0/7.0) * sqrt(6.0 / 5.0))
};
const array<double, 4> GaussTable4pt::w = {
    (18.0 - sqrt(30.0)) / 36.0,
    (18.0 + sqrt(30.0)) / 36.0,
    (18.0 + sqrt(30.0)) / 36.0,
    (18.0 - sqrt(30.0)) / 36.0
};
    double GaussTable4pt::integral1D_local(double (*f)(double)) {
        double sum = 0.0;
        for (int i = 0; i < 4; i++) sum += w[i] * f(x[i]);
        return sum;
    }
    double GaussTable4pt::integral2D_local(double (*f)(double, double)) {
        double sum = 0.0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                sum += w[i] * w[j] * f(x[i], x[j]);
            }
        }
        return sum;
    }
    double GaussTable4pt::integral1D_global(double (*f)(double), double x1, double x2) {
        double sum = 0.0;
        double detJ = (x2 - x1) / 2;
        for (int i = 0; i < 4; i++) {
            double xpc_global = x1 * ((1 - x[i]) / 2) + x2 * ((1 + x[i]) / 2);
            sum += f(xpc_global) * w[i] * detJ;
        }
        return sum;
    }
    double GaussTable4pt::integral2D_global(double (*f)(double, double), ElemUniv d, element e) {
        if (NPC != 16) {
            cerr << "GaussTable4pt::integral2D_global: Ilosc punktow calkowania nie jest rowna 16" << endl;
            exit(EXIT_FAILURE);
        }
        else {
            double sum = 0.0;
            for (int i = 0; i < 16; i++) {
                double xpc_global = e.nodes[0]->x * d.N_KsiEta[i][0] + e.nodes[1]->x * d.N_KsiEta[i][1] + e.nodes[2]->x * d.N_KsiEta[i][2] + e.nodes[3]->x * d.N_KsiEta[i][3];
                double ypc_global = e.nodes[0]->y * d.N_KsiEta[i][0] + e.nodes[1]->y * d.N_KsiEta[i][1] + e.nodes[2]->y * d.N_KsiEta[i][2] + e.nodes[3]->y * d.N_KsiEta[i][3];

                double w1, w2;
                switch(i) {
                    case 0: w1 = w[0]; w2 = w[0]; break;
                    case 1: w1 = w[1]; w2 = w[0]; break;
                    case 2: w1 = w[2]; w2 = w[0]; break;
                    case 3: w1 = w[3]; w2 = w[0]; break;
                    case 4: w1 = w[0]; w2 = w[1]; break;
                    case 5: w1 = w[1]; w2 = w[1]; break;
                    case 6: w1 = w[2]; w2 = w[1]; break;
                    case 7: w1 = w[3]; w2 = w[1]; break;
                    case 8: w1 = w[0]; w2 = w[2]; break;
                    case 9: w1 = w[1]; w2 = w[2]; break;
                    case 10: w1 = w[2]; w2 = w[2]; break;
                    case 11: w1 = w[3]; w2 = w[2]; break;
                    case 12: w1 = w[0]; w2 = w[3]; break;
                    case 13: w1 = w[1]; w2 = w[3]; break;
                    case 14: w1 = w[2]; w2 = w[3]; break;
                    case 15: w1 = w[3]; w2 = w[3]; break;
                    default: break;
                }

                sum += f(xpc_global, ypc_global) * e.Jacobian[i].detJ * w1 * w2;
            }
            return sum;
        }
    }
    array<array<double, 4>, 4> GaussTable4pt::integral2D_H(element e) {
        if (NPC != 16) {
            cerr << "GaussTable4pt::integral2D_H: Ilosc punktow calkowania nie jest rowna 16" << endl;
            exit(EXIT_FAILURE);
        }
        else {
            array<array<double, 4>, 4> sum = { 0 };
            for (int i = 0; i < 16; i++) {
                double w1, w2;
                switch(i) {
                    case 0: w1 = w[0]; w2 = w[0]; break;
                    case 1: w1 = w[1]; w2 = w[0]; break;
                    case 2: w1 = w[2]; w2 = w[0]; break;
                    case 3: w1 = w[3]; w2 = w[0]; break;
                    case 4: w1 = w[0]; w2 = w[1]; break;
                    case 5: w1 = w[1]; w2 = w[1]; break;
                    case 6: w1 = w[2]; w2 = w[1]; break;
                    case 7: w1 = w[3]; w2 = w[1]; break;
                    case 8: w1 = w[0]; w2 = w[2]; break;
                    case 9: w1 = w[1]; w2 = w[2]; break;
                    case 10: w1 = w[2]; w2 = w[2]; break;
                    case 11: w1 = w[3]; w2 = w[2]; break;
                    case 12: w1 = w[0]; w2 = w[3]; break;
                    case 13: w1 = w[1]; w2 = w[3]; break;
                    case 14: w1 = w[2]; w2 = w[3]; break;
                    case 15: w1 = w[3]; w2 = w[3]; break;
                    default: break;
                }

                for (int j = 0; j < 4; j++) {
                    for (int k = 0; k < 4; k++) {
                        sum[j][k] += e.H_local[i].H_npc[j][k] * w1 * w2;
                    }
                }
            }
            return sum;
        }
    }
