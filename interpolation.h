#ifndef INTERPOLATION_H
#define INTERPOLATION_H

using namespace std;

#include <QWidget>
#include <QPoint>
#include <string>
#include <stdio.h>
#include <vector>

class Interpolation
{
public:
    Interpolation();
    int getRefreshFreq();
    void setSpeed(int value);
    void setNumber(int value);
    void GenIntPos(std::vector<QPoint> points);
    void Clear();
    QPolygon GetPolygon(int idx);

private:
    int number;
    int speed;
    int pointNumber;
    enum interpolationModeEnum{linear,vector,clockwise,counterClockwise} interpolationMode;
    void LinearInt(std::vector<QPoint> points);
    void VectorInt(std::vector<QPoint> points);
    std::vector<QPoint> EuclideanToPolar(std::vector<QPoint> points);
    std::vector<QPoint> PolarToEuclidian(std::vector<QPoint> points);
    std::vector<QPoint> intPoints;

};

#endif
