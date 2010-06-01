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

#include <QTimer>
#include <QStringList>
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>

#include <QBluetoothAddress>
#include <QBluetoothRfcommSocket>
#include <QBluetoothRemoteDeviceDialog>

#include <QtopiaApplication>
#include <QWaitWidget>
#include <QAction>
#include <QMenu>
#include <QSoftMenuBar>

#include "neoconnection.h"

#define DEBUG 0

/*
 * Constructor of dummy connection application
 */
NeoConnection::NeoConnection(QWidget *parent, Qt::WFlags f)
    : QWidget(parent, f)
{
    /* Create the user interface from .ui header file */
    setupUi(this);

    /* initialise the neo_state */
    neo_state = NEO_INIT;
}


/*
 *  Destructor which sends a disconnect to the server before terminating
 */
NeoConnection::~NeoConnection()
{
}


/*
 * Make a socket connection to any avaiable local address to the scanned
 * address on the supplied channel
 */
void NeoConnection::connectSocket()
{
    /* Create a Qt Bluetooth device select dialog to grab an address */
}


void NeoConnection::on_serverButton_clicked()
{
}

/*
 * Updates the network state machine
 *
 */
void NeoConnection::updateFSM(const QString &command)
{
    qDebug() << "Current Operation: " << command;
    switch(neo_state)
    {
        case NEO_INIT:
            break;
        default:
            break;
    }
}

