#include "readFromFile.h"
#include "grid.h"
#include "GaussTable.h"
#include "functions.h"

#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    // zmiana NPC i DEBUG_MODE w config.h

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Symulacja");

    const char* inputPath;
    if (argc > 1) {
        inputPath = argv[1];
        w.loadAndRun(QString(inputPath));
    }

    w.show();
    return a.exec();
    //return 0;
}
