#include "interpolation.h"
#define PI 3.14f;

Interpolation::Interpolation()
{
    number=10;
    pointNumber=0;
    speed=1;
    interpolationMode=vector;
}

int Interpolation::getRefreshFreq(){
    return 5000/(speed*number);
}
void Interpolation::setSpeed(int value){
    speed=value;
}

void Interpolation::setNumber(int value){
    number=value;
}

void Interpolation::Clear(){
    intPoints=std::vector<QPoint>(number*30,QPoint(0,0));
    origins=std::vector<QPoint>(number,QPoint(0,0));
}

void Interpolation::GenIntPos(std::vector<QPoint> points){
    Clear();
    pointNumber=points.size()/2;
    switch(interpolationMode){
    case linear:
        LinearInt(points);
        break;
    case vector:
        VectorInt(points);
        break;
    case clockwise:
        VectorInt(points);
        break;
    case counterClockwise:
        VectorInt(points);
        break;
    default:
        break;
    }
}

void Interpolation::LinearInt(std::vector<QPoint> points){
    float t;
    for(int i=0;i<number;i++){
        t=i*1.0f/number;
        for(int j=0;j<pointNumber;j++){
            intPoints[pointNumber*i+j]=QPoint((1-t)*points[j].x()+t*points[pointNumber+j].x(),(1-t)*points[j].y()+t*points[pointNumber+j].y());
        }
    }
}

void Interpolation::GenOrigins(std::vector<QPoint> points){
    QPoint start,end;
    start=points[0];
    end=points[pointNumber];
    float t;
    for(int i=0;i<number;i++){
        t=i*1.0f/number;
        origins[i]=QPoint((1-t)*start.x()+t*end.x(),(1-t)*start.y()+t*end.y());
    }
}

void Interpolation::VectorInt(std::vector<QPoint> points){

    GenOrigins(points);
    std::vector<QPoint> polarPoints=EuclideanToPolar(points);
    LinearInt(polarPoints);
    std::vector<QPoint> newPoints=PolarToEuclidian(intPoints);
    intPoints.swap(newPoints);
    newPoints.clear();

}

std::vector<QPoint> Interpolation::EuclideanToPolar(std::vector<QPoint> points){
    std::vector<QPoint> polarPoints;
    std::vector<QPoint> originsAtEnds;

    int pointsNum=points.size()/2;

    int x,y;
    float r,t;
    float scale=100.0f;
    for(int j=0;j<2;j++){
        originsAtEnds.push_back(points[pointsNum*j]);
        for(int i=0;i<pointsNum;i++){
            x=points[j*pointsNum+i].x()-originsAtEnds[j].x();
            y=points[j*pointsNum+i].y()-originsAtEnds[j].y();
            r=std::sqrt(x*x+y*y);
            t=std::atan2(y,x);
            if(j==1){
                if(interpolationMode==clockwise){
                    if(t*scale<polarPoints[i].y())
                        t+=2*PI;
                }else if(interpolationMode==counterClockwise){
                    if(t*scale>polarPoints[i].y())
                        t-=2*PI;
                }
            }
            polarPoints.push_back(QPoint(r*scale,t*scale));
        }
    }
    return polarPoints;
}

std::vector<QPoint> Interpolation::PolarToEuclidian(std::vector<QPoint> points){
    std::vector<QPoint> euclideanPoints;

    float r,t;
    float scale=100.0f;
    for(int i=0;i<pointNumber*number;i++){
        r=points[i].x()/scale;
        t=points[i].y()/scale;
        euclideanPoints.push_back(QPoint(r*std::cos(t)+origins[i/pointNumber].x(),r*std::sin(t)+origins[i/pointNumber].y()));
    }
    return euclideanPoints;
}

QPolygon Interpolation::GetPolygon(int& idx){
    QPolygon newPolygon;
    idx++;
    if(idx>=number)idx=0;
    for(int i=0;i<pointNumber;i++){
        newPolygon.push_back(intPoints[idx*pointNumber+i]);
    }
    newPolygon.push_back(intPoints[idx*pointNumber+0]);
    return newPolygon;
}

void Interpolation::setMode(int mode){
    if(mode==0){
        interpolationMode=linear;
    }else if(mode==1){
        interpolationMode=vector;
    }else if(mode==2){
        interpolationMode=clockwise;
    }else{
        interpolationMode=counterClockwise;
    }
}
