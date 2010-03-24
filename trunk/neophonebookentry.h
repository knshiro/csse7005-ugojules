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
        NeoPhoneBookEntry(QString name, QString number, QString contactEmail = "", QString path = "");
        QString getContactName();
        QString getPhoneNumber();
        QString getContactEmail();
        QString getPictureFilePath();
        void setContactName(QString name);
        void setPhoneNumber(QString number);
        void setContactEmail(QString email);
        void setPictureFilePath(QString path);
        ~NeoPhoneBookEntry();

    private:
        QString contactName;
        QString phoneNumber;
        QString contactEmail;
        QString pictureFilePath;
};

#endif

