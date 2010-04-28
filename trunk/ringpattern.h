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

#ifndef RINGPATTERN_H
#define RINGPATTERN_H
#include <QtGui>
#include <qtopia/qtopiaapplication.h>

class RingPattern : public QObject
{
    Q_OBJECT

    public:	
		RingPattern();
		void addPattern(QString fileName);
		void setPattern(QString fileName);
		void playPattern(QString mode);
		void startVibrate();
		void stopVibrate();
        ~RingPattern();

    private:
		QMap<QString,QList<int>> vibPatterns;
		QMap<QString,QList<int>> ledPatterns;
};

#endif

