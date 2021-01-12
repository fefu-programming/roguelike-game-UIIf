#pragma once
#include <vector>

class Perlin
{
private:
    int rand_offset;
    static float Lerp(float a, float b, float t);
    static float QunticCurve(float t);
    std::vector<float> GetPseudoRandomGradientVector(int x, int y);
    static float Dot(std::vector<float> a, std::vector<float> b);
public:
    Perlin();
    float Noise(float fx, float fy);
};