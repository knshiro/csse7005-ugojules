#include "unittest.h"
#include <QtGlobal>



UnitTest::UnitTest(){
    
}

void UnitTest::testPart1(){
    phoneBook = new NeoPhoneBook();
    phoneBook->addEntry(new NeoPhoneBookEntry("b","01");
    phoneBook->addEntry(new NeoPhoneBookEntry("d","02");
    phoneBook->addEntry(new NeoPhoneBookEntry("e","03");
    phoneBook->addEntry(new NeoPhoneBookEntry("a","03");
    phoneBook->addEntry(new NeoPhoneBookEntry("c","03");


    if(phoneBook->getNumEntries()==5) 
      qDebug() << "getNumEntries: OK";
    else qDebug() << "getNumEntries: ERROR";

    if(phoneBook->getElementAt(0)->getContactName()=="a") 
      qDebug() << "a: OK";
    else qDebug() << "a: ERROR: " << phoneBook->getElementAt(0)->getContactName();

    if(phoneBook->getElementAt(1)->getContactName()=="b") 
      qDebug() << "b: OK";
    else qDebug() << "b: ERROR: " << phoneBook->getElementAt(1)->getContactName();

    if(phoneBook->getElementAt(2)->getContactName()=="c") 
      qDebug() << "c: OK";
    else qDebug() << "c: ERROR: " << phoneBook->getElementAt(2)->getContactName();

    if(phoneBook->getElementAt(3)->getContactName()=="d") 
      qDebug() << "d: OK";
    else qDebug() << "d: ERROR: " << phoneBook->getElementAt(3)->getContactName();

    if(phoneBook->getElementAt(4)->getContactName()=="e") 
      qDebug() << "e: OK";
    else qDebug() << "e: ERROR: " << phoneBook->getElementAt(4)->getContactName();

    QString s = phoneBook->getElementAt(3)->getContactName();
    phoneBook->deleteEntry(2);
    if(phoneBook->getElementAt(2)->getContactName()==s) 
      qDebug() << "deleteEntry: OK";
    else qDebug() << "deleteEntry: ERROR";

    phoneBook->replaceEntry(2,new NeoPhoneBookEntry("x","00");
    if(phoneBook->getElementAt(2)->getContactName()=="x") 
      qDebug() << "replaceEntry: OK";
    else qDebug() << "replaceEntry: ERROR";

}