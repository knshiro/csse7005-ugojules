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
}

NeoPhoneBookEntry::NeoPhoneBookEntry(QString name, QString number, QString email, QString path)
{
    contactName = name;
    phoneNumber = number;
    contactEmail = email;
    pictureFilePath = path;
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

NeoPhoneBookEntry::~NeoPhoneBookEntry()
{
    // Do nothing for now
}

