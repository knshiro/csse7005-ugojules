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
#include "selectcalldialog.h"
#include <QImageDocumentSelectorDialog>
#include <QContentFilter>

AddContactDialog::AddContactDialog(QWidget *parent, Qt::WFlags f)
    : QWidget(parent, f)
{
    // initialize the dialog
    setupUi(this);
    editEntry = NULL;
    ringOffset = 0;

}

AddContactDialog::~AddContactDialog()
{
    // Do nothing
}

void AddContactDialog::setupEdit(NeoPhoneBookEntry *entryToEdit)
{
    QPixmap picture;
	QDir documents = QDir::home();
	documents.cd("Documents");
    editEntry = entryToEdit;
    // sets up the UI for edit-mode
    nameLineEdit->setText(entryToEdit->getContactName());
    numberLineEdit->setText(entryToEdit->getPhoneNumber());
    emailLineEdit->setText(entryToEdit->getContactEmail());
    pictureFilePath = entryToEdit->getPictureFilePath();
    ringToneLabel->setText(entryToEdit->getRingtone());
    vibrationLabel->setText(entryToEdit->getVibrationPattern());
    ledLabel->setText(entryToEdit->getLedPattern());
    ringOptionComboBox->setCurrentIndex(entryToEdit->getRingOption());
    setRingOffset(entryToEdit->getRingOffset());
    qDebug() << "Filename :" << entryToEdit->getPictureFilePath();
    if(entryToEdit->getPictureFilePath() != ""){
      picture = QPixmap(documents.filePath(pictureFilePath));
      picture = picture.scaled(QSize(pictureLabel->width(),pictureLabel->height()),Qt::KeepAspectRatio,Qt::SmoothTransformation);
      pictureLabel->setPixmap(picture);
      removePushButton->setEnabled(true);
    }
}


void AddContactDialog::on_savePushButton_clicked()
{
    qDebug() << ">>>> Save Clicked";
    if(nameLineEdit->text() != "" && numberLineEdit->text() != ""){
        if(editEntry != NULL){
	        editEntry->setContactName(nameLineEdit->text());
            editEntry->setPhoneNumber(numberLineEdit->text());
            editEntry->setContactEmail(emailLineEdit->text());
            editEntry->setPictureFilePath(pictureFilePath);
            editEntry->setRingTone(ringToneLabel->text());
            editEntry->setVibrationPattern(vibrationLabel->text());
            editEntry->setLedPattern(ledLabel->text());
            editEntry->setRingOption(ringOptionComboBox->currentIndex ());
            editEntry->setRingOffset(ringOffset);
            qDebug() << ">>Set ring offset :" << editEntry->getRingOffset();
            emit editContact(editEntry);
        }
        else {
	        NeoPhoneBookEntry *newEntry = new NeoPhoneBookEntry(nameLineEdit->text(), numberLineEdit->text(), emailLineEdit->text(),pictureFilePath, ringToneLabel->text(), vibrationLabel->text(), ledLabel->text(), ringOptionComboBox->currentIndex(), ringOffset);
            emit addContact(newEntry);
        }
	close();
    } else {
		QMessageBox::warning(this, "Save impossible",
                   "You must enter at least a name and a telephone number",
                   QMessageBox::Ok);
	}
    
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
		QFileInfo picFile(content.fileName());
        pictureFilePath = picFile.fileName();
		picture = QPixmap(content.fileName());
	qDebug() << "Filename :" << pictureFilePath;
        picture = picture.scaled(QSize(pictureLabel->width(),pictureLabel->height()),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        pictureLabel->setPixmap(picture);
		removePushButton->setEnabled(true);
    } else {
        // Reject
    }
}

void AddContactDialog::on_ringOptionComboBox_currentIndexChanged(int i){
	
	qDebug()<< "index:" << i;
	if(i == 0) {
		ledPushButton->setEnabled(true);
	}
	else {
		ledPushButton->setEnabled(false);
	}
		

}

void AddContactDialog::on_ringTonePushButton_clicked(){
	browseState = RINGTONE;
	SelectCallDialog *dialog = new SelectCallDialog(ringToneLabel->text(), ".aud" ); 
	dialog->setAttribute(Qt::WA_DeleteOnClose);
    connect( dialog, SIGNAL(fileSelected(QString)),
                 this, SLOT(setFile(QString)) );
    dialog->showMaximized();
}

void AddContactDialog::on_ledPushButton_clicked(){
	browseState = LED;
	SelectCallDialog *dialog = new SelectCallDialog(ledLabel->text(), ".led", "Pulse", "Random"); 
	dialog->setAttribute(Qt::WA_DeleteOnClose);
    connect( dialog, SIGNAL(fileSelected(QString)),
                 this, SLOT(setFile(QString)) );
    dialog->showMaximized();
}
void AddContactDialog::on_vibrationPushButton_clicked(){
	browseState = VIBRATION;
	SelectCallDialog *dialog = new SelectCallDialog(vibrationLabel->text(), ".vib", "Pulse","Random"); 
	dialog->setAttribute(Qt::WA_DeleteOnClose);
    connect( dialog, SIGNAL(fileSelected(QString)),
                 this, SLOT(setFile(QString)) );
    dialog->showMaximized(); 
}

void AddContactDialog::setFile(QString filename) {
    AudioDialog * ad;
	switch(browseState){
		case RINGTONE:
			qDebug() << "Ringtone :" << filename << "selected";
			ad = new AudioDialog(filename);
                        ad->showMaximized();
            ad->setAttribute(Qt::WA_DeleteOnClose);
            connect(ad, SIGNAL(saveOffset(int)), this, SLOT(setRingOffset(int)));
			
            ringToneLabel->setText(filename);
			break;
		case LED:
			qDebug() << "LED :" << filename << "selected";
			ledLabel->setText(filename);
			break;
		case VIBRATION:
			qDebug() << "Vibration :" << filename << "selected";
			vibrationLabel->setText(filename);
			break;
		default:
			;
	}
}

void AddContactDialog::setRingOffset(int offset){
    qDebug() << "Saving offset :" << offset << "dsec";
    ringOffset = offset;
}
