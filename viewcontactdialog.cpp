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

#include "viewcontactdialog.h"

ViewContactDialog::ViewContactDialog(NeoPhoneBookEntry* entry, QWidget *parent, Qt::WFlags f)
    : QWidget(parent, f)
{
	setupUi(this);
	nameLabel->setText(entry->getContactName());
	numberLabel->setText(entry->getPhoneNumber());

}

ViewContactDialog::~ViewContactDialog()
{
    // Do nothing
}

void ViewContactDialog::on_editButton_clicked(){
	/*AddContactDialog *myAddContactDialog = new AddContactDialog();
	myAddContactDialog->setupEdit
        myAddContactDialog->setAttribute(Qt::WA_DeleteOnClose);
        myAddContactDialog->showMaximized();*/
}

void ViewContactDialog::on_deleteButton_clicked(){

}

void ViewContactDialog::on_callButton_clicked(){

}
