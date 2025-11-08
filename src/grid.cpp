#include "grid.h"

void ElemUniv::calculateShapeFunctions(){
    // najpierw zainicjalizuj wartości (chroni przed niezainicjalizowaną pamięcią)
    for (int i = 0; i < NPC; ++i) {
        for (int j = 0; j < 4; ++j) {
            this->N_KsiEta[i][j] = 0.0;
        }
    }

    // implementacja tylko dla 2D
    double ksi = 0.0, eta = 0.0;
    switch (NPC){
        case 1:
            cerr << "ElemUniv::calculateShapeFunctions: Nie zaimplementowano liczenia funkcji kształtu dla 1 punktu calkowania w 2D" << endl;
            exit(EXIT_FAILURE);
        case 4:
            for (int i = 0; i < NPC; i ++){
                if (i == 0) {
                    ksi = GaussTable2pt::x[0];
                    eta = GaussTable2pt::x[0];
                } else if (i == 1) {
                    ksi = GaussTable2pt::x[1];
                    eta = GaussTable2pt::x[0];
                } else if (i == 2) {
                    ksi = GaussTable2pt::x[1];
                    eta = GaussTable2pt::x[1];
                } else { // i == 3
                    ksi = GaussTable2pt::x[0];
                    eta = GaussTable2pt::x[1];
                }
                this->N_KsiEta[i][0] = 0.25 * (1 - ksi) * (1 - eta);
                this->N_KsiEta[i][1] = 0.25 * (1 + ksi) * (1 - eta);
                this->N_KsiEta[i][2] = 0.25 * (1 + ksi) * (1 + eta);
                this->N_KsiEta[i][3] = 0.25 * (1 - ksi) * (1 + eta);
            }
            break;
        case 9:
            for (int i = 0; i < NPC; i ++){
                if (i == 0) {
                    ksi = GaussTable3pt::x[0];
                    eta = GaussTable3pt::x[0];
                } else if (i == 1) {
                    ksi = GaussTable3pt::x[1];
                    eta = GaussTable3pt::x[0];
                } else if (i == 2) {
                    ksi = GaussTable3pt::x[2];
                    eta = GaussTable3pt::x[0];
                } else if (i == 3) {
                    ksi = GaussTable3pt::x[0];
                    eta = GaussTable3pt::x[1];
                } else if (i == 4) {
                    ksi = GaussTable3pt::x[1];
                    eta = GaussTable3pt::x[1];
                } else if (i == 5) {
                    ksi = GaussTable3pt::x[2];
                    eta = GaussTable3pt::x[1];
                } else if (i == 6) {
                    ksi = GaussTable3pt::x[0];
                    eta = GaussTable3pt::x[2];
                } else if (i == 7) {
                    ksi = GaussTable3pt::x[1];
                    eta = GaussTable3pt::x[2];
                } else { // i == 8
                    ksi = GaussTable3pt::x[2];
                    eta = GaussTable3pt::x[2];
                }
                this->N_KsiEta[i][0] = 0.25 * (1 - ksi) * (1 - eta);
                this->N_KsiEta[i][1] = 0.25 * (1 + ksi) * (1 - eta);
                this->N_KsiEta[i][2] = 0.25 * (1 + ksi) * (1 + eta);
                this->N_KsiEta[i][3] = 0.25 * (1 - ksi) * (1 + eta);
            }
            break;
        default:
            cerr << "ElemUniv::calculateShapeFunctions: Niepoprawna ilosc punktow calkowania dla 2D" << endl;
            exit(EXIT_FAILURE);
    }
}

