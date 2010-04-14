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
#include "phonebookdialog.h"


ViewContactDialog::ViewContactDialog(PhoneBookDialog *phoneBookDialog, int indexEntry, QWidget *parent, Qt::WFlags f)
    : QWidget(parent, f)
{
	this->phoneBookDialog=phoneBookDialog;
	this->indexEntry=indexEntry;
	setupUi(this);
	NeoPhoneBookEntry * entry = phoneBookDialog->myPhoneBook->getElementAt(indexEntry);
	nameLabel->setText(entry->getContactName());
	numberLabel->setText(entry->getPhoneNumber());
	QPixmap * pic = new QPixmap();
	pic->load(entry->getPictureFilePath());
	pictureLabel->setPixmap(*pic);

}

ViewContactDialog::~ViewContactDialog()
{
    // Do nothing
}

void ViewContactDialog::on_editButton_clicked(){
	AddContactDialog *myAddContactDialog = new AddContactDialog();
        myAddContactDialog->setAttribute(Qt::WA_DeleteOnClose);
	myAddContactDialog->setupEdit(phoneBookDialog->myPhoneBook->getElementAt(indexEntry));
        myAddContactDialog->showMaximized();
	QObject::connect( myAddContactDialog, SIGNAL(addContact(NeoPhoneBookEntry *)), phoneBookDialog, SLOT(addContact(NeoPhoneBookEntry *) ));
	QObject::connect( myAddContactDialog, SIGNAL(editContact(NeoPhoneBookEntry *)), phoneBookDialog, SLOT(replaceContact(NeoPhoneBookEntry *) ));
	close();
}

void ViewContactDialog::on_deleteButton_clicked(){
	emit deleteContact(indexEntry);
	close();
}

void ViewContactDialog::on_callButton_clicked(){

}
