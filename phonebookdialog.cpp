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
#include "viewcontactdialog.h"
#include "ringpattern.h"
#include <QSoftMenuBar>

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
	ringpattern = new RingPattern();
	audioThread = new PlayAudioThread();
	accelThread = new AccelThread();
	neoConnection = new NeoConnection();
	QObject::connect(neoConnection,SIGNAL(connected()),this, SLOT(connected()));
	QObject::connect(neoConnection,SIGNAL(disconnected()),this, SLOT(disconnected()));
	QObject::connect(neoConnection,SIGNAL(receivedPacket(QByteArray)),this, SLOT(treatPacket(QByteArray)));
	treatPacketState = WAITING;
	QMenu *menu = QSoftMenuBar::menuFor(this);
	connectAct = new QAction( tr("Connect"), this);
	QObject::connect(connectAct, SIGNAL(triggered()),this, SLOT(connectBluetooth()));
    menu->addAction(connectAct);

	QObject::connect(accelThread, SIGNAL(facingUp(bool)), this, SLOT(facingUp(bool)));
    QObject::connect(audioThread, SIGNAL(endReached()), this, SLOT(outputFinished()));
    QObject::connect(ringpattern, SIGNAL(finished()), this, SLOT(outputFinished()));
	
    qDebug()<<"instanciated phonebook ringpattern and playaudiothread";
	myPhoneBook->loadPhoneBook();
	qDebug()<<"phonebook loaded";
    selection = 0;
    slotIndex << -1 << 0 << 1 << 2 << 3;
	qDebug()<<"prepared slots";
    updateScreen(REFRESH);
	qDebug()<<"ready";

    //Load patterns
    loadPatterns();

}

PhoneBookDialog::~PhoneBookDialog()
{
    // Do nothing for now
	ringpattern->~RingPattern();
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
	qDebug()<< "<<<<Update Screen";
	qDebug()<<"Selection :"<<selection;
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
			qDebug()<<"s:"<<selection<<" n:"<<myPhoneBook->getNumEntries();
			if(selection == myPhoneBook->getNumEntries()-1) break;
			qDebug()<<"sis:"<<slotIndex.size()<<" sil:"<<slotIndex.last();
			if((selection==slotIndex.last())){
				qDebug()<<"scroll down";
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
			qDebug()<<"refresh";
			slotIndex.clear();
			if (selection == -1){
				qDebug()<<"selection is on new contact";
				for (int i = -1; i< std::min(myPhoneBook->getNumEntries(),4);i++){
					slotIndex << i;
				}
			} else if (selection >= myPhoneBook->getNumEntries()-3) {
				qDebug()<<"selection is at end of phonebook";
				for(int i = 0; i<=std::min(4,myPhoneBook->getNumEntries());i++){
					slotIndex.prepend(myPhoneBook->getNumEntries()-1-i);
				}
			} else {
				qDebug()<<"selection is in the middle of phonebook";
				slotIndex << selection -1;
				slotIndex << selection;
				for(int i=selection+1; i < std::min(selection+4,myPhoneBook->getNumEntries());i++) {
					slotIndex << i;
				}
			}
			break;
		default:
			;
	}
	qDebug()<<"selection after switch: "<<selection;
	int i;
	for(i=0;i<slotIndex.size();i++){
		qDebug()<<"Slot index"<< i << ":" << slotIndex.at(i);
		if(slotIndex.at(i) == -1){
			updateContactSlot(i,"New contact",(slotIndex.at(i)==selection));
		} else {
			updateContactSlot(i,myPhoneBook->getElementAt(slotIndex.at(i))->getContactName(),(slotIndex.at(i)==selection));
		}
	}
	for(int j=i;j<5;j++){
		updateContactSlot(i,"");
	}
}

void PhoneBookDialog::addContact(NeoPhoneBookEntry *newEntry)
{
    // add contact to the phonebook and refresh screen
	myPhoneBook->addEntry(newEntry);
	selection = myPhoneBook->findIndex(newEntry->getContactName());
	updateScreen(REFRESH);
	syncPhoneBook();

}

void PhoneBookDialog::replaceContact(NeoPhoneBookEntry *newEntry)
{
    // replace contact in the phonebook and refresh screen
	myPhoneBook->deleteEntry(selection);
	myPhoneBook->addEntry(newEntry);
	myPhoneBook->savePhoneBook();
	selection= myPhoneBook->findIndex(newEntry->getContactName());
	updateScreen(REFRESH);
	syncPhoneBook();

}

