#pragma once

#include "grid.h"
#include "functions.h"
#include "GaussTable.h"
#include "readFromFile.h"
#include <string>
#include <iostream>

bool runSimulation(const std::string& inputPath, GlobalData& globalData, grid& mesh, bool debug = false);