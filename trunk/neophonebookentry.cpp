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

#include "neophonebookentry.h"

NeoPhoneBookEntry::NeoPhoneBookEntry()
{
    contactName = "";
    phoneNumber = "";
    contactEmail = "";
    pictureFilePath = "";
    ringtone = "Default";
    vibrationPattern = "Pulse";
    ledPattern = "Pulse";
    ringOption = 0;
    ringOffset = 0;
}

NeoPhoneBookEntry::NeoPhoneBookEntry(QString name, QString number, QString email, QString path, 
	QString tone, QString vpattern, QString lpattern, int option, int offset)
{
    contactName = name;
    phoneNumber = number;
    contactEmail = email;
    pictureFilePath = path;
    ringtone = tone;
    vibrationPattern = vpattern;
    ledPattern = lpattern;
    ringOption = option;
	ringOffset = offset;
}



QString NeoPhoneBookEntry::getContactName()
{
    return contactName;
}

QString NeoPhoneBookEntry::getPhoneNumber()
{
    return phoneNumber;
}

QString NeoPhoneBookEntry::getContactEmail()
{
    return contactEmail;
}

QString NeoPhoneBookEntry::getPictureFilePath()
{
    return pictureFilePath;
}

QString NeoPhoneBookEntry::getRingtone()
{
    return ringtone;
}

QString NeoPhoneBookEntry::getVibrationPattern()
{
    return vibrationPattern;
}

QString NeoPhoneBookEntry::getLedPattern()
{
    return ledPattern;
}

int NeoPhoneBookEntry::getRingOption()
{
    return ringOption;
}

int NeoPhoneBookEntry::getRingOffset()
{
    return ringOffset;
}

void NeoPhoneBookEntry::setContactName(QString name)
{
    contactName = name;
}

void NeoPhoneBookEntry::setPhoneNumber(QString number)
{
    phoneNumber = number;
}

void NeoPhoneBookEntry::setContactEmail(QString email)
{
    contactEmail = email;
}

void NeoPhoneBookEntry::setPictureFilePath(QString path)
{
    pictureFilePath = path;
}

void NeoPhoneBookEntry::setRingTone(QString tone)
{
    ringtone = tone;
}

void NeoPhoneBookEntry::setVibrationPattern(QString vpattern)
{
    vibrationPattern = vpattern;
}

void NeoPhoneBookEntry::setLedPattern(QString lpattern)
{
    ledPattern = lpattern;
}

void NeoPhoneBookEntry::setRingOption(int option)
{
    ringOption = option;
}

void NeoPhoneBookEntry::setRingOffset(int offset)
{
    ringOffset = offset;
}

NeoPhoneBookEntry::~NeoPhoneBookEntry()
{
    // Do nothing for now
}

