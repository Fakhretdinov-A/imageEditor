#pragma once

#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Filters/standard_filters.h"
#include "Filters/matrix_filters.h"
#include "Filters/my_filters.h"

void UseFilters(Picture&, std::vector<std::vector<std::string>>);