void PhoneBookDialog::deleteContact(int index)
{
    // delete contact in the phonebook
	myPhoneBook->deleteEntry(index);
	if(index==myPhoneBook->getNumEntries()) updateScreen(DELETE_LAST);
	else updateScreen(REFRESH);
	syncPhoneBook();

}

void PhoneBookDialog::outputFinished(){
    outputRunning--;
    if (outputRunning==0)
        accelThread->stop();
}

void PhoneBookDialog::stopCall(){
	audioThread->stop();
    ringpattern->stopVibrate();
	accelThread->stop();
}

void PhoneBookDialog::callContact(int index){
	qDebug() << "Call contact" << index;
	accelThread->start();

    NeoPhoneBookEntry* contact = myPhoneBook->getElementAt(index);
	
    qDebug() << "Vibration pattern :" << contact->getVibrationPattern();
    ringpattern->setPattern(contact->getVibrationPattern(),RingPattern::VIB);
    qDebug() << "Led pattern :" << contact->getLedPattern();
    ringpattern->setPattern(contact->getLedPattern(),RingPattern::LED);
    ringpattern->setSynchronized( contact->getRingOption() == 1);

	// safe
	audioThread->stop();
	audioThread->loadFile(contact->getRingtone());
	audioThread->setOffset(contact->getRingOffset());
	

	

	// start the show !
	if(accelThread->isFacingUp()){
        orientationState=0;
		audioThread->play();
    }
    else {
        orientationState=1;
    }
	ringpattern->startVibrate();
    
    outputRunning=2;

/*
	// pour pulse :
	
	ringpattern->setPattern("Pulse",RingPattern::VIB);
	ringpattern->setPattern("Pulse",RingPattern::LED);
	ringpattern->startVibrate();
	

	// pour random :
	ringpattern->setPattern("Random",RingPattern::VIB);
	ringpattern->setPattern("Random",RingPattern::LED);
	ringpattern->startVibrate();
*/
}

void PhoneBookDialog::facingUp(bool up){
	switch(orientationState){
	case 0: // phone started facing up
		if(up)  // nothing changed
			break;
		// phone has been turned down, hangup
		stopCall();
		break;
	case 1: // phone is facing down
		if(!up) // nothing changed
			break;
		// phone has been turned up
		orientationState=2;
		break;
	case 2: // phone started facing down then facing up
		if(up)  // nothing changed
			break;
		// phone has been turned down
		// hang up
		stopCall();
		break;
	default: break;
	}
}


void PhoneBookDialog::on_searchLineEdit_textChanged(const QString &text)
{
    if(text=="") return;
    qDebug() << ">>Text changed";
    // updates the screen so that the selected entry zeroes into closest match
    int i = myPhoneBook->findIndex(text);
    qDebug() << "Index found =" << i;
    selection = i;
    updateScreen(REFRESH);
}

void PhoneBookDialog::on_upButton_clicked()
{
    searchLineEdit->setText("");
    updateScreen(UP);
    
}

void PhoneBookDialog::on_downButton_clicked()
{
    searchLineEdit->setText("");
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
        ViewContactDialog *vcd = new ViewContactDialog(this,selection);
        
		QObject::connect( vcd, SIGNAL(deleteContact(int)), this, SLOT(deleteContact(int) ));
		QObject::connect( vcd, SIGNAL(callContact(int)), this, SLOT(callContact(int) ));
        QObject::connect( vcd, SIGNAL(stopCall()), this, SLOT(stopCall() ));
        vcd->setAttribute(Qt::WA_DeleteOnClose);
        vcd->showMaximized();
    }
    updateScreen(REFRESH);

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

void PhoneBookDialog::loadPatterns(){
    
    QDir dir = QDir::home();
    dir.cd("Documents");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);


    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        QString fileName = fileInfo.fileName();
        qDebug() << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
                                                .arg(fileInfo.fileName()));
        if(fileName.endsWith(".vib")){
            ringpattern->addPattern(fileName,RingPattern::VIB);
        } 
        else if (fileName.endsWith(".led")){
            ringpattern->addPattern(fileName,RingPattern::LED);
        }
    }

}

void PhoneBookDialog::connectBluetooth(){
	qDebug()<<"connect";
	neoConnection->showMaximized();
}

void PhoneBookDialog::disconnectBluetooth(){
	qDebug()<<"disconnect";
	neoConnection->disconnectBluetooth();
}

void PhoneBookDialog::connected(){
	connectAct->setText("Disconnect");
	connectAct->disconnect(SIGNAL(triggered()));
	QObject::connect(connectAct,SIGNAL(triggered()),this,SLOT(disconnectBluetooth()));
	syncPhoneBook(true);
}

