#include "readFromFile.h"
#include "grid.h"

using namespace std;

bool readFromFile(const string& filename, GlobalData& globalData, grid& mesh) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Nie mozna otworzyc pliku: " << filename << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string key;
        ss >> key;

        if (key == "SimulationTime") ss >> globalData.SimulationTime;
        else if (key == "SimulationStepTime") ss >> globalData.SimulationStepTime;
        else if (key == "Conductivity") ss >> globalData.Conductivity;
        else if (key == "Alfa") ss >> globalData.Alfa;
        else if (key == "Tot") ss >> globalData.Tot;
        else if (key == "InitialTemp") ss >> globalData.InitialTemp;
        else if (key == "Density") ss >> globalData.Density;
        else if (key == "SpecificHeat") ss >> globalData.SpecificHeat;
        else if (key == "Nodes") {
            string tmp; ss >> tmp >> globalData.nN;
            mesh.nN = globalData.nN;
            mesh.node.resize(globalData.nN);
        }
        else if (key == "Elements") {
            string tmp; ss >> tmp >> globalData.nE;
            mesh.nE = globalData.nE;
            mesh.element.resize(globalData.nE);
        }
        else if (key == "*Node") {
            for (int i = 0; i < globalData.nN; ++i) {
                getline(file, line);
                stringstream nodeStream(line);
                int idx;
                char comma;
                nodeStream >> idx >> comma >> mesh.node[i].x >> comma >> mesh.node[i].y;
            }
        }
        else if (key == "*Element,") {
            for (int i = 0; i < globalData.nE; ++i) {
                getline(file, line);
                stringstream elStream(line);
                int idx, n1, n2, n3, n4;
                char comma;
                elStream >> idx >> comma >> n1 >> comma >> n2 >> comma >> n3 >> comma >> n4;
                mesh.element[i].ID[0] = &mesh.node[n1 - 1];
                mesh.element[i].ID[1] = &mesh.node[n2 - 1];
                mesh.element[i].ID[2] = &mesh.node[n3 - 1];
                mesh.element[i].ID[3] = &mesh.node[n4 - 1];
            }
        }
    }

    cout << "Dane z pliku: " << filename << " zostaly wczytane\n" << endl;
    file.close();
    return true;
}
