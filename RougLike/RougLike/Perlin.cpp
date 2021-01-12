#include "Perlin.h"

Perlin::Perlin() {
    rand_offset = rand()%10;
}

float Perlin::Lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}

float Perlin::QunticCurve(float t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

std::vector<float> Perlin::GetPseudoRandomGradientVector(int x, int y)
{
    int v = ((x * x * y + y * y * x) * rand_offset + rand_offset )% 4;

    switch (v)
    {
    case 0:  return std::vector<float> {  1, 0 };
    case 1:  return std::vector<float> { -1, 0 };
    case 2:  return std::vector<float> {  0, 1 };
    default: return std::vector<float> {  0, -1 };
    }
}

float Perlin::Dot(std::vector<float> a, std::vector<float> b)
{
    return a[0] * b[0] + a[1] * b[1];
}

float Perlin::Noise(float fx, float fy)
{
    fx /= 4;
    fy /= 4;
    // сразу находим координаты левой верхней вершины квадрата
    int left = (int)fx;
    int top = (int)fy;

    // а теперь локальные координаты точки внутри квадрата
    float pointInQuadX = fx - left;
    float pointInQuadY = fy - top;

    // извлекаем градиентные векторы для всех вершин квадрата:
    std::vector<float> topLeftGradient = GetPseudoRandomGradientVector(left, top);
    std::vector<float> topRightGradient = GetPseudoRandomGradientVector(left + 1, top);
    std::vector<float> bottomLeftGradient = GetPseudoRandomGradientVector(left, top + 1);
    std::vector<float> bottomRightGradient = GetPseudoRandomGradientVector(left + 1, top + 1);

    // вектора от вершин квадрата до точки внутри квадрата:
    std::vector<float> distanceToTopLeft = std::vector<float>{ pointInQuadX, pointInQuadY };
    std::vector<float> distanceToTopRight = std::vector<float>{ pointInQuadX - 1, pointInQuadY };
    std::vector<float> distanceToBottomLeft = std::vector<float>{ pointInQuadX, pointInQuadY - 1 };
    std::vector<float> distanceToBottomRight = std::vector<float>{ pointInQuadX - 1, pointInQuadY - 1 };

    // считаем скалярные произведения между которыми будем интерполировать
/*
 tx1--tx2
  |    |
 bx1--bx2
*/
    float tx1 = Dot(distanceToTopLeft, topLeftGradient);
    float tx2 = Dot(distanceToTopRight, topRightGradient);
    float bx1 = Dot(distanceToBottomLeft, bottomLeftGradient);
    float bx2 = Dot(distanceToBottomRight, bottomRightGradient);

    // готовим параметры интерполяции, чтобы она не была линейной:
    pointInQuadX = QunticCurve(pointInQuadX);
    pointInQuadY = QunticCurve(pointInQuadY);

    // собственно, интерполяция:
    float tx = Lerp(tx1, tx2, pointInQuadX);
    float bx = Lerp(bx1, bx2, pointInQuadX);
    float tb = Lerp(tx, bx, pointInQuadY) + 1;

    // возвращаем результат:
    return 1/tb;
}