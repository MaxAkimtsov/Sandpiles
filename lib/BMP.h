// Copyright 2022 Max Akimtsov

#ifndef LIB_BMP_H_
#define LIB_BMP_H_

#include <iostream>
#include <string>
#include <vector>

struct Color {
    float r, g, b;

    Color();
    Color(float r, float g, float b);
    ~Color();
};

class BMP {
public:
    BMP(int width, int heigth);
    ~BMP();

    Color GetColor(int x, int y) const;
    void SetColor(const Color& color, int x, int y);

    void Export(std::string path);

private:
    int m_width;
    int m_height;
    std::vector<Color> m_colors;
};

#endif  // LIB_BMP_H_