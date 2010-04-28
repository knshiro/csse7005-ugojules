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
	// prepare threads
	blueThread=new VibLedThread("/sys/class/leds/gta02-power:blue");
	orangeThread=new VibLedThread("/sys/class/leds/gta02-power:orange");
	redThread=new VibLedThread("/sys/class/leds/gta02-aux:red");
	vibThread=new VibLedThread("/sys/class/leds/neo1973:vibrator");	

	// create pattern "Pulse" for vib
	QList<int> vibPulse;
	int i;
	for(i=0;i<13;i++)
		vibPulse << 255 << 250 << 0 << 500;
	vibPatterns["Pulse"]=vibPulse;

	// create pattern "Pulse" for leds
	QList<int> ledPulse;
	for(i=0;i<13;i++)
		ledPulse << 1 << 1 << 1 << 255 << 250 << 1 << 1 << 1 << 0 << 500;
	ledPatterns["Pulse"]=ledPulse;
	
	
}

// load a pattern from a file
void RingPattern::addPattern(QString fileName, DeviceType type){
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
	// put pattern in the corresponding list (depending on type of device)
	switch(type){
	case VIB:
		vibPatterns[fileName]=l;
		qDebug() << "added new vib pattern";
		break;
	case LED:
		ledPatterns[fileName]=l;
		qDebug() << "added new led pattern";
		break;
	default:
		qDebug() << "invalide type";
	}

}

void RingPattern::setPattern(QString fileName, DeviceType type){
	qDebug() << "setting pattern" << fileName;
	QValueSpaceObject * obj = new QValueSpaceObject("/CSSE4003");
	switch(type){
	case VIB:
		obj->setAttribute("VibPattern",fileName);
		break;
	case LED:
		obj->setAttribute("LedPattern",fileName);
		break;
	default:
		break;
	}
}

void RingPattern::playPattern(){
	qDebug() << ">>>> play pattern";
	int i;
	QList<int> blueLed;
	QList<int> orangeLed;
	QList<int> redLed;
	QList<int> vib;

	// read space variables
	QValueSpaceItem *ledsP = new QValueSpaceItem("/CSSE4003/LedPattern");
	QValueSpaceItem *vibP = new QValueSpaceItem("/CSSE4003/VibPattern");

	// if led pattern is "Random", generate a random pattern
	if(ledsP->value().equals("Random")) {
		blueLed = generateRandomPattern();
		orangeLed = generateRandomPattern();
		redLed = generateRandomPattern();
	}
	else {
		// split the leds global pattern into 3 patterns (1 for each led)
		QList<int> l = ledPatterns[ledsP->value()];
		for(i=0;i<l.size();i+=5){
			blueLed.append(l[i]*l[i+3]); blueLed.append(l[i+4]);
			orangeLed.append(l[i+1]*l[i+3]); orangeLed.append(l[i+4]);
			redLed.append(l[i+2]*l[i+3]); redLed.append(l[i+4]);
		}
	}

	// if vib pattern is "Random", generate a random one
	if(vibP->value().equals("Random")) {
		vib = generateRandomPattern();
	}
	else {
		vib = vibPatterns[vibP->value()];
	}

	// set patterns in threads
	blueThread.setPattern(blueLed);
	orangeThread.setPattern(orangeLed);
	redThread.setPattern(redLed);
	vibThread.setPattern(vib);

	qDebug() << "  starting pattern (vib:" << vibP->value() << ", leds:" << ledsP->value() << ")" ;

	// start the threads
	blueThread.start();
	orangeThread.start();
	redThread.start();
	vibThread.start();

	qDebug() << "  pattern started";
}

QList<int> RingPattern::generateRandomPattern(){
	QList<int> l;
	int strength, duration, delay;
	for(int i =0;i<10;i++){
		strength = 100+(qrand()*155)/RAND_MAX;
		duration = 50+(qrand()*1950)/RAND_MAX;
		delay = 50+(qrand()*450)/RAND_MAX;
		l << strength << duration << 0 << delay;
	}
	return l;
}


void RingPattern::startVibrate(){
	qDebug() << ">>>> startVibrate";
	playPattern();
	qDebug() << "<<<< startVibrate";
}

void RingPattern::stopVibrate(){
	qDebug() << ">>>> stopVibrate";
	blueThread.terminate();
	orangeThread.terminate();
	redThread.terminate();
	vibThread.terminate();
	qDebug() << "<<<< stopVibrate";
}

RingPattern::~RingPattern()
{
    // Do nothing for now
}

