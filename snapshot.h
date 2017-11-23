#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <QFile>
#include <QPixmap>
#include <QWidget>
#include "CAviFile/AviFile.h"
QT_BEGIN_NAMESPACE
Q_GUI_EXPORT HBITMAP qt_pixmapToWinHBITMAP(
    const QPixmap &p, int hbitmapFormat = 0);

class Snapshot:public QWidget//: public QThread
{
public:
    Snapshot();
    //virtual void run();
    int save(int movingStep,QPixmap pixmap);
    void On();

private:
    void SaveImg(QString fpath,QPixmap pixmap);
    void Refresh();
    int saveProgress;
    void ImgToAvi();
    CAviFile* aviFile;

};

#endif // SNAPSHOT_H
