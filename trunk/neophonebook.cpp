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

#include "neophonebook.h"
#include <QtGlobal>

NeoPhoneBook::NeoPhoneBook()
{
	//fileName = "/home/root/Applications/CSSE4003/Documents/phonebook";
    // Use this path for QVFB
    //fileName = "/home/user/csse7005-ugojules/Documents/phonebook";

    // Use this path for KINGSTON
    //fileName = "/media/KINGSTON/csse7005/project/csse7005-ugojules/Documents/phonebook";
    
    // Use this path for NEO 
    fileName = "/home/root/Documents/phonebook";
}

void NeoPhoneBook::addEntry(NeoPhoneBookEntry *newEntry)
{
    qDebug() << ">>>> Adding entry";
    // add the entry to the phonebook using findIndex and save
    int i = findIndex(newEntry->getContactName());
    qDebug() << "Index of the entry :" << i;
    phoneList.insert(i,newEntry);
    savePhoneBook();
    qDebug() << "<<<< Entry added";
    
}

int NeoPhoneBook::findIndex(QString const &name)
{
    // find the best index to insert into the list using binary search
     if(phoneList.size()==0){return 0;}
     if(QString::compare(name,phoneList.at(0)->getContactName(),Qt::CaseInsensitive)<=0){
       return 0;}
     if(name.compare(phoneList.at(phoneList.size()-1)->getContactName(),Qt::CaseInsensitive)>0){
           return phoneList.size();}
 
     return recFindIndex(name,0,phoneList.size()-1);
}

int NeoPhoneBook::recFindIndex(QString const &name,int start, int end)
{
   
    if(end==start+1) return end;
    int mid = (start+end)/2;
    QString midS = phoneList.at(mid)->getContactName();
    if(name.compare(midS,Qt::CaseInsensitive)==0){
      return mid;
    }
    if(name.compare(midS,Qt::CaseInsensitive)<0){
      return recFindIndex(name,start,mid);
    }
    else {
      return recFindIndex(name,mid,end);
    }

}


void NeoPhoneBook::loadPhoneBook()
{
    // load the phonebook by reading the "phonebook" file and populating
    // phoneList
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
       return;
    while (!file.atEnd()) {
        QString line = QString(file.readLine());
        line = line.replace("\n","").replace("\r","");
        QStringList fields = line.split("|");
	NeoPhoneBookEntry * newEntry = new NeoPhoneBookEntry(fields.at(0),fields.at(1),fields.at(2),fields.at(3),
		fields.at(4),fields.at(5),fields.at(6),fields.at(7).toInt(),fields.at(8).toInt());
	if(fields.at(4).compare("")==0) newEntry->setRingTone("Default");
	if(fields.at(5).compare("")==0) newEntry->setVibrationPattern("Pulse");
	if(fields.at(6).compare("")==0) newEntry->setLedPattern("Pulse");
	if(fields.at(7).compare("")==0) newEntry->setRingOption(0);
	if(fields.at(8).compare("")==0) newEntry->setRingOffset(0);

	int i = findIndex(newEntry->getContactName());
    	phoneList.insert(i,newEntry);
    }
    
}

void NeoPhoneBook::savePhoneBook()
{
    qDebug()<<">>>>Saving phonebook";
    // save the phonebook by writing phoneList to the "phonebook" file
    QFile file(fileName);
    
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
       return;
	QDataStream out(&file);
    writePhoneBookIn(out);
    qDebug()<<"<<<<Phonebook saved";
}

void NeoPhoneBook::writePhoneBookIn(QDataStream &out){
	QByteArray bytes;
NeoPhoneBookEntry entry;
	for(int i=0;i<phoneList.size();i++){
      entry = *phoneList.at(i);
      QString line = entry.getContactName() + "|" + entry.getPhoneNumber() + "|" + entry.getContactEmail() + "|" + entry.getPictureFilePath()+"|"+entry.getRingtone()+"|"+entry.getVibrationPattern()+"|"+entry.getLedPattern()+"|";
      line.append(QString::number(entry.getRingOption()));
      line.append("|");
      line.append(QString::number(entry.getRingOffset()));
      line.append("\n");
      qDebug()<<"Saving entry" <<line;
      out << line ;
    }

}

void NeoPhoneBook::clearPhoneBook()
{
    // remove all entries from the phoneList
    phoneList.clear();
}

void NeoPhoneBook::replaceEntry(int index, NeoPhoneBookEntry *newEntry)
{
    // replace an entry in the phoneList at index with newEntry
    phoneList.replace(index,newEntry);
    savePhoneBook();
}

void NeoPhoneBook::deleteEntry(int index)
{
    // remove an entry in the phoneList at index
    phoneList.removeAt(index);
    savePhoneBook();
}

int NeoPhoneBook::getNumEntries()
{
    // return the size of the phoneList
    return phoneList.size();
}

NeoPhoneBookEntry* NeoPhoneBook::getElementAt(int index)
{
    // return the element of phoneList at index
    return phoneList.at(index);
}

NeoPhoneBook::~NeoPhoneBook()
{
    // Do nothing for now
}

