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

#ifndef NEOCONNECTION_H
#define NEOCONNECTION_H

#include <QTimer>
#include <qtopia/qtopiaapplication.h>

#include "neophonebook.h"
#include "protocols.h"
#include "ui_neoconnection.h"

class QWaitWidget;
class QAction;
class QBluetoothRfcommSocket;
class QTextEdit;
class QLineEdit;

class NeoConnection : public QWidget, public Ui_NeoConnection
{
    Q_OBJECT
    
    public:
        NeoConnection( QWidget *parent = 0, Qt::WFlags f = 0 );
        ~NeoConnection();
    
    public slots:
        void connectSocket();
        void updateFSM(const QString &command);
        void on_serverButton_clicked();
		int syncPhoneBook(NeoPhoneBook * phoneBook);

    private slots:
		void readFromSocket();

    private:
        int neo_state;
		QBluetoothRfcommSocket *rfcommSocket;
		qint64 write(const QByteArray & byteArray);
};

#endif

