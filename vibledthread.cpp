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

VibLedThread::VibLedThread(QString hardwareFile){
	this->hardwareFile=hardwareFile;
}

void VibLedThread::setPattern(QList<int> pattern){
	this->pattern=pattern;
}


void VibLedThread::VibLedThread::run()
{
	step(-2);
}

void VibLedThread::step(int i){
	i=i+2;
	QFile brightness( hardwareFile + "/brightness");
	brightness.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
	QTextStream out(&brightness);
	if(i<pattern.size()){
		out<<pattern.at(i);
		brightness.close();
		QTimer::singleShot(pattern.at(i+1), this, SLOT(step(i)));
	}
	else {
		out<<"0";
		brightness.close();
	}
}
