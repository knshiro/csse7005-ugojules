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

#ifndef VIEWCONTACTDIALOG_H
#define VIEWCONTACTDIALOG_H

#include <QtGui>
#include <qtopiaapplication.h>

#include "neophonebookentry.h"
#include "phonebookdialog.h"
#include "ui_viewcontactform.h"

class ViewContactDialog : public QWidget, public Ui_ViewContactDialog
{
    Q_OBJECT

    public:
        ViewContactDialog(PhoneBookDialog* phoneBookDialog, int indexEntry, QWidget *parent=0, Qt::WFlags f = 0 );
        ~ViewContactDialog();
        
            
    private slots:
	void on_editButton_clicked();
	void on_deleteButton_clicked();
	void on_callButton_clicked();

    private:
	PhoneBookDialog* phoneBookDialog;
	int indexEntry;

    signals:
	void deleteContact(int index);
	void callContact(int index);
    void stopCall();
};

#endif

