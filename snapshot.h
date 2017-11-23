#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <QWaitCondition>
#include <QMutex>
#include <QThread>
#include <QFile>
#include <QReadWriteLock>
#include <QPixmap>
#include <QWidget>


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

};

#endif // SNAPSHOT_H
