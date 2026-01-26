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
        else if (key == "Nodes" || key == "Nodes_number") {
            string next; ss >> next;
            if (isdigit(next[0])) {
                globalData.nN = stoi(next);
            } else {
                ss >> globalData.nN;
            }
            mesh.nN = globalData.nN;
            mesh.nodes.resize(globalData.nN);
        }
        else if (key == "Elements" || key == "Elements_number") {
            string next; ss >> next;
            if (isdigit(next[0])) {
                globalData.nE = stoi(next);
            } else {
                ss >> globalData.nE;
            }
            mesh.nE = globalData.nE;
            mesh.elements.resize(globalData.nE);
        }
        else if (key == "*Node") {
            for (int i = 0; i < globalData.nN; ++i) {
                getline(file, line);
                stringstream nodeStream(line);
                int idx;
                char comma;
                nodeStream >> idx >> comma >> mesh.nodes[i].x >> comma >> mesh.nodes[i].y;
                mesh.nodes[i].id = idx;
                mesh.nodes[i].BC = false;
            }
        }
        else if (key == "*Element,") {
            for (int i = 0; i < globalData.nE; ++i) {
                getline(file, line);
                stringstream elStream(line);
                int idx, n1, n2, n3, n4;
                char comma;
                elStream >> idx >> comma >> n1 >> comma >> n2 >> comma >> n3 >> comma >> n4;
                mesh.elements[i].nodes[0] = &mesh.nodes[n1 - 1];
                mesh.elements[i].nodes[1] = &mesh.nodes[n2 - 1];
                mesh.elements[i].nodes[2] = &mesh.nodes[n3 - 1];
                mesh.elements[i].nodes[3] = &mesh.nodes[n4 - 1];
                mesh.elements[i].id = idx;
            }
        }
        else if (key == "*BC") {
            if (getline(file, line)) {
                stringstream bcStream(line);
                while (bcStream.good()) {
                    int id; char comma;
                    if (!(bcStream >> id)) break;
                    if (id >= 1 && id <= mesh.nN) mesh.nodes[id - 1].BC = true;
                    if (bcStream.peek() == ',') bcStream >> comma;
                    while (bcStream.peek() == ' ') bcStream.get();
        }
    }
}
    }

    cout << endl << "Dane z pliku: " << filename << " zostaly wczytane\n" << endl;
    file.close();
    return true;
}
