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

#ifndef ADDCONTACTDIALOG_H
#define ADDCONTACTDIALOG_H

#include <QtGui>
#include <qtopiaapplication.h>

#include "neophonebookentry.h"
#include "ui_addcontactform.h"

class AddContactDialog : public QWidget, public Ui_AddContactDialog
{
    Q_OBJECT

    public:
        AddContactDialog( QWidget *parent=0, Qt::WFlags f = 0 );
        void setupEdit(NeoPhoneBookEntry *entryToEdit);
        ~AddContactDialog();

    private:
        QString pictureFilePath;
	NeoPhoneBookEntry *editEntry;


    private slots:
	void on_savePushButton_clicked();
	void on_cancelPushButton_clicked();
	void on_browsePushButton_clicked();
	void on_removePushButton_clicked();

    signals:
      void editContact(NeoPhoneBookEntry *editEntry);
      void addContact(NeoPhoneBookEntry *newEntry);

};

#endif

