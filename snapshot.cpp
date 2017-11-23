#include "snapshot.h"

Snapshot::Snapshot()
{
    Refresh();
}

void Snapshot::Refresh(){
    saveProgress=-1;
}

void Snapshot::On(){
    saveProgress=0;
}
int Snapshot::save(int movingStep,QPixmap pixmap){
    //void Snapshot::run(){
    if(saveProgress>-1){
        QString fname=QString::number(movingStep,10)+".png";
        if(!QFile::exists(fname)){
            SaveImg(fname,pixmap);
            saveProgress++;
        }
    }
    return saveProgress;
}

void Snapshot::SaveImg(QString fpath,QPixmap pixmap){

    //QPixmap pixmap = QPixmap::grabWidget(this);//QWidget::grab();
    pixmap.save(fpath);

}
