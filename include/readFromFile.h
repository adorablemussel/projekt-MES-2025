#pragma once

#include "grid.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool readFromFile(const string& filename, GlobalData& globalData, grid& mesh);