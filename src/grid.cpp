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

void element::calculateJacobian(ElemUniv d){
    double dx_dKsi, dy_dKsi;
    double dx_dEta, dy_dEta;

    for (int i = 0; i < NPC; i++){
        dx_dKsi = d.dN_dKsi[i][0]*nodes[0]->x + d.dN_dKsi[i][1]*nodes[1]->x + d.dN_dKsi[i][2]*nodes[2]->x + d.dN_dKsi[i][3]*nodes[3]->x;
        dx_dEta = d.dN_dEta[i][0]*nodes[0]->x + d.dN_dEta[i][1]*nodes[1]->x + d.dN_dEta[i][2]*nodes[2]->x + d.dN_dEta[i][3]*nodes[3]->x;
        dy_dKsi = d.dN_dKsi[i][0]*nodes[0]->y + d.dN_dKsi[i][1]*nodes[1]->y + d.dN_dKsi[i][2]*nodes[2]->y + d.dN_dKsi[i][3]*nodes[3]->y;
        dy_dEta = d.dN_dEta[i][0]*nodes[0]->y + d.dN_dEta[i][1]*nodes[1]->y + d.dN_dEta[i][2]*nodes[2]->y + d.dN_dEta[i][3]*nodes[3]->y;

        Jacobian[i].J[0][0] = dx_dKsi;
        Jacobian[i].J[1][0] = dx_dEta;
        Jacobian[i].J[0][1] = dy_dKsi;
        Jacobian[i].J[1][1] = dy_dEta;

        Jacobian[i].detJ = dx_dKsi*dy_dEta - dx_dEta*dy_dKsi;

        if (fabs(Jacobian[i].detJ) < 1e-12) {
            cerr << "element::calculateJacobian: Zerowy lub bardzo maly wyznacznik Jakobianu" << endl;
            exit(EXIT_FAILURE);
        }

        double invDet = 1.0 / Jacobian[i].detJ;
        Jacobian[i].J1[0][0] = invDet * (dy_dEta);
        Jacobian[i].J1[1][0] = invDet * (-dx_dEta);
        Jacobian[i].J1[0][1] = invDet * (-dy_dKsi);
        Jacobian[i].J1[1][1] = invDet * (dx_dKsi);
    }
}

void element::calculateHMatrix(ElemUniv d, GlobalData data){
    double conductivity = data.Conductivity;

    // najpierw liczymy pochodne funkcji kształtu po x i y (macierz dN_dx i dN_dy)
    for (int i = 0; i < NPC; i++){
        for (int j = 0; j < 4; j++){
            H_local[i].dN_dx[j] = Jacobian[i].J1[0][0] * d.dN_dKsi[i][j] + Jacobian[i].J1[0][1] * d.dN_dEta[i][j];
            H_local[i].dN_dy[j] = Jacobian[i].J1[1][0] * d.dN_dKsi[i][j] + Jacobian[i].J1[1][1] * d.dN_dEta[i][j];
        }
    }

    // składowe macierzy H (H w każdym punkcie całkowania)
    for (int i = 0; i < NPC; i++){
        for (int j = 0; j < 4; j++){
            for (int k = 0; k < 4; k++){
                H_local[i].H_npc[j][k] = conductivity * (H_local[i].dN_dx[j] * H_local[i].dN_dx[k] + H_local[i].dN_dy[j] * H_local[i].dN_dy[k]) * Jacobian[i].detJ;
            }
        }
    }

    // policz macierz elementu po integracji powierzchniowej: H_elem = sum_i H(i) * w_ksi(i) * w_eta(i)
    // wyzeruj macierz H_elem przed sumowaniem
    for (int r = 0; r < 4; r++){
        for (int c = 0; c < 4; c++){
            // H_elem przechowujemy w każdym wpisie H_local[i] dla wygody odczytu,
            // ale wartości będą identyczne; wykorzystamy H_local[0].H_elem jako reprezentatywną.
            H_local[0].H_elem[r][c] = 0.0;
        }
    }

    if (NPC == 4){
        for (int i = 0; i < 4; i++){
            double w1, w2;
            switch (i){
                case 0: w1 = GaussTable2pt::w[0]; w2 = GaussTable2pt::w[0]; break;
                case 1: w1 = GaussTable2pt::w[1]; w2 = GaussTable2pt::w[0]; break;
                case 2: w1 = GaussTable2pt::w[1]; w2 = GaussTable2pt::w[1]; break;
                case 3: w1 = GaussTable2pt::w[0]; w2 = GaussTable2pt::w[1]; break;
                default: w1 = 0.0; w2 = 0.0; break;
            }
            for (int r = 0; r < 4; r++){
                for (int c = 0; c < 4; c++){
                    H_local[0].H_elem[r][c] += H_local[i].H_npc[r][c] * w1 * w2;
                }
            }
        }
    }
    else if (NPC == 9){
        for (int i = 0; i < 9; i++){
            double w1, w2;
            switch (i){
                case 0: w1 = GaussTable3pt::w[0]; w2 = GaussTable3pt::w[0]; break;
                case 1: w1 = GaussTable3pt::w[1]; w2 = GaussTable3pt::w[0]; break;
                case 2: w1 = GaussTable3pt::w[2]; w2 = GaussTable3pt::w[0]; break;
                case 3: w1 = GaussTable3pt::w[0]; w2 = GaussTable3pt::w[1]; break;
                case 4: w1 = GaussTable3pt::w[1]; w2 = GaussTable3pt::w[1]; break;
                case 5: w1 = GaussTable3pt::w[2]; w2 = GaussTable3pt::w[1]; break;
                case 6: w1 = GaussTable3pt::w[0]; w2 = GaussTable3pt::w[2]; break;
                case 7: w1 = GaussTable3pt::w[1]; w2 = GaussTable3pt::w[2]; break;
                case 8: w1 = GaussTable3pt::w[2]; w2 = GaussTable3pt::w[2]; break;
                default: w1 = 0.0; w2 = 0.0; break;
            }
            for (int r = 0; r < 4; r++){
                for (int c = 0; c < 4; c++){
                    H_local[0].H_elem[r][c] += H_local[i].H_npc[r][c] * w1 * w2;
                }
            }
        }
    }
    else {
        cerr << "element::calculateHMatrix: Niezaimplementowana liczba punktow calkowania dla integracji H_elem" << endl;
        exit(EXIT_FAILURE);
    }
}

