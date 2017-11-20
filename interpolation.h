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
    void GenIntPos(vector<QPoint>& points);
private:
    int number;
    int speed;
    enum interpolationModeEnum{linear,vector,clockwise,counterClockwise} interpolationMode;
    std::vector<QPoint> LinearInt(std::vector<std::vector<QPoint>> points);
    std::vector<QPoint> VectorInt(std::vector<std::vector<QPoint>> points);
    std::vector<QPoint> EuclideanToPolar(std::vector<QPoint> points);
    std::vector<QPoint> PolarToEuclidian(std::vector<QPoint> points);

};

#endif
