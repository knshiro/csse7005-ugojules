#include "playaudiothread.h"
#include <QDir>

PlayAudioThread::PlayAudioThread(QString filename){
    QAudioOutput *audio = new QAudioOutput();
    audio->setFrequency( 11025 );
    audio->setChannels( 1 );
    audio->setBitsPerSample( 16 );
    audio->open( QIODevice::WriteOnly );

    if(filename != NULL && filename != ""){
        loadFile(filename);
    }
}

PlayAudioThread::~PlayAudioThread(){
}

void PlayAudioThread::loadFile(QString filename){

    if(filename.startsWith("/")){
        file = new QFile(filename);
    }
    else{
        QDir dir = QDir::home();
        dir.cd("Documents");
        //qDebug << dir.filePath(filename);
        file = new QFile(dir.filePath(filename));
    }
    if (!file->open(QIODevice::ReadOnly)){
        //qWarning() << "Cannot open the file" << file->fileName());
    }
}

void PlayAudioThread::run(){

}

void PlayAudioThread::stop(){

}
void PlayAudioThread::setOffset(int _offset){
}

void PlayAudioThread::play(int offset){
}
void PlayAudioThread::pauseResume(){
}
int PlayAudioThread::getDuration(){

    return 0;
}

