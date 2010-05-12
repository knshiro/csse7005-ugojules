/****************************************************************************
**
** This file is part of the Qt Extended Opensource Package.
**
** Copyright (C) 2008 Trolltech ASA.
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

#ifndef PHONEBOOKDIALOG_H
#define PHONEBOOKDIALOG_H
#include "ui_phonebookform.h"
#include "neophonebook.h"
#include "addcontactdialog.h"
#include "ringpattern.h"
#include "playaudiothread.h"
#include <QtGui>


class PhoneBookDialog : public QWidget, public Ui_PhoneBookForm
{
    Q_OBJECT
    public:
        enum Update_Types { UP, DOWN, REFRESH, DELETE_LAST };
    

        PhoneBookDialog( QWidget *parent = 0, Qt::WFlags f = 0 );
        void updateScreen(Update_Types);
        void updateContactSlot(int index, QString name, bool selected = false);
        ~PhoneBookDialog();

        NeoPhoneBook *myPhoneBook;
        void loadPatterns();

    private slots:
        void addContact(NeoPhoneBookEntry *newEntry);
        void replaceContact(NeoPhoneBookEntry *newEntry);
        void deleteContact(int index);
		void callContact(int index);
        void stopCall();
		void on_searchLineEdit_textChanged(const QString &text);
		void on_upButton_clicked();
		void on_downButton_clicked();
		void on_selectButton_clicked();
		void on_deleteButton_clicked();

    private:
        int selection;
        QList<int> slotIndex;
		QList<QLabel*> contactSlots;
		RingPattern *ringpattern;
		PlayAudioThread * audioThread;
};

#endif

