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
    int getRefreshInterval();
    void setSpeed(int value);
    void setNumber(int value);
    int getNumber(){
        return number;
    }
    void GenIntPos(std::vector<QPoint> points);
    void Clear();
    QPolygon GetPolygon(int& idx);
    void setMode(int mode);

private:
    int number;
    int pointNumber;
    int speed;
    void LinearInt(std::vector<QPoint> points);
    void VectorInt(std::vector<QPoint> points);
    std::vector<QPoint> EuclideanToPolar(std::vector<QPoint> points);
    std::vector<QPoint> PolarToEuclidian(std::vector<QPoint> points);
    void GenOrigins(std::vector<QPoint> points);
    std::vector<QPoint> intPoints;
    std::vector<QPoint> origins;
    enum interpolationModeEnum{linear,vector,clockwise,counterClockwise} interpolationMode;

};

#endif
