// Copyright 2022 Max Akimtsov

#include "lib/SandpileGenerator.h"

#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    SandpileGenerator SG;

    SG.GetOptions(argc, argv);

    std::vector <std::vector<uint64_t>> coordinates = SG.CreateGrainsMap();

    SG.PilesCollapse(coordinates);

    return 0;
}