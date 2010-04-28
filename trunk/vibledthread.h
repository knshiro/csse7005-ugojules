 
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

#ifndef NEOPHONEBOOK_H
#define NEOPHONEBOOK_H
#include <QtGui>
#include <qtopia/qtopiaapplication.h>

class VibLedThread : public QThread
 {
    Q_OBJECT


	public:
		VibLedThread(QString hardwareFile);
    	void run();
		void setPattern(QList<int> pattern);

	private:
		QString hardwareFile;
		QList pattern;

	slots:
		void step(int i);
 };
