// Copyright 2022 Max Akimtsov

#include "SandpileGenerator.h"
#include "BMP.h"

#define WHITE_COLOR Color(1.0f, 1.0f, 1.0f)
#define GREEN_COLOR Color(0.0f, 1.0f, 0.0f)
#define MAGENTA_COLOR Color(1.0f, 0.0f, 1.0f)
#define YELLOW_COLOR Color(1.0f, 1.0f, 0.0f)
#define BLACK_COLOR Color(0.0f, 0.0f, 0.0f)

void SandpileGenerator::GetOptions(int argc, char** argv) {
    std::vector<std::string> options;
    for (int i = 1; i < argc; i++) {
        std::string str(argv[i]);
        options.push_back(str);
    }
    for (int i = 0; i < options.size() - 1; i++) {
        if (options[i] == "-l" || options[i] == "--length") {
            this->length = std::stoi(options[i + 1]);
        } else if (options[i] == "-w" || options[i] == "--width") {
            this->width = std::stoi(options[i + 1]);
        } else if (options[i] == "-i" || options[i] == "--input") {
            this->input_filepath = options[i + 1];
        } else if (options[i] == "-o" || options[i] == "--output") {
            this->output_filepath = options[i + 1];
        } else if (options[i] == "-m" || options[i] == "--max-iter") {
            this->iterations = std::stoi(options[i + 1]);
        } else if (options[i] == "-f" || options[i] == "--freq") {
            this->frequency = std::stoi(options[i + 1]);
        }
    }
}
std::vector<std::vector<uint64_t>> SandpileGenerator::CreateGrainsMap() {
    std::ifstream FileOpen;
    FileOpen.open(this->input_filepath);
    std::vector<std::vector<uint64_t>> coordinates(this->length, std::vector<uint64_t>(this->width));
    if (FileOpen.is_open()) {
        uint16_t x;
        uint16_t y;
        uint64_t particles_amount;
        while (FileOpen >> x >> y >> particles_amount) {
            coordinates[x][y] = particles_amount;
        }
        return coordinates;
    } else {
        std::cout << "OpenError: input file opening corrupted" << std::endl;
    }
}

void SandpileGenerator::PilesCollapse(std::vector<std::vector<uint64_t>>& coordinates) {
    for (uint64_t iter = 0; iter < this->iterations; iter++) {
        BMP BMPImage(this->length, this->width);
        bool any_four_on_field = false;
        for (int32_t i = 0; i < this->length; i++) {
            for (int32_t j = 0; j < this->width; j++) {
                if (coordinates[i][j] > 3) {
                    any_four_on_field = true;
                    coordinates[i][j] -= 4;
                    coordinates[i - 1][j]++;
                    coordinates[i + 1][j]++;
                    coordinates[i][j - 1]++;
                    coordinates[i][j + 1]++;
                    if (i - 1 >= 0) {
                        coordinates[i - 1][j]++;
                    }
                    if (i + 1 < this->length) {
                        coordinates[i + 1][j]++;
                    }
                    if (j - 1 >= 0) {
                        coordinates[i][j - 1]++;
                    }
                    if (j + 1 < this->width) {
                        coordinates[i][j + 1]++;
                    }
                }
            }
        }
        if (iter % this->frequency == 0 || !any_four_on_field) {
            for (uint16_t x = 0; x < this->length; x++) {
                for (uint16_t y = 0; y < this->width; y++) {
                    if (coordinates[x][y] == 0) {
                        BMPImage.SetColor(WHITE_COLOR, x, y);
                    } else if (coordinates[x][y] == 1) {
                        BMPImage.SetColor(GREEN_COLOR, x, y);
                    } else if (coordinates[x][y] == 2) {
                        BMPImage.SetColor(MAGENTA_COLOR, x, y);
                    } else if (coordinates[x][y] == 3) {
                        BMPImage.SetColor(YELLOW_COLOR, x, y);
                    } else if (coordinates[x][y] > 3) {
                        BMPImage.SetColor(BLACK_COLOR, x, y);
                    }
                }
            }
            BMPImage.Export(this->output_filepath + '/' + std::to_string(iter) + ".bmp");
        }
        if (!any_four_on_field) {
            return;
        }
    }
}