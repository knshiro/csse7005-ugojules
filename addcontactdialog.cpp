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

#include "addcontactdialog.h"
#include <QImageDocumentSelectorDialog>
AddContactDialog::AddContactDialog(QWidget *parent, Qt::WFlags f)
    : QWidget(parent, f)
{
    // initialize the dialog
    setupUi(this);
    editEntry = NULL;

}

AddContactDialog::~AddContactDialog()
{
    // Do nothing
}

void AddContactDialog::setupEdit(NeoPhoneBookEntry *entryToEdit)
{
    QPixmap picture;
    editEntry = entryToEdit;
    // sets up the UI for edit-mode
    nameLineEdit->setText(entryToEdit->getContactName());
    numberLineEdit->setText(entryToEdit->getPhoneNumber());
    emailLineEdit->setText(entryToEdit->getContactEmail());
    pictureFilePath = entryToEdit->getPictureFilePath();
    qDebug() << "Filename :" << entryToEdit->getPictureFilePath();
    if(entryToEdit->getPictureFilePath() != ""){
      picture = QPixmap(entryToEdit->getPictureFilePath());
      picture = picture.scaled(QSize(pictureLabel->width(),1000),Qt::KeepAspectRatio,Qt::SmoothTransformation);
      pictureLabel->setPixmap(picture);
      removePushButton->setEnabled(true);
    }
}


void AddContactDialog::on_savePushButton_clicked()
{
       qDebug() << ">>>> Save Clicked";
       if(editEntry != NULL){
	 editEntry-> setContactName(nameLineEdit->text());
         editEntry-> setPhoneNumber(numberLineEdit->text());
         editEntry-> setContactEmail(emailLineEdit->text());
	 qDebug() << "Picture path:" << pictureFilePath;
         editEntry-> setPictureFilePath(pictureFilePath);
         emit editContact(editEntry);
       }
       else {
	NeoPhoneBookEntry *newEntry = new NeoPhoneBookEntry(nameLineEdit->text(), numberLineEdit->text(), emailLineEdit->text(),pictureFilePath);
         emit addContact(newEntry);
       }
	close();
}


void AddContactDialog::on_cancelPushButton_clicked()
{
	close();
}
void AddContactDialog::on_removePushButton_clicked()
{
	pictureFilePath = "";
	pictureLabel->setText("No Picture");
	removePushButton->setEnabled(false);

}

void AddContactDialog::on_browsePushButton_clicked()
{
    QImageDocumentSelectorDialog dialog( this );
    QPixmap picture;


    if( QtopiaApplication::execDialog( &dialog ) ) {
        // Accept
        QContent content = dialog.selectedDocument();
        pictureFilePath = content.fileName ();
	picture = QPixmap(pictureFilePath);
	qDebug() << "Filename :" << pictureFilePath;
        picture = picture.scaled(QSize(pictureLabel->width(),1000),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        pictureLabel->setPixmap(picture);
		removePushButton->setEnabled(true);
    } else {
        // Reject
    }
}

