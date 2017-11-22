#include "renderarea.h"

#include <QPainter>

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    interpolationControl=new(Interpolation);
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    modeTemp=0;
    Refresh();

}

void RenderArea::Refresh(){
    movingStep=0;

    isTimerEnabled=false;
    currentSubject=before;
    isShapeShown[before]=false;
    isShapeShown[after]=false;
    isShapeShown[2]=false;

    pointNum[0]=0;
    pointNum[1]=0;
    numberTemp=10;

    SetTimer();
    interpolationControl->Clear();
}

void RenderArea::setNumber(int value){
    numberTemp=value;
}

void RenderArea::setSpeed(float value){
    interpolationControl->setSpeed(value);
    SetTimer();
}

void RenderArea::SetTimer(){
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
    Refresh();
    pointsCoord.clear();
    update();
}

void RenderArea::changeMode(int mode){
    modeTemp=mode;
}

void RenderArea::play(){
    movingStep=0;
    interpolationControl->setNumber(numberTemp);
    interpolationControl->setMode(modeTemp);
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
    QColor cPoint=cActive;
    QColor cLine=cActive;
    QColor cIntLine=cActive;

    if(isShapeShown[2]){
        cPoint=cInactive;
        cLine=cInactive;
        cIntLine=cActive;
    }

    QPainter painter(this);

    painter.setPen(QPen(cPoint,0));

    //points
    for(int i=0;i<pointsCoord.size();i++){
        painter.drawEllipse(pointsCoord[i],5,5);
    }

    painter.setPen(QPen(cLine,0));

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
    painter.drawPath(path);


    painter.setPen(QPen(cIntLine,0));

    //interval pos
    if(isShapeShown[2]){
        QPainterPath path2;
        path2.addPolygon(interpolationControl->GetPolygon(movingStep));
        painter.drawPath(path2);
    }



}