void grid::calculateGlobalHMatrix(){
    // przygotuj rozmiar i wyzeruj globalną macierz H (nN x nN)
    H_global.assign(nN, std::vector<double>(nN, 0.0));

    // agregacja macierzy H z poszczególnych elementów do globalnej macierzy H
    for (element& e: elements){
        for (int i = 0; i < 4; i++){
            int row = e.nodes[i]->id - 1; // indeks w macierzy globalnej
            for (int j = 0; j < 4; j++){
                int col = e.nodes[j]->id - 1; // indeks w macierzy globalnej
                H_global[row][col] += e.H_local[0].H_elem[i][j];
            }
        }
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

void element::print(){

    cout << "Element: "<< id << endl;
    cout << " Wezly elementu: " << endl;
    for (int j = 0; j < 4; j++){
        cout << "  ID " << nodes[j]->id << ": (" << nodes[j]->x << ", " << nodes[j]->y << ")" << endl;
    }
    cout << "\n Jakobian w punktach calkowania: " << endl;
    for (int i = 0; i < NPC; i++){
        cout << "  P" << i + 1 << ":" << endl;
        cout << "     J = [ " << Jacobian[i].J[0][0] << "  " << Jacobian[i].J[0][1] << " ]" << endl;
        cout << "         [ " << Jacobian[i].J[1][0] << "  " << Jacobian[i].J[1][1] << " ]" << endl;
        cout << "  detJ = " << Jacobian[i].detJ << endl;
        cout << "    J1 = [ " << Jacobian[i].J1[0][0] << "  " << Jacobian[i].J1[0][1] << " ]" << endl;
        cout << "         [ " << Jacobian[i].J1[1][0] << "  " << Jacobian[i].J1[1][1] << " ]\n" << endl;
    }
    cout << " Macierz H w punktach calkowania: " << endl;
    for (int i = 0; i < NPC; i++){
        cout << "  P" << i + 1 << ":" << endl;
        for (int j = 0; j < 4; j++){
            cout << "     ";
            for (int k = 0; k < 4; k++){
                cout << H_local[i].H_npc[j][k] << " ";
            }
            cout << endl;
        }
        cout << "\n";
    }
}

void grid::print(){
    cout << "Calkowita liczba wezlow: " << nN << endl;
    cout << "Calkowita liczba elementow: " << nE << endl;
    cout << "\n";
    cout << "Wspolrzedne poszczegolnych wezlow: " << endl; 
    for (int i = 0; i < nN; i++){
        cout << " ID " << i + 1 << ": (" << nodes[i].x << ", " << nodes[i].y << ")" << endl;
    }
    cout << "\n";
    cout << "Wezly w poszczegolnych elementach: " << endl;
    for (int i = 0; i < nE; i++){
        cout << " Element: " << i + 1 << endl;
        cout << "  ";
        for (int j = 0; j < 4; j++){
            cout << elements[i].nodes[j]->id << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void grid::printGlobalHMatrix(){
    cout << "Globalna macierz H: " << endl;
    for (int i = 0; i < nN; i++){
        for (int j = 0; j < nN; j++){
            cout << H_global[i][j] << " ";
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
