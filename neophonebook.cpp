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
    // Use this path for QVFB
    //fileName = "/home/user/projects/Assignment_2/Documents/phonebook";

    // Use this path for KINGSTON
    fileName = "/media/KINGSTON/csse7005/project/csse7005-ugojules/Documents/phonebook";
    
    // Use this path for NEO 
    //fileName = "/home/root/Documents/phonebook";
}

void NeoPhoneBook::addEntry(NeoPhoneBookEntry *newEntry)
{
    // add the entry to the phonebook using findIndex and save
    int i = findIndex(newEntry);
    phoneList.insert(i,newEntry);
}

int NeoPhoneBook::findIndex(NeoPhoneBookEntry *entry)
{
    // find the best index to insert into the list using binary search
    if(phoneList.size()==0){return 0;}
    if(QString::compare(entry->getContactName(),phoneList.at(0)->getContactName())<0){
      return 0;}
    if(entry->getContactName().compare(phoneList.at(phoneList.size()-1)->getContactName())>0){
          return phoneList.size();}

    return recFindIndex(entry,0,phoneList.size()-1);
}

int NeoPhoneBook::recFindIndex(NeoPhoneBookEntry *newEntry,int start, int end)
{
   
    if(end==start+1) return end;
    int mid = (start+end)/2;
    QString midS = phoneList.at(mid)->getContactName();
    if(newEntry->getContactName().compare(midS)==0){
      return mid;
    }
    if(newEntry->getContactName().compare(midS)<0){
      return recFindIndex(newEntry,start,mid);
    }
    else {
      return recFindIndex(newEntry,mid,end);
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
        line = line.replace("\n","");
        QStringList fields = line.split("|");
        addEntry(new NeoPhoneBookEntry(fields.at(0),fields.at(1),fields.at(2),fields.at(3)));
    }
    
}

void NeoPhoneBook::savePhoneBook()
{
    // save the phonebook by writing phoneList to the "phonebook" file
    QFile file(fileName);
    NeoPhoneBookEntry entry;
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
       return;
    for(int i=0;i<phoneList.size();i++){
      entry = *phoneList.at(i);
      QString line = entry.getContactName() + "|" + entry.getPhoneNumber() + "|" + entry.getContactEmail() + "|" + entry.getPictureFilePath()+"\n";
      QByteArray bytes = line.toAscii();
      file.write(bytes);
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
}

void NeoPhoneBook::deleteEntry(int index)
{
    // remove an entry in the phoneList at index
    phoneList.removeAt(index);
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

