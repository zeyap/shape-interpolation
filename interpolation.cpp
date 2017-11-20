#include "interpolation.h"

Interpolation::Interpolation()
{
    number=10;
    speed=100;
    interpolationMode=linear;
}

int Interpolation::getRefreshFreq(){
    return 5/(speed*number);
}
void Interpolation::setSpeed(int value){
    speed=value;
}

void Interpolation::setNumber(int value){
    number=value;
}

void Interpolation::Clear(){
    intPoints.clear();
}

void Interpolation::GenIntPos(std::vector<QPoint> points){
    pointNumber=points.size()/2;
    switch(interpolationMode){
    case linear:
        LinearInt(points);
        break;
    case vector:
        VectorInt(points);
        break;
    case clockwise:
        break;
    case counterClockwise:
        break;
    default:
        break;
    }
}

void Interpolation::LinearInt(std::vector<QPoint> points){
    float t;
    QPoint qtemp;
    for(int i=0;i<number;i++){
        t=i*1.0f/number;
        for(int j=0;j<pointNumber;j++){
            qtemp=QPoint((1-t)*points[j].x()+t*points[pointNumber+j].x(),(1-t)*points[j].y()+t*points[pointNumber+j].y());
            intPoints.push_back(qtemp);
        }
    }
}

void Interpolation::VectorInt(std::vector<QPoint> points){

    std::vector<QPoint> polarPoints=EuclideanToPolar(points);
    LinearInt(polarPoints);
    std::vector<QPoint> newPoints=PolarToEuclidian(intPoints);
    intPoints.swap(newPoints);
    newPoints.clear();

}

std::vector<QPoint> Interpolation::EuclideanToPolar(std::vector<QPoint> points){
    std::vector<QPoint> polarPoints;
    int pointsNum=points.size();
    int x,y;
    float scale=100.0f;
    for(int j=0;j<2;j++){
        for(int i=0;i<pointsNum;i++){
            x=points[j*pointsNum+i].x();
            y=points[j*pointsNum+i].y();
            polarPoints.push_back(QPoint(std::sqrt(x*x+y*y)*scale,std::atan2(y,x)*scale));
        }
    }
    return polarPoints;
}

std::vector<QPoint> Interpolation::PolarToEuclidian(std::vector<QPoint> points){
    std::vector<QPoint> euclideanPoints;
    int pointsNum=points.size();
    float r,t;
    float scale=100.0f;
    for(int i=0;i<pointsNum;i++){
        r=points[i].x()/scale;
        t=points[i].y()/scale;
        euclideanPoints.push_back(QPoint(r*std::cos(t),r*std::sin(t)));
    }
    return euclideanPoints;
}

QPolygon Interpolation::GetPolygon(int idx){
    QPolygon newPolygon;
    for(int i=0;i<pointNumber;i++){
        newPolygon.push_back(intPoints[idx*pointNumber+i]);
    }
    newPolygon.push_back(intPoints[idx*pointNumber+0]);
    return newPolygon;
}
