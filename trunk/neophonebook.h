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
#include <QByteArray>

#include <qtopia/qtopiaapplication.h>
#include "neophonebookentry.h"

class NeoPhoneBook : public QObject
{
    Q_OBJECT

    public:	
        NeoPhoneBook();
        int getNumEntries();
        int findIndex(QString const &name);
        void addEntry(NeoPhoneBookEntry *newEntry);
        void replaceEntry(int index, NeoPhoneBookEntry *newEntry);
        void deleteEntry(int index);
        void loadPhoneBook();
        void savePhoneBook();
        void clearPhoneBook();
        NeoPhoneBookEntry* getElementAt(int index);
		void writePhoneBookIn(QByteArray &out);
        ~NeoPhoneBook();

    private:
        QList<NeoPhoneBookEntry*> phoneList;
        QString fileName;
		int recFindIndex(QString const &name,int start, int end);

};

#endif

