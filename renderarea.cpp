#include "renderarea.h"

#include <QPainter>

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    interpolationControl=new(Interpolation);
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    movingStep=0;

    isTimerEnabled=false;
    currentSubject=before;
    isShapeShown[before]=false;
    isShapeShown[after]=false;
    isShapeShown[2]=false;

    pointNum[0]=0;
    pointNum[1]=0;
}

void RenderArea::setNumber(int value){
    interpolationControl->setNumber(value);
}

void RenderArea::setSpeed(float value){
    interpolationControl->setSpeed(value);
    if(isTimerEnabled){
        delete timer;
    }

    timer = new QTimer(this);
    isTimerEnabled=true;

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(interpolationControl->getRefreshFreq());
}

void RenderArea::drawShape(){
    if(currentSubject==before){
        isShapeShown[before]=true;
        currentSubject=after;
    }
    else{
        if(isDrawingDone()){
            isShapeShown[after]=true;
        }
    }
    update();
}

void RenderArea::clear(){
    pointsCoord.clear();
    interpolationControl->Clear();
    update();
}

void RenderArea::play(){
    isShapeShown[2]=true;
    interpolationControl->GenIntPos(pointsCoord);
    update();

}

void RenderArea::mousePressEvent(QMouseEvent *event){

    if(!isDrawingDone()){
        float x = event->pos().x();
        float y=event->pos().y();
        pointsCoord.push_back(QPoint((int)x,(int)y));
        pointNum[currentSubject]++;

        update();
    }
}

bool RenderArea::isDrawingDone(){
    return pointNum[before]==pointNum[after]&&pointNum[before]!=0;
}


void RenderArea::paintEvent(QPaintEvent *){

    QPainter painter(this);
    QColor cPoint=QColor(0,0,0);
    painter.setPen(QPen(cPoint,0));

    //points
    for(int i=0;i<pointsCoord.size();i++){
        painter.drawEllipse(pointsCoord[i],5,5);
    }


    //start&end polygons
    QPainterPath path;
    QPolygon polygon[2];
    for(int k=0;k<2;k++){
        if(isShapeShown[k]){
            int idx;
            for(int i=0;i<pointNum[k];i++){
                idx=pointNum[0]*k+i;
                polygon[k].push_back(pointsCoord[idx]);
            }
            idx=pointNum[0]*k+0;
            polygon[k].push_back(pointsCoord[idx]);
        }
        path.addPolygon(polygon[k]);
    }


    //interval pos
    if(isShapeShown[2]){
        path.addPolygon(interpolationControl->GetPolygon(5));
    }

    painter.drawPath(path);

}
