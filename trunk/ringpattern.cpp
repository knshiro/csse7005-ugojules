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

#include "ringpattern.h"
#include <QtGlobal>

RingPattern::RingPattern()
{

}

// load a pattern from a file (.vib or .led)
void addPattern(QString fileName){
	int i;
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	
	// temp list to store pattern as a list
	QList<int> l;
	// scan file, concatenating everything in the list
	while (!file.atEnd()) {
		QString[] line = QString(file.readLine()).replace("\n","").split(",");
		for(i=0;i<line.length();i++)
			l.append(line.at(i));
	}
	// put pattern in the corresponding list (depending on file)
	if(fileName.endsWith(".vib"){
		vibPatterns[fileName]=l;
		qDebug() << "added new vib pattern";
	}
	else {
		ledPatterns[fileName]=l;
		qDebug() << "added new led pattern";
	}

}

void setPattern(QString fileName){
	qDebug() << "setting pattern" << fileName;
	QValueSpaceObject * obj = new QValueSpaceObject("/CSSE4003");
	if(fileName.endsWith(".vib")
		obj->setAttribute("VibPattern",fileName);
	else
		obj->setAttribute("LedPattern",fileName);
}

void playPattern(QString mode){
	
}

void startVibrate(){
	qDebug() << "startVibrate";
	QVibrateAccessoryProvider::setVibrateNow(true);
}

void stopVibrate(){
	qDebug() << "stopVibrate";
	QVibrateAccessoryProvider::setVibrateNow(false);
}

RingPattern::~RingPattern()
{
    // Do nothing for now
}

