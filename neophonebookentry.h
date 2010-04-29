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

#ifndef NEOPHONEBOOKENTRY_H
#define NEOPHONEBOOKENTRY_H

#include <QString>

class NeoPhoneBookEntry
{
    
    public:
        NeoPhoneBookEntry();
        //NeoPhoneBookEntry(QString name, QString number);
        NeoPhoneBookEntry(QString name, QString number, QString contactEmail = "", QString path = "", 
		QString tone="Default", QString vpattern="Pulse", QString lpattern = "Pulse", int option = 0);
        QString getContactName();
        QString getPhoneNumber();
        QString getContactEmail();
        QString getPictureFilePath();
	QString getRingtone();
	QString getVibrationPattern();
	QString getLedPattern();
	int getRingOption();
        void setContactName(QString name);
        void setPhoneNumber(QString number);
        void setContactEmail(QString email);
        void setPictureFilePath(QString path);
	void setRingTone(QString tone);
	void setVibrationPattern(QString vpattern);
	void setLedPattern(QString lpattern);
	void setRingOption(int option);

        ~NeoPhoneBookEntry();

    private:
        QString contactName;
        QString phoneNumber;
        QString contactEmail;
        QString pictureFilePath;
	QString ringtone;
	QString vibrationPattern;
	QString ledPattern;
	int ringOption;
};

#endif

