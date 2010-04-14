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

#include "phonebookdialog.h"

PhoneBookDialog::PhoneBookDialog(QWidget *parent, Qt::WFlags f)
    : QWidget(parent, f)
{
	qDebug()<<"constructeur";
    setupUi(this);
	qDebug()<<"passe setupUI";
	contactSlots.append(firstContact);
	contactSlots.append(secondContact);
	contactSlots.append(thirdContact);
	contactSlots.append(forthContact);
	contactSlots.append(fifthContact);
	qDebug()<<"passe append";
    myPhoneBook = new NeoPhoneBook();
    qDebug()<<"bite";
	myPhoneBook->loadPhoneBook();
	qDebug()<<"pouet";
    selection = 0;
    slotIndex << -1 << 0 << 1 << 2 << 3;
	qDebug()<<"prout";
    updateScreen(REFRESH);
	qDebug()<<"caca";
}

PhoneBookDialog::~PhoneBookDialog()
{
    // Do nothing for now
}

void PhoneBookDialog::updateContactSlot(int index, QString name, bool selected)
{
    QPalette *pal;
    // update the contact slot at 'index' with the text 'name'
	contactSlots.at(index)->setText(name);
	
    if(selected){
		pal = new QPalette(Qt::blue);
	} else {
		pal = new QPalette(Qt::black);
	}
	contactSlots.at(index)->setPalette(*pal);
}

void PhoneBookDialog::updateScreen(Update_Types type)
{
	qDebug()<<"caca pouet"<<selection;
	if(selection<-1) selection = -1;
	if(selection>myPhoneBook->getNumEntries()-1) selection = myPhoneBook->getNumEntries()-1;
    // updates the 5 contact slots for scrolling or refreshing
    switch(type){
		case UP:
			if (selection == -1){
				return;
			}
			selection--;
			if((selection < slotIndex.first()+1)&&(selection>-1)){
				slotIndex.pop_back();
				slotIndex.push_front(selection-1);
			}
			break;
		case DOWN:
			if (selection == myPhoneBook->getNumEntries()-1){
				return;
			}
			selection++;
			if((selection>slotIndex.last()-1)&&(selection<myPhoneBook->getNumEntries()-1)){
				slotIndex.pop_front();
				slotIndex.push_back(selection+1);
			}
			break;
		case DELETE_LAST:
			selection = myPhoneBook->getNumEntries()-1;
			slotIndex.pop_back();
			if(myPhoneBook->getNumEntries()>3)
				slotIndex.push_front(selection-4);
			break;
		case REFRESH:
			slotIndex.clear();
			if (selection <= -1){
				selection = -1;
				for (int i = -1; i< myPhoneBook->getNumEntries()-1;i++){
					slotIndex << i;
				}
			} else
			if (selection >= myPhoneBook->getNumEntries()-1){
				selection = myPhoneBook->getNumEntries()-1;
				for(int i = myPhoneBook->getNumEntries()-1; i>=-1;i--){
					slotIndex.prepend(i);
				}
			} else {
				slotIndex << selection -1;
				slotIndex << selection;
				for(int i= selection +1; i < std::min(selection + 4,myPhoneBook->getNumEntries());i++) {
					slotIndex << i;
				}
			}
			break;
		default:
			;
	}
	qDebug()<<"pouet caca"<<selection;
	for(int i=0;i<5;i++){
		qDebug()<<"Slot index"<< i << ":" << slotIndex.at(i);
		if(slotIndex.at(i) == -1){
			updateContactSlot(i,"New contact",(slotIndex.at(i)==selection));
		} else {
		if(slotIndex.at(i)<myPhoneBook->getNumEntries())
			updateContactSlot(i,myPhoneBook->getElementAt(slotIndex.at(i))->getContactName(),(slotIndex.at(i)==selection));
		else
			updateContactSlot(i,"");
		}
	}
}

void PhoneBookDialog::addContact(NeoPhoneBookEntry *newEntry)
{
    // add contact to the phonebook and refresh screen
	myPhoneBook->addEntry(newEntry);
	updateScreen(REFRESH);

}

void PhoneBookDialog::replaceContact(NeoPhoneBookEntry *newEntry)
{
    // replace contact in the phonebook and refresh screen
	myPhoneBook->savePhoneBook();
	updateScreen(REFRESH);
}

void PhoneBookDialog::deleteContact(int index)
{
    // delete contact in the phonebook
	myPhoneBook->deleteEntry(index);
	if(index==myPhoneBook->getNumEntries()) updateScreen(DELETE_LAST);
	else updateScreen(REFRESH);
}

void PhoneBookDialog::on_searchLineEdit_textChanged(const QString &text)
{
    qDebug() << ">>Text changed";
    // updates the screen so that the selected entry zeroes into closest match
    int i = myPhoneBook->findIndex(text);
    qDebug() << "Index found =" << i;
    selection = i;
    updateScreen(REFRESH);
}

void PhoneBookDialog::on_upButton_clicked()
{
    updateScreen(UP);
}

void PhoneBookDialog::on_downButton_clicked()
{
    updateScreen(DOWN);
}

void PhoneBookDialog::on_selectButton_clicked()
{
    // if new contact is the selection open dialog to add contacts
    // otherwise open dialog to view contact information
    // the example below will open the dialog at full screen
    if(selection==-1){
        AddContactDialog *myAddContactDialog = new AddContactDialog();
        myAddContactDialog->setAttribute(Qt::WA_DeleteOnClose);
        myAddContactDialog->showMaximized();
	QObject::connect( myAddContactDialog, SIGNAL(addContact(NeoPhoneBookEntry *)), this, SLOT(addContact(NeoPhoneBookEntry *) ));
	QObject::connect( myAddContactDialog, SIGNAL(editContact(NeoPhoneBookEntry *)), this, SLOT(replaceContact(NeoPhoneBookEntry *) ));
    }
    else {
        ViewContactDialog *vcd = new ViewContactDialog(myPhoneBook->getElementAt(selection));
        vcd->setAttribute(Qt::WA_DeleteOnClose);
        vcd->showMaximized();
    }
}

void PhoneBookDialog::on_deleteButton_clicked()
{
    // prompt user to be able to delete the selected contact
	if(selection==-1) return;
	qDebug() << "deleting ?: " << QString::number(selection);

  /*  QMessageBox msgBox;
    msgBox.setWindowTitle("Confirm delete");
    msgBox.setIcon(QMessageBox::Yes|QMessageBox::No);
    msgBox.setText("Erase contact " + myPhoneBook->getElementAt(selection)->getContactName() +" ?");
    msgBox.exec(); */
	int ret = QMessageBox::warning(this, "Confirm delete",
                   "Erase contact " + myPhoneBook->getElementAt(selection)->getContactName() +" ?",
                   QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
	if (ret==QMessageBox::Yes) deleteContact(selection);
}

