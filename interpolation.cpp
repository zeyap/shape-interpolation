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

void Interpolation::GenIntPos(std::vector<QPoint> &points){
    switch(interpolationMode){
    case linear:
        points.push_back(LinearInt(points));
        break;
    case vector:
        //VectorInt(points);
        break;
    case clockwise:
        break;
    case counterClockwise:
        break;
    default:
        break;
    }
}

std::vector<QPoint> Interpolation::LinearInt(std::vector<QPoint> points){
    std::vector<QPoint> newPoints;
    float t;
    int pointsNum=points.size()/2;
    QPoint qtemp;
    for(int i=0;i<number;i++){
        t=i*1.0f/number;
        for(int j=0;j<pointsNum;j++){
            qtemp=QPoint((1-t)*points[j].x()+t*points[pointsNum+j].x(),(1-t)*points[j].y()+t*points[pointsNum+j].y());
            newPoints.push_back(qtemp);
        }
    }
    return newPoints;
}

std::vector<QPoint> Interpolation::VectorInt(std::vector<QPoint> points){

    std::vector<QPoint> polarPoints=EuclideanToPolar(points);
    std::vector<QPoint> newPolarPoints=LinearInt(polarPoints);
    return PolarToEuclidian(newPolarPoints);

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
            polarPoints[j].push_back(QPoint(std::sqrt(x*x+y*y)*scale,std::atan2(y,x)*scale));
        }
    }
    return polarPoints;
}

std::vector<QPoint> Interpolation::PolarToEuclidian(std::vector<QPoint> points){
    std::vector<QPoint> euclideanPoints;

    int pointsNum=points.size();
    int r,t;
    for(int i=0;i<pointsNum;i++){
        r=points[i].x();
        t=points[i].y();
        euclideanPoints.push_back(QPoint(r*std::cos(t),r*std::sin(t)));
    }

    return euclideanPoints;
}
