/****************************************************************************
**
** Copyright (C) 2009 by user *
** user@greenphonesdk *
**
** Contact: Qt Extended Information (info@qtextended.org)
**
** This file may be used under the terms of the GNU General Public License
** version 2.0 as published by the Free Software Foundation and appearing
** in the file LICENSE.GPL included in the packaging of this file.
**
** Please review the following information to ensure GNU General Public
** Licensing requirements will be met:
**     http://www.fsf.org/licensing/licenses/info/GPLv2.html.
**
****************************************************************************/

#include "audiodialog.h"

AudioDialog::AudioDialog(QString filename, QWidget *parent, Qt::WFlags f)
    : QWidget(parent, f)
{
    // initialize the dialog
    setupUi(this);
    player = new PlayAudioThread(filename);
    playing = false;
    audioLength = player->getDuration();
    QString duration = timeToString(audioLength);
    qDebug()<<"ready to play"<<filename<<"duration:"<<duration;
    labelFileName->setText(filename);
    totalTime->setText(duration);
    updatePosition(0,true);

    slider->setMaximum(audioLength);
    connect(player,SIGNAL(currentSec(int)),this,SLOT(updatePosition(int)));

}

void AudioDialog::on_playButton_clicked(){
    

    if(playing){
        player->stop();
        playing=false;
    }
    else {
        player->play();
        playing=true;
    }
    updatePlayButton();
}

void AudioDialog::updatePlayButton(){
    if(playing){
        playButton->setIcon(QIcon("icons/pause.png"));
    }
    else {
        playButton->setIcon(QIcon("icons/play.png"));
    }
}



void AudioDialog::on_stopButton_clicked(){
    player->stop();
    playing=false;
    updatePosition(0,true);
    player->setOffset(0);
    updatePlayButton();
}

void AudioDialog::on_rewindButton_clicked(){
	if(playing) player->stop();
	int newOffset = player->getOffset() - audioLength/10;
	if(newOffset<0) newOffset=0;
	qDebug() << "rewind pressed, old offset:" << player->getOffset() << "new offset:" << newOffset;
	slider->setSliderDown(true);
	slider->setSliderPosition(newOffset);
	slider->setSliderDown(false);
	if(playing) player->play();
}

void AudioDialog::on_forwardButton_clicked(){
	if(playing) player->stop();
	int newOffset = player->getOffset() + audioLength/10;
	qDebug() << "rewind pressed, old offset:" << player->getOffset() << "new offset:" << newOffset;
	if(newOffset>=audioLength){
		endReached();
		return;
	}
	slider->setSliderDown(true);
	slider->setSliderPosition(newOffset);
	slider->setSliderDown(false);
	if(playing) player->play();
}

void AudioDialog::on_slider_valueChanged(int value){
    if(playing && !slider->isSliderDown()) return;
    qDebug()<<"slider moved to"<<value;
    player->setOffset(value);
    elapsedTime->setText(timeToString(value));
    remainingTime->setText(timeToString(audioLength-value));
}

void AudioDialog::on_slider_sliderPressed(){
	if(playing) player->stop();
}

void AudioDialog::on_slider_sliderReleased(){
	if(playing) player->play();
}



void AudioDialog::updatePosition(int time, bool force){
    qDebug()<<"updatePosition"<<time;
    if(playing||force){
        elapsedTime->setText(timeToString(time));
        remainingTime->setText(timeToString(audioLength-time));
        slider->setSliderPosition(time);
    }
    else {
        qDebug()<<"    ignored signal";
    }
}

QString AudioDialog::timeToString(int time){
    int min = time/600;
    int sec = (time/10)%60;
    QString sMin, sSec;
    if(min<10) sMin = "0";
    if(sec<10) sSec = "0";
    sMin+=QString::number(min);
    sSec+=QString::number(sec);
    return sMin+":"+sSec;
}

void AudioDialog::endReached(){
    playing=false;
    updatePlayButton();
    player->setOffset(0);
	slider->setSliderPosition(0);
}

void AudioDialog::on_saveButton_clicked(){

    emit saveOffset(player->getOffset());
    close();

}
void AudioDialog::on_cancelButton_clicked(){

    close();

}

AudioDialog::~AudioDialog()
{
    // Do nothing
    delete player;
}
