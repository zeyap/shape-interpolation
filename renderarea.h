#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QWidget>
#include <QMouseEvent>
#include<QImage>
#include<QLabel>
#include<QTimer>

#include <vector>
#include<string>
#include<interpolation.h>
#include <snapshot.h>

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    Interpolation* interpolationControl;
    Snapshot* snapshot;
    RenderArea(QWidget *parent = 0);
    int height=100;
    int width=100;
    std::vector<QPoint> pointsCoord;

public slots:
    void setNumber(int value);
    void setSpeed(float value);

    void drawShape();
    void clear();
    void play();
    void changeMode(int mode);
    void save();

    void UpdateAndShootScreen();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *) override;
    void redrawIntPoints();
    bool isDrawingDone();
    void SetTimer();
    void Refresh();

private:

    int movingStep;
    QTimer *timer;
    int numberTemp;
    int modeTemp;
    bool isTimerEnabled;
    enum currentSubjectEnum{before, after, trans} currentSubject;
    bool isShapeShown[3];
    int pointNum[2];
    QColor cActive=QColor(0,200,100);
    QColor cInactive=QColor(250,200,0);

};

#endif // RENDERAREA_H
