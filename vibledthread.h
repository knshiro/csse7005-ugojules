 
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

#ifndef VIBLEDTHREAD_H
#define VIBLEDTHREAD_H
#include <QtGui>
#include <qtopia/qtopiaapplication.h>

class VibLedThread : public QThread
 {
    Q_OBJECT


	public:
		VibLedThread(QString hardwareFile,QString name="");
    	void run();
		void setPattern(QList<int> pattern);
		void stop();
		~VibLedThread();

	private:
		QString hardwareFile;
		QList<int> pattern;
		int index;
		QTimer *timer;
		bool running;
		QString name;

	public slots:
		void step();
	
    signals:
        void finished();
 };

#endif
