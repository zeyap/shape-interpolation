#include "snapshot.h"

Snapshot::Snapshot()
{
    Refresh();
}

void Snapshot::Refresh(){
    saveProgress=-1;
    progressStr="";
}

void Snapshot::On(){
    saveProgress=0;
    progressStr="||";
}
int Snapshot::save(int movingStep,QPixmap pixmap){
    //void Snapshot::run(){
    if(saveProgress>-1){
        QString fname = QString::number(movingStep,10)+".png";
        if(!QFile::exists(fname)){
            SaveImg(fname,pixmap);
            saveProgress++;
            progressStr+="||";
            Window::setStatus("wait"+progressStr);
        }
    }
    return saveProgress;
}

void Snapshot::SaveImg(QString fpath,QPixmap pixmap){

    //QPixmap pixmap = QPixmap::grabWidget(this);//QWidget::grab();
    pixmap.save(fpath);

}