void PhoneBookDialog::disconnected(){
	connectAct->setText("Connect");
	connectAct->disconnect(SIGNAL(triggered()));
	QObject::connect(connectAct,SIGNAL(triggered()),this,SLOT(connectBluetooth()));
}


int PhoneBookDialog::syncPhoneBook(bool data){
    QByteArray buffer;
    QStringList filters;
 	QDir dir = QDir::home();
	QFile log(dir.filePath("log.txt"));
	if(neoConnection->isConnected()){
		buffer.append(QString("%1").arg(1).toAscii());
		buffer.append('\n');
		buffer.append(QString("%1").arg(SYNC).toAscii());
		buffer.append('\n');
		buffer.append("phonebook\n");
		myPhoneBook->writePhoneBookIn(buffer);
		buffer.append("/phonebook\n");
	
		filters << "*.aud";
		readDir(buffer,"ringtones",filters,"Default","",false);
	
		filters.removeFirst();
		filters << "*.vib";
		readDir(buffer,"vibs",filters,"Pulse","Random",false);
	
		filters.removeFirst();
		filters << "*.led";
		readDir(buffer,"leds",filters,"Pulse","Random",false);
	
		filters.removeFirst();
		filters << "*.jpg" << "*.png";
		readDir(buffer,"images",filters,"","",data);
		
	// 	qDebug() << buffer << buffer.size();
		qDebug() << "PhoneBook written to output" << buffer.size() << "bytes";
	
		qDebug() << neoConnection->write(buffer) << "bytes written to the socket";
		if (!log.open(QIODevice::WriteOnly)){
			qDebug() << "ERREUR d'ouverture de log";
		}
		log.write(buffer);
		log.close();	
	}
    return 0;
}

void PhoneBookDialog::readDir(QByteArray & out, const QString & name, const QStringList & filters, const QString & defaultName, const QString & randomName, bool data){
	qDebug() << "Reading dir with filters" << filters;
	
    QDir dir = QDir::home();
    dir.cd("Documents");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setNameFilters(filters);

    dir.setSorting(QDir::Name);

	out.append(name.toAscii());
	out.append('\n');
    if(defaultName != ""){
        out.append(defaultName);
		out.append('\n');
    }
    if(randomName != ""){
        out.append(randomName);
		out.append('\n');
    }

    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        qDebug() << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
                .arg(fileInfo.fileName()));
            out.append(fileInfo.fileName().toAscii());
			out.append('\n');
            if(data){
                out.append(QString("%1\n").arg(fileInfo.size()).toAscii());
            }
    }
	out.append('/');
	out.append(name.toAscii());
	out.append('\n');
    if(data){
        for (int i = 0; i < list.size(); ++i) {
            QFileInfo fileInfo = list.at(i);
            qDebug() << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
                    .arg(fileInfo.fileName()));	
                QFile file(fileInfo.filePath());
                if (!file.open(QIODevice::ReadOnly)){
                    qWarning("Cannot open the file");
                }
                out.append(file.readAll());
        }
    }
}

void PhoneBookDialog::treatPacket(QByteArray packet){
	
	QString buffer;
	QTextStream in(packet);
	if(treatPacketState == WAITING){
		in.readLine();				//Transaction id do nothing for now
		buffer = in.readLine();
		qDebug() << "Received value" << buffer.toInt();
		switch(buffer.toInt()){
			case SYNC:
				qDebug() << "Receive sync message";
				treatSync(in);
				break;
			case ACK:
				qDebug() << "Receive ack message";
				break;
			case CALL:
				qDebug() << "Receive call message";
				treatCall(in);
				break;
			default:
			;
		}
	}
	else {
		switch(treatPacketState){
			case SYNCING:
				treatSync(in);
				break;
			default:
			;
		}
	}
}

int PhoneBookDialog::treatSync(QTextStream &in){
	qDebug() << "Treating sync message";
	QString line;
	QFile phoneBookFile(myPhoneBook->fileName);
	if( !phoneBookFile.open(QIODevice::WriteOnly) ){
		qWarning("Could not write the phonebook");
		return -1;
	}
	line = in.readLine();
	if(line.compare("phonebook")==0){
		while( !in.atEnd() && (line = in.readLine()).compare("/phonebook") != 0){
			phoneBookFile.write(line.toAscii());
			phoneBookFile.write("\n");
		}
		phoneBookFile.close();
		myPhoneBook->clearPhoneBook();
		myPhoneBook->loadPhoneBook();
    	updateScreen(REFRESH);
		
	}
	return 0;
}

int PhoneBookDialog::treatCall(QTextStream &in){
	qDebug() << "Treating call message";
	QString line;
	line = in.readLine();
	callContact(line.toInt());
	return 0;
}
