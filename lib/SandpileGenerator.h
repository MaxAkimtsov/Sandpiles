// Copyright 2022 Max Akimtsov
#ifndef LIB_SANDPILEGENERATOR_H_
#define LIB_SANDPILEGENERATOR_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class SandpileGenerator {
private:
    uint16_t length;
    uint16_t width;
    std::string input_filepath;
    std::string output_filepath;
    uint32_t iterations;
    uint32_t frequency;
public:
    void GetOptions(int argc, char* argv[]);

    std::vector <std::vector<uint64_t>> CreateGrainsMap();

    void PilesCollapse(std::vector <std::vector<uint64_t>>& coordinates);
};

#endif  // LIB_SANDPILEGENERATOR_H_