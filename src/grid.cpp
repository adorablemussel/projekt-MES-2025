#include "grid.h"

void ElemUniv::calculateShapeFunctions(){
    for (int i = 0; i < NPC; ++i) {
        for (int j = 0; j < 4; ++j) {
            this->N_KsiEta[i][j] = 0.0;
        }
    }

    //implementacja tylko dla 2D
    double ksi = 0.0, eta = 0.0;
    switch (NPC){
        case 1:
            cerr << "ElemUniv::calculateShapeFunctions: Nie zaimplementowano liczenia funkcji kształtu dla 1 punktu calkowania w 2D" << endl;
            exit(EXIT_FAILURE);
        case 4:
            for (int i = 0; i < NPC; i ++){
                if (i == 0) {ksi = GaussTable2pt::x[0]; eta = GaussTable2pt::x[0];} 
                else if (i == 1) {ksi = GaussTable2pt::x[1]; eta = GaussTable2pt::x[0];} 
                else if (i == 2) {ksi = GaussTable2pt::x[1]; eta = GaussTable2pt::x[1];} 
                else {/* i == 3 */ksi = GaussTable2pt::x[0]; eta = GaussTable2pt::x[1];}

                this->N_KsiEta[i][0] = 0.25 * (1 - ksi) * (1 - eta);
                this->N_KsiEta[i][1] = 0.25 * (1 + ksi) * (1 - eta);
                this->N_KsiEta[i][2] = 0.25 * (1 + ksi) * (1 + eta);
                this->N_KsiEta[i][3] = 0.25 * (1 - ksi) * (1 + eta);
            }
            break;
        case 9:
            for (int i = 0; i < NPC; i ++){
                if (i == 0) {ksi = GaussTable3pt::x[0]; eta = GaussTable3pt::x[0];} 
                else if (i == 1) {ksi = GaussTable3pt::x[1]; eta = GaussTable3pt::x[0];} 
                else if (i == 2) {ksi = GaussTable3pt::x[2]; eta = GaussTable3pt::x[0];} 
                else if (i == 3) {ksi = GaussTable3pt::x[0]; eta = GaussTable3pt::x[1];} 
                else if (i == 4) {ksi = GaussTable3pt::x[1]; eta = GaussTable3pt::x[1];} 
                else if (i == 5) {ksi = GaussTable3pt::x[2]; eta = GaussTable3pt::x[1];} 
                else if (i == 6) {ksi = GaussTable3pt::x[0]; eta = GaussTable3pt::x[2];} 
                else if (i == 7) {ksi = GaussTable3pt::x[1]; eta = GaussTable3pt::x[2];} 
                else {/* i == 8 */ksi = GaussTable3pt::x[2]; eta = GaussTable3pt::x[2];}
                this->N_KsiEta[i][0] = 0.25 * (1 - ksi) * (1 - eta);
                this->N_KsiEta[i][1] = 0.25 * (1 + ksi) * (1 - eta);
                this->N_KsiEta[i][2] = 0.25 * (1 + ksi) * (1 + eta);
                this->N_KsiEta[i][3] = 0.25 * (1 - ksi) * (1 + eta);
            }
            break;
        case 16:
            for (int i = 0; i < NPC; i++){
                if (i == 0) { ksi = GaussTable4pt::x[0]; eta = GaussTable4pt::x[0];}
                else if (i == 1) { ksi = GaussTable4pt::x[1]; eta = GaussTable4pt::x[0];}
                else if (i == 2) { ksi = GaussTable4pt::x[2]; eta = GaussTable4pt::x[0];}
                else if (i == 3) { ksi = GaussTable4pt::x[3]; eta = GaussTable4pt::x[0];}
                else if (i == 4) { ksi = GaussTable4pt::x[0]; eta = GaussTable4pt::x[1];}
                else if (i == 5) { ksi = GaussTable4pt::x[1]; eta = GaussTable4pt::x[1];}
                else if (i == 6) { ksi = GaussTable4pt::x[2]; eta = GaussTable4pt::x[1];}
                else if (i == 7) { ksi = GaussTable4pt::x[3]; eta = GaussTable4pt::x[1];}
                else if (i == 8) { ksi = GaussTable4pt::x[0]; eta = GaussTable4pt::x[2];}
                else if (i == 9) { ksi = GaussTable4pt::x[1]; eta = GaussTable4pt::x[2];}
                else if (i == 10) { ksi = GaussTable4pt::x[2]; eta = GaussTable4pt::x[2];}
                else if (i == 11) { ksi = GaussTable4pt::x[3]; eta = GaussTable4pt::x[2];}
                else if (i == 12) { ksi = GaussTable4pt::x[0]; eta = GaussTable4pt::x[3];}
                else if (i == 13) { ksi = GaussTable4pt::x[1]; eta = GaussTable4pt::x[3];}
                else if (i == 14) { ksi = GaussTable4pt::x[2]; eta = GaussTable4pt::x[3];}
                else {/* i == 15 */ ksi = GaussTable4pt::x[3]; eta = GaussTable4pt::x[3];}
                
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
        //(żeby zaimplementować - trzeba zmienić tablice ze statycznych na dynamiczne bo zmienia się ilość równań w każdym wymiarze)
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
                    if (i == 0) { ksi = GaussTable2pt::x[0]; eta = GaussTable2pt::x[0];}
                    else if (i == 1) { ksi = GaussTable2pt::x[1]; eta = GaussTable2pt::x[0];}
                    else if (i == 2) { ksi = GaussTable2pt::x[1]; eta = GaussTable2pt::x[1];}
                    else if (i == 3) { ksi = GaussTable2pt::x[0]; eta = GaussTable2pt::x[1];}

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
                    if (i == 0) { ksi = GaussTable3pt::x[0]; eta = GaussTable3pt::x[0];}
                    else if (i == 1) { ksi = GaussTable3pt::x[1]; eta = GaussTable3pt::x[0];}
                    else if (i == 2) { ksi = GaussTable3pt::x[2]; eta = GaussTable3pt::x[0];}
                    else if (i == 3) { ksi = GaussTable3pt::x[0]; eta = GaussTable3pt::x[1];}
                    else if (i == 4) { ksi = GaussTable3pt::x[1]; eta = GaussTable3pt::x[1];}
                    else if (i == 5) { ksi = GaussTable3pt::x[2]; eta = GaussTable3pt::x[1];}
                    else if (i == 6) { ksi = GaussTable3pt::x[0]; eta = GaussTable3pt::x[2];}
                    else if (i == 7) { ksi = GaussTable3pt::x[1]; eta = GaussTable3pt::x[2];}
                    else if (i == 8) { ksi = GaussTable3pt::x[2]; eta = GaussTable3pt::x[2];}
                    
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
            case 16:
                for (int i = 0; i < NPC; i++){
                    if (i == 0) { ksi = GaussTable4pt::x[0]; eta = GaussTable4pt::x[0];}
                    else if (i == 1) { ksi = GaussTable4pt::x[1]; eta = GaussTable4pt::x[0];}
                    else if (i == 2) { ksi = GaussTable4pt::x[2]; eta = GaussTable4pt::x[0];}
                    else if (i == 3) { ksi = GaussTable4pt::x[3]; eta = GaussTable4pt::x[0];}
                    else if (i == 4) { ksi = GaussTable4pt::x[0]; eta = GaussTable4pt::x[1];}
                    else if (i == 5) { ksi = GaussTable4pt::x[1]; eta = GaussTable4pt::x[1];}
                    else if (i == 6) { ksi = GaussTable4pt::x[2]; eta = GaussTable4pt::x[1];}
                    else if (i == 7) { ksi = GaussTable4pt::x[3]; eta = GaussTable4pt::x[1];}
                    else if (i == 8) { ksi = GaussTable4pt::x[0]; eta = GaussTable4pt::x[2];}
                    else if (i == 9) { ksi = GaussTable4pt::x[1]; eta = GaussTable4pt::x[2];}
                    else if (i == 10) { ksi = GaussTable4pt::x[2]; eta = GaussTable4pt::x[2];}
                    else if (i == 11) { ksi = GaussTable4pt::x[3]; eta = GaussTable4pt::x[2];}
                    else if (i == 12) { ksi = GaussTable4pt::x[0]; eta = GaussTable4pt::x[3];}
                    else if (i == 13) { ksi = GaussTable4pt::x[1]; eta = GaussTable4pt::x[3];}
                    else if (i == 14) { ksi = GaussTable4pt::x[2]; eta = GaussTable4pt::x[3];}
                    else {/* i == 15 */ ksi = GaussTable4pt::x[3]; eta = GaussTable4pt::x[3];}
                    
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

void ElemUniv::calculateSurfaceFunctions() {
    int npc1D = sqrt(NPC);
    for (int edge = 0; edge < 4; ++edge) {
        Surface& S = surface[edge];
        S.npc1D = npc1D;

        S.w.resize(npc1D);

        for (int k = 0; k < 4; ++k){
            S.N[k].resize(npc1D);
        }

        for (int j = 0; j < npc1D; ++j) {
            double t;
            double w;

            if (npc1D == 2)      { t = GaussTable2pt::x[j]; w = GaussTable2pt::w[j]; }
            else if (npc1D == 3) { t = GaussTable3pt::x[j]; w = GaussTable3pt::w[j]; }
            else                 { t = GaussTable4pt::x[j]; w = GaussTable4pt::w[j]; }

            double ksi;
            double eta;
            if (edge == 0) { ksi = t;    eta = -1.0; }
            else if (edge == 1) { ksi = 1.0;  eta = t; } 
            else if (edge == 2) { ksi = -t;   eta = 1.0; }
            else { ksi = -1.0; eta = -t; }

            S.w[j] = w;
            S.N[0][j] = 0.25*(1-ksi)*(1-eta);
            S.N[1][j] = 0.25*(1+ksi)*(1-eta);
            S.N[2][j] = 0.25*(1+ksi)*(1+eta);
            S.N[3][j] = 0.25*(1-ksi)*(1+eta);
        }
    }
}

void element::calculateJacobian(const ElemUniv& d){
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
            cerr << "element::calculateJacobian: Jakobian zerowy" << endl;
            exit(EXIT_FAILURE);
        }

        double invDet = 1.0 / Jacobian[i].detJ;
        Jacobian[i].J1[0][0] = invDet * (dy_dEta);
        Jacobian[i].J1[1][0] = invDet * (-dx_dEta);
        Jacobian[i].J1[0][1] = invDet * (-dy_dKsi);
        Jacobian[i].J1[1][1] = invDet * (dx_dKsi);
    }
}

void element::calculateLocalHMatrix(const ElemUniv& d, const GlobalData& data){
    double conductivity = data.Conductivity;

    for (int i = 0; i < NPC; i++){
        for (int j = 0; j < 4; j++){
            H_local[i].dN_dx[j] = Jacobian[i].J1[0][0] * d.dN_dKsi[i][j] + Jacobian[i].J1[0][1] * d.dN_dEta[i][j];
            H_local[i].dN_dy[j] = Jacobian[i].J1[1][0] * d.dN_dKsi[i][j] + Jacobian[i].J1[1][1] * d.dN_dEta[i][j];
        }
    }

    for (int i = 0; i < NPC; i++){
        for (int j = 0; j < 4; j++){
            for (int k = 0; k < 4; k++){
                H_local[i].H_npc[j][k] = conductivity * (H_local[i].dN_dx[j] * H_local[i].dN_dx[k] + H_local[i].dN_dy[j] * H_local[i].dN_dy[k]) * Jacobian[i].detJ;
            }
        }
    }

    for (int r = 0; r < 4; r++){
        for (int c = 0; c < 4; c++){
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
    else if (NPC == 16){
        for (int i = 0; i < 16; i++){
            double w1, w2;
            switch(i){
                case 0: w1 = GaussTable4pt::w[0]; w2 = GaussTable4pt::w[0]; break;
                case 1: w1 = GaussTable4pt::w[1]; w2 = GaussTable4pt::w[0]; break;
                case 2: w1 = GaussTable4pt::w[2]; w2 = GaussTable4pt::w[0]; break;
                case 3: w1 = GaussTable4pt::w[3]; w2 = GaussTable4pt::w[0]; break;
                case 4: w1 = GaussTable4pt::w[0]; w2 = GaussTable4pt::w[1]; break;
                case 5: w1 = GaussTable4pt::w[1]; w2 = GaussTable4pt::w[1]; break;
                case 6: w1 = GaussTable4pt::w[2]; w2 = GaussTable4pt::w[1]; break;
                case 7: w1 = GaussTable4pt::w[3]; w2 = GaussTable4pt::w[1]; break;
                case 8: w1 = GaussTable4pt::w[0]; w2 = GaussTable4pt::w[2]; break;
                case 9: w1 = GaussTable4pt::w[1]; w2 = GaussTable4pt::w[2]; break;
                case 10: w1 = GaussTable4pt::w[2]; w2 = GaussTable4pt::w[2]; break;
                case 11: w1 = GaussTable4pt::w[3]; w2 = GaussTable4pt::w[2]; break;
                case 12: w1 = GaussTable4pt::w[0]; w2 = GaussTable4pt::w[3]; break;
                case 13: w1 = GaussTable4pt::w[1]; w2 = GaussTable4pt::w[3]; break;
                case 14: w1 = GaussTable4pt::w[2]; w2 = GaussTable4pt::w[3]; break;
                case 15: w1 = GaussTable4pt::w[3]; w2 = GaussTable4pt::w[3]; break;
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
        cerr << "element::calculateLocalHMatrix: Niezaimplementowana liczba punktow calkowania" << endl;
        exit(EXIT_FAILURE);
    }
}

void element::calculateLocalHbcMatrix(const ElemUniv& d, const GlobalData& data) {
    for (int r=0;r<4;r++){
        for (int c=0;c<4;c++) {
            Hbc_local[r][c]=0.0;
        }
    }
    int edges[4][2]={{0,1}, {1,2}, {2,3}, {3,0}};

    for (int i=0;i<4;i++){
        int a = edges[i][0];
        int b = edges[i][1];

        if (!(nodes[a]->BC && nodes[b]->BC)) continue;

        double dx = nodes[b]->x - nodes[a]->x;
        double dy = nodes[b]->y - nodes[a]->y;
        double detJ_edge = 0.5 * std::sqrt(dx*dx+dy*dy);

        const ElemUniv::Surface& S = d.surface[i];

        for (int j=0;j<S.npc1D;j++){
            double w=S.w[j];

            for (int k=0;k<4;k++)
                for (int l=0;l<4;l++)
                    Hbc_local[k][l] += data.Alfa * S.N[k][j] * S.N[l][j] * w * detJ_edge;
        }
    }
}

void element::calculateLocalPVector(const ElemUniv& d, const GlobalData& data){
    for (int k=0;k<4;k++){

        P_local[k]=0.0;
    }
    int edges[4][2]={{0,1}, {1,2}, {2,3}, {3,0}};

    for (int i=0;i<4;i++){
        int a = edges[i][0];
        int b = edges[i][1];

        if (!(nodes[a]->BC && nodes[b]->BC)) continue;

        double dx = nodes[b]->x - nodes[a]->x;
        double dy = nodes[b]->y - nodes[a]->y;
        double detJ_edge = 0.5 * std::sqrt(dx*dx+dy*dy);

        const ElemUniv::Surface& S = d.surface[i];

        for (int j=0;j<S.npc1D;j++){
            double w=S.w[j];

            for (int k=0;k<4;k++)
                P_local[k] += data.Alfa * data.Tot * S.N[k][j] * w * detJ_edge;
        }
    }
}

void element::calculateLocalCMatrix(const ElemUniv& d, const GlobalData& data){
	double density = data.Density;
	double specific_heat = data.SpecificHeat;

	for (int r=0; r<4; r++){
		for (int c=0; c<4; c++){
			C_local[r][c] = 0.0;
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
                    C_local[r][c] += density * specific_heat * d.N_KsiEta[i][r] * d.N_KsiEta[i][c] * Jacobian[i].detJ * w1 * w2;
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
                    C_local[r][c] += density * specific_heat * d.N_KsiEta[i][r] * d.N_KsiEta[i][c] * Jacobian[i].detJ * w1 * w2;
                }
            }
        }
    }
    else if (NPC == 16){
        for (int i = 0; i < 16; i++){
            double w1, w2;
            switch(i){
                case 0: w1 = GaussTable4pt::w[0]; w2 = GaussTable4pt::w[0]; break;
                case 1: w1 = GaussTable4pt::w[1]; w2 = GaussTable4pt::w[0]; break;
                case 2: w1 = GaussTable4pt::w[2]; w2 = GaussTable4pt::w[0]; break;
                case 3: w1 = GaussTable4pt::w[3]; w2 = GaussTable4pt::w[0]; break;
                case 4: w1 = GaussTable4pt::w[0]; w2 = GaussTable4pt::w[1]; break;
                case 5: w1 = GaussTable4pt::w[1]; w2 = GaussTable4pt::w[1]; break;
                case 6: w1 = GaussTable4pt::w[2]; w2 = GaussTable4pt::w[1]; break;
                case 7: w1 = GaussTable4pt::w[3]; w2 = GaussTable4pt::w[1]; break;
                case 8: w1 = GaussTable4pt::w[0]; w2 = GaussTable4pt::w[2]; break;
                case 9: w1 = GaussTable4pt::w[1]; w2 = GaussTable4pt::w[2]; break;
                case 10: w1 = GaussTable4pt::w[2]; w2 = GaussTable4pt::w[2]; break;
                case 11: w1 = GaussTable4pt::w[3]; w2 = GaussTable4pt::w[2]; break;
                case 12: w1 = GaussTable4pt::w[0]; w2 = GaussTable4pt::w[3]; break;
                case 13: w1 = GaussTable4pt::w[1]; w2 = GaussTable4pt::w[3]; break;
                case 14: w1 = GaussTable4pt::w[2]; w2 = GaussTable4pt::w[3]; break;
                case 15: w1 = GaussTable4pt::w[3]; w2 = GaussTable4pt::w[3]; break;
                default: w1 = 0.0; w2 = 0.0; break;
            }
            for (int r = 0; r < 4; r++){
                for (int c = 0; c < 4; c++){
                    C_local[r][c] += density * specific_heat * d.N_KsiEta[i][r] * d.N_KsiEta[i][c] * Jacobian[i].detJ * w1 * w2;
                }
            }
        }
    }
    else {
        cerr << "element::calculateLocalCMatrix: Niezaimplementowana liczba punktow calkowania" << endl;
        exit(EXIT_FAILURE);
    }


}

void grid::calculateGlobalHMatrix(SystemOfEquation& system){
    system.H_global.assign(nN, std::vector<double>(nN, 0.0));

    for (element& e: elements){
        for (int i = 0; i < 4; i++){
            int row = e.nodes[i]->id - 1;
            for (int j = 0; j < 4; j++){
                int col = e.nodes[j]->id - 1;
                system.H_global[row][col] += e.H_local[0].H_elem[i][j];
            }
        }
    }
}

void grid::calculateGlobalHbcMatrix(SystemOfEquation& system){
    for (element& e: elements){
        for (int m = 0; m < 4; m++) {
            int row = e.nodes[m]->id - 1;
            for (int n = 0; n < 4; n++) {
                int col = e.nodes[n]->id - 1;
                system.H_global[row][col] += e.Hbc_local[m][n];
            }
        }
    }
}

void grid::calculateGlobalPVector(SystemOfEquation& system){
    system.P_global.assign(nN, 0.0);

    for (element& e: elements){
        for (int m = 0; m < 4; m++) {
            int global_idx = e.nodes[m]->id - 1;
            system.P_global[global_idx] += e.P_local[m];
        }
    }
}

void grid::calculateGlobalCMatrix(SystemOfEquation& system) {
    system.C_global.assign(nN, vector<double>(nN, 0.0));

    for (element& e : elements) {
        for (int i = 0; i < 4; i++) {

            int row = e.nodes[i]->id - 1;

            for (int j = 0; j < 4; j++) {
                int col = e.nodes[j]->id - 1;
                system.C_global[row][col] += e.C_local[i][j];
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
    cout << "\n JMatrix w punktach calkowania: " << endl;
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
	//Hbc
	bool hasBC = false;
	for (int i = 0; i < NPC; i++) {
		for (int j = 0; j < 4; j++) {
			if(Hbc_local[i][j] != 0.0){
				hasBC = true;
				break;
			}
		}
	}
	if (hasBC) {
	cout << " Macierz Hbc: " << endl;
        for (int i = 0; i < 4; i++) {
            cout << "     ";
            for (int j = 0; j < 4; j++) {
                cout << Hbc_local[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
	else {
        cout << " Element nie ma krawedzi na brzegu (Hbc = 0)." << endl << endl;
    }
    cout << " Wektor P lokalny: " << endl;
    for (int i = 0; i < 4; i++){
        cout << "     P[" << i + 1 << "] = " << P_local[i] << endl;
    }
	cout << endl;
	cout << " Macierz C lokalna: " << endl;
    for (int i = 0; i < 4; i++) {
        cout << "     ";
        for (int j = 0; j < 4; j++) {
            cout << C_local[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
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

void grid::printGlobalHMatrix(SystemOfEquation& system) {
    cout << "Globalna macierz H: " << endl;
    for (int i = 0; i < nN; i++){
        for (int j = 0; j < nN; j++){
            cout << system.H_global[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void grid::printGlobalPVector(SystemOfEquation& system) {
    cout << "Globalny wektor P:" << endl;
    for (int i = 0; i < nN; i++) {
        cout << "Node " << i+1 << ": " << system.P_global[i] << endl;
    }
    cout << endl;
}

void grid::printGlobalCMatrix(SystemOfEquation& system) {
    cout << "Globalna macierz C: " << endl;
    for (int i = 0; i < nN; i++) {
        for (int j = 0; j < nN; j++) {
            cout << system.C_global[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void SystemOfEquation::printTemeperatures(int step, double currentTime ,const vector<double>& temperatures){
    cout << endl;
    cout << "Krok: " << step << " | Czas: " << currentTime << "s" << endl;
    cout << "Temperatury w wezlach:" << endl;
    cout << endl;

    for (size_t i = 0; i < temperatures.size(); i++) {
        cout << "Node " << i + 1 << ":\t" << temperatures[i] << endl;
    }
    cout << endl;
}

void SystemOfEquation::printSteps(int step, int totalSteps, double currentTime, const vector<double>& temp) {
    double minT = *min_element(temp.begin(), temp.end());
    double maxT = *max_element(temp.begin(), temp.end());

    cout << "Krok " << step << "/" << totalSteps 
         << " \tCzas: " << currentTime << "s"
         << " \tMin Temp: " << minT 
         << " \tMax Temp: " << maxT << endl;
}

vector<double> SystemOfEquation::solveGauss(vector<vector<double>>& A, vector<double>& b) {
    int n = b.size();

    for (int i = 0; i < n; i++) {
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (abs(A[k][i]) > abs(A[maxRow][i])) {
                maxRow = k;
            }
        }

        swap(A[i], A[maxRow]);
        swap(b[i], b[maxRow]);

        if (abs(A[i][i]) < 1e-12) continue;
        for (int k = i + 1; k < n; k++) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < n; j++) {
                A[k][j] -= factor * A[i][j];
            }
            b[k] -= factor * b[i];
        }
    }

    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / A[i][i];
    }

    return x;
}

void SystemOfEquation::solveSimulation(const GlobalData& data) {
cout << "\n~ Symulacja procesu cieplnego ~" << endl;

    double dt = data.SimulationStepTime;
    int nSteps = static_cast<int>(data.SimulationTime / dt);
    int nN = P_global.size();
    vector<double> t0(nN, data.InitialTemp);
    vector<double> t1(nN);

    //([H] + [C]/dt) * {t1} = ([C]/dt) * {t0} + {P}
    //[A] = [H] + [C]/dt
    //[C_dt] = [C]/dt
    vector<vector<double>> A(nN, vector<double>(nN, 0.0));
    vector<vector<double>> C_dt(nN, vector<double>(nN, 0.0));

    for (int i = 0; i < nN; i++) {
        for (int j = 0; j < nN; j++) {
            C_dt[i][j] = C_global[i][j] / dt;

            A[i][j] = H_global[i][j] + C_dt[i][j];
        }
    }

    for (int step = 1; step <= nSteps; step++) {
        double currentTime = step * dt;
        vector<double> B(nN, 0.0);
        for (int i = 0; i < nN; i++) {
            double c_part = 0.0;

            for (int j = 0; j < nN; j++) {
                c_part += C_dt[i][j] * t0[j];
            }

            B[i] = c_part + P_global[i];
        }

        vector<vector<double>> A_step = A;
        t1 = solveGauss(A_step, B);

        printSteps(step, nSteps, currentTime, t1);

        //printTemeperatures(step, currentTime, t1);

        t0 = t1;
    }

    this->t = t1;

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
