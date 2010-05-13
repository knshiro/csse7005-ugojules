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

#include "vibledthread.h"
#include <QtGlobal> 

VibLedThread::VibLedThread(QString hardwareFile,QString name){
	this->hardwareFile=hardwareFile;
	this->name=name;
	timer = new QTimer(this);
	timer->setSingleShot(true);
	connect(timer, SIGNAL(timeout()), this, SLOT(step()));	
	//connect(this, SIGNAL(stopTimer()), timer, SLOT(stop()));	

}


void VibLedThread::setPattern(QList<int> pattern){
	this->pattern=pattern;
}


void VibLedThread::VibLedThread::run()
{
	qDebug()<<"run, pattern.size()="<< pattern.size();
	index=0;
	running=true;
	step();
}

void VibLedThread::step(){
	QFile brightness( hardwareFile + "/brightness");
	brightness.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
	QTextStream out(&brightness);
	if((2*index<pattern.size())&&(running==true)){
		out<<pattern.at(2*index);
		brightness.close();
		index++;
		timer->start(pattern.at(2*index-1));
		qDebug()<<name<<": step"<<index<< "- timer set: " << pattern.at(2*index-1);
	}
	else {
		out<<"0";
		brightness.close();
        emit finished();
		qDebug()<<name<<": stopped at step"<<index;
	}
}

void VibLedThread::stop(){
	qDebug()<<"stopping";
	running=false;
	QFile brightness( hardwareFile + "/brightness");
	brightness.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
	QTextStream out(&brightness);
	out<<"0";
	brightness.close();
}

VibLedThread::~VibLedThread(){
	stop();
}