void ElemUniv::calculateDerivatives(){
    if (D == 1) {
        // żeby zaimplementować - trzeba zmienić tablice ze statycznych na dynamiczne bo zmienia się ilość równań w każdym wymiarze
        cerr << "ElemUniv::calculateDerivatives: Nie zaimplementowano liczenia calek Jakobianu dla 1D" << endl;
        exit(EXIT_FAILURE);
    }
    else if (D == 2) {
        double ksi, eta;
        switch (NPC){
            case 1:
                cerr << "ElemUniv::calculateDerivatives: Nie zaimplementowano liczenia calek Jakobianu dla 1 punktu calkowania w 2D" << endl;
                exit(EXIT_FAILURE);
            case 4:
                for (int i = 0; i < NPC; i ++){
                    if (i == 0) {
                        ksi = GaussTable2pt::x[0];
                        eta = GaussTable2pt::x[0];
                    }
                    if (i == 1) {
                        ksi = GaussTable2pt::x[1];
                        eta = GaussTable2pt::x[0];
                    }
                    if (i == 2) {
                        ksi = GaussTable2pt::x[1];
                        eta = GaussTable2pt::x[1];
                    }
                    if (i == 3) {
                        ksi = GaussTable2pt::x[0];
                        eta = GaussTable2pt::x[1];
                    }
                    this->dN_dKsi[i][0] = -0.25 * (1 - eta);
                    this->dN_dKsi[i][1] =  0.25 * (1 - eta);
                    this->dN_dKsi[i][2] =  0.25 * (1 + eta);
                    this->dN_dKsi[i][3] = -0.25 * (1 + eta);

                    this->dN_dEta[i][0] = -0.25 * (1 - ksi);
                    this->dN_dEta[i][1] = -0.25 * (1 + ksi);
                    this->dN_dEta[i][2] =  0.25 * (1 + ksi);
                    this->dN_dEta[i][3] =  0.25 * (1 - ksi);
                }
                break;
            case 9:
                for (int i = 0; i < NPC; i ++){
                    if (i == 0) {
                        ksi = GaussTable3pt::x[0];
                        eta = GaussTable3pt::x[0];
                    }
                    if (i == 1) {
                        ksi = GaussTable3pt::x[1];
                        eta = GaussTable3pt::x[0];
                    }
                    if (i == 2) {
                        ksi = GaussTable3pt::x[2];
                        eta = GaussTable3pt::x[0];
                    }
                    if (i == 3) {
                        ksi = GaussTable3pt::x[0];
                        eta = GaussTable3pt::x[1];
                    }
                    if (i == 4) {
                        ksi = GaussTable3pt::x[1];
                        eta = GaussTable3pt::x[1];
                    }
                    if (i == 5) {
                        ksi = GaussTable3pt::x[2];
                        eta = GaussTable3pt::x[1];
                    }
                    if (i == 6) {
                        ksi = GaussTable3pt::x[0];
                        eta = GaussTable3pt::x[2];
                    }
                    if (i == 7) {
                        ksi = GaussTable3pt::x[1];
                        eta = GaussTable3pt::x[2];
                    }
                    if (i == 8) {
                        ksi = GaussTable3pt::x[2];
                        eta = GaussTable3pt::x[2];
                    }
                    this->dN_dKsi[i][0] = -0.25 * (1 - eta);
                    this->dN_dKsi[i][1] =  0.25 * (1 - eta);
                    this->dN_dKsi[i][2] =  0.25 * (1 + eta);
                    this->dN_dKsi[i][3] = -0.25 * (1 + eta);

                    this->dN_dEta[i][0] = -0.25 * (1 - ksi);
                    this->dN_dEta[i][1] = -0.25 * (1 + ksi);
                    this->dN_dEta[i][2] =  0.25 * (1 + ksi);
                    this->dN_dEta[i][3] =  0.25 * (1 - ksi);
                }
                break;
            default:
                cerr << "ElemUniv::calculateDerivatives: Niepoprawna ilosc punktow calkowania dla 2D" << endl;
                exit(EXIT_FAILURE);
                break;
        }
    }
    else if (D == 3){
        cerr << "ElemUniv::calculateDerivatives: Nie zaimplementowano liczenia calek Jakobianu dla 3D" << endl;
        exit(EXIT_FAILURE);
    }
    else {
        cerr << "ElemUniv::calculateDerivatives: Niepoprawna ilosc wymiarow" << endl;
        exit(EXIT_FAILURE);
    }
}

void element::calculateJakobian(ElemUniv d){
    double dx_dKsi, dy_dKsi;
    double dx_dEta, dy_dEta;

    for (int i = 0; i < NPC; i++){
        dx_dKsi = d.dN_dKsi[i][0]*ID[0]->x + d.dN_dKsi[i][1]*ID[1]->x + d.dN_dKsi[i][2]*ID[2]->x + d.dN_dKsi[i][3]*ID[3]->x;
        dx_dEta = d.dN_dEta[i][0]*ID[0]->x + d.dN_dEta[i][1]*ID[1]->x + d.dN_dEta[i][2]*ID[2]->x + d.dN_dEta[i][3]*ID[3]->x;
        dy_dKsi = d.dN_dKsi[i][0]*ID[0]->y + d.dN_dKsi[i][1]*ID[1]->y + d.dN_dKsi[i][2]*ID[2]->y + d.dN_dKsi[i][3]*ID[3]->y;
        dy_dEta = d.dN_dEta[i][0]*ID[0]->y + d.dN_dEta[i][1]*ID[1]->y + d.dN_dEta[i][2]*ID[2]->y + d.dN_dEta[i][3]*ID[3]->y;

        jakobian[i].J[0][0] = dx_dKsi;
        jakobian[i].J[1][0] = dx_dEta;
        jakobian[i].J[0][1] = dy_dKsi;
        jakobian[i].J[1][1] = dy_dEta;

        jakobian[i].detJ = dx_dKsi*dy_dEta - dx_dEta*dy_dKsi;

        if (fabs(jakobian[i].detJ) < 1e-12) {
            cerr << "element::calculateJakobian: Zerowy lub bardzo maly wyznacznik Jakobianu" << endl;
            exit(EXIT_FAILURE);
        }

        double invDet = 1.0 / jakobian[i].detJ;
        jakobian[i].J1[0][0] = invDet * (dy_dEta);
        jakobian[i].J1[1][0] = invDet * (-dx_dEta);
        jakobian[i].J1[0][1] = invDet * (-dy_dKsi);
        jakobian[i].J1[1][1] = invDet * (dx_dKsi);
    }
}

