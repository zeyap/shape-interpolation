#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <QWaitCondition>
#include <QMutex>
#include <QThread>
#include <QFile>
#include <QReadWriteLock>
#include <QPixmap>
#include <QWidget>
#include <window.h>
#include <Windows.h>


class Snapshot:public QWidget//: public QThread
{
public:
    Snapshot();
    //virtual void run();
    int save(int movingStep,QPixmap pixmap);
    void Refresh();
    void On();

private:
    void SaveImg(QString fpath,QPixmap pixmap);
    int saveProgress;
    QString progressStr;

    SYSTEMTIME sys_time;

};

#endif // SNAPSHOT_H
