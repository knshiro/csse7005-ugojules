#include "playaudiothread.h"
#include <QDir>

PlayAudioThread::PlayAudioThread(QString filename){
    audioOutput = new QAudioOutput();
    file = NULL;
    audioOutput->setFrequency( FREQUENCY );
    audioOutput->setChannels( CHANNELS );
    audioOutput->setBitsPerSample( BITSPERSAMPLE );
    audioOutput->open( QIODevice::WriteOnly );

    if(filename != NULL && filename != ""){
        loadFile(filename);
    }
}

PlayAudioThread::~PlayAudioThread(){
    stop();
    delete audioOutput;
    delete file;
}

bool PlayAudioThread::loadFile(QString filename){
    qDebug() << ">> Load file" << filename;
    
    stop();
    delete file;

    if(filename.startsWith("/")){
        file = new QFile(filename);
    }
    else{
        QDir dir = QDir::home();
        dir.cd("Documents");
        qDebug() << dir.filePath(filename);
        file = new QFile(dir.filePath(filename));
    }
    
    if (!file->open(QIODevice::ReadOnly)){
        qDebug() << "Cannot open the file" << file->fileName();
        return false;
    } else {
        qDebug() << "<< File" << file->fileName() << "loaded";
        return true;
    }
}

void PlayAudioThread::run(){

    char buffer[BYTESPERDS];
    qint64 len;
    active = true;
    qDebug() << ">>Audio Thread started";
    while (active && !file->atEnd()){
        len = file->read(buffer,BYTESPERDS);
        audioOutput->write( buffer,  len );
        qDebug()<<">currentSec"<<file->pos() / BYTESPERDS;
        emit currentSec(file->pos() / BYTESPERDS);
        qDebug()<<"<currentSec"<<file->pos() / BYTESPERDS;
    }
    if(file->atEnd()){
        active = false;
        emit endReached();
    }
    qDebug() << "<<Audio thread return";
}

void PlayAudioThread::stop(){
    qDebug() << "Stop";
    active = false;
    qDebug() << "Start waiting";
    wait(1000);
    qDebug() << "Finished waiting";
}

bool PlayAudioThread::setOffset(int _offset){
    qint64 bytesOffset = 0;
    //stop();

    bytesOffset = _offset * (BYTESPERDS);
    if(file != NULL){
        return file->seek(bytesOffset);
    }
    else {
        return false;
    }
}

int PlayAudioThread::getOffset(){
	return file->pos() / BYTESPERDS;
}

bool PlayAudioThread::play(int offset){
    qDebug() << ">>Play";
    stop();
    qDebug() << "Audio Thread stopped";
    if (file != NULL){
        if (offset >=0){
            if (setOffset(offset)){
                qDebug() << "Offset :" << offset << "sec";
            }
        }
        start();
        return true;
    }
    else {
        qDebug() << "File is NULL !!!";
        return false;
    }
}

void PlayAudioThread::pauseResume(){
}

int PlayAudioThread::getDuration(){
    qint64 fileSize = 0;
    qint64 duration = 0;
    if(file != NULL) {
        qDebug() << "Frequence sur 10" << FREQUENCY/10.0 ;
        qDebug() << "(FREQUENCY/10.0) * CHANNELS * BITSPERSAMPLE/8" << (FREQUENCY/10.0) * CHANNELS * BITSPERSAMPLE/8;
        qDebug() << "File size" << file->size() ;
        fileSize = file->size()/BYTESPERDS;
    }
    duration = fileSize;
    return fileSize;
}