void ElemUniv::print(){
    for (int i = 0; i < NPC; i++){
        cout << "P" << i+1  << ":" << endl;
        cout << " Funkcje ksztaltu: " << endl;
        for (int j = 0; j < 4; j++){
            cout << "  " << j+1 << ". N_KsiEta: " << this->N_KsiEta[i][j] << endl;
        }
        cout << " Pochodne funkcji ksztaltu: " << endl;
        for (int j = 0; j < 4; j++){
            cout << "  " << j+1 << ". dN_Ksi: " << this->dN_dKsi[i][j] << endl;
        }
        for (int j = 0; j < 4; j++){
            cout << "  " << j+1 << ". dN_Eta: " << this->dN_dEta[i][j] << endl;
        }
        cout << "\n";
    }
}

void element::print(int elementID){
    if (elementID == 0) {cout << "Element"<< endl;}
    else {cout << "Element: "<< elementID << endl;}
    cout << " Wezly elementu: " << endl;
    for (int j = 0; j < 4; j++){
        cout << "  ID " << j + 1 << ": (" << ID[j]->x << ", " << ID[j]->y << ")" << endl;
    }
    cout << "\n Jakobian w punktach calkowania: " << endl;
    for (int i = 0; i < NPC; i++){
        cout << "  P" << i + 1 << ":" << endl;
        cout << "     J = [ " << jakobian[i].J[0][0] << "  " << jakobian[i].J[0][1] << " ]" << endl;
        cout << "         [ " << jakobian[i].J[1][0] << "  " << jakobian[i].J[1][1] << " ]" << endl;
        cout << "  detJ = " << jakobian[i].detJ << endl;
        cout << "    J1 = [ " << jakobian[i].J1[0][0] << "  " << jakobian[i].J1[0][1] << " ]" << endl;
        cout << "         [ " << jakobian[i].J1[1][0] << "  " << jakobian[i].J1[1][1] << " ]\n" << endl;
    }
}

void grid::print(){
    cout << "Calkowita liczba wezlow: " << nN << endl;
    cout << "Calkowita liczba elementow: " << nE << endl;
    cout << "\n";
    cout << "Wspolrzedne poszczegolnych wezlow: " << endl; 
    for (int i = 0; i < nN; i++){
        cout << " ID " << i + 1 << ": (" << node[i].x << ", " << node[i].y << ")" << endl;
    }
    cout << "\n";
    cout << "Wezly w poszczegolnych elementach: " << endl;
    for (int i = 0; i < nE; i++){
        cout << " Element: " << i + 1 << endl;
        cout << "  ";
        for (int j = 0; j < 4; j++){
            int index = distance(node.data(), element[i].ID[j]) + 1; //tu liczy indeks po zajmowanym miejscu w pamieci
            cout << index << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void GlobalData::print(){
    cout << "Dane globalne z pliku:" << endl;
    cout << " SimulationTime: " << SimulationTime << endl;
    cout << " SimulationStepTime: " << SimulationStepTime << endl;
    cout << " Conductivity: " << Conductivity << endl;
    cout << " Alfa: " << Alfa << endl;
    cout << " Tot: " << Tot << endl;
    cout << " InitialTemp: " << InitialTemp << endl;
    cout << " Density: " << Density << endl;
    cout << " SpecificHeat: " << SpecificHeat << endl;
    cout << " npc: " << npc << endl;
    cout << " dimension: " << dimension << endl;
    cout << " nN: " << nN << endl;
    cout << " nE: " << nE << endl;
    cout << "\n";
}
