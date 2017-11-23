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
    aviFile=new CAviFile("output.avi",0,10);
}
int Snapshot::save(int movingStep,QPixmap pixmap){
    //void Snapshot::run(){
    if(saveProgress>-1){
        QString fname=QString::number(movingStep,10)+".bmp";
        if(!QFile::exists(fname)){
            SaveImg(fname,pixmap);
            saveProgress++;
        }
    }
    return saveProgress;
}

void Snapshot::SaveImg(QString fpath,QPixmap pixmap){

    //pixmap.save(fpath);

    HBITMAP hBmp = qt_pixmapToWinHBITMAP(pixmap, 2);
    HRESULT res=aviFile->AppendNewFrame(hBmp);
}

void Snapshot::ImgToAvi(){

}
