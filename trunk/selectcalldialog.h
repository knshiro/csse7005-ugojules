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

#ifndef SELECTCALLDIALOG_H
#define SELECTCALLTDIALOG_H

#include <QtGui>
#include <qtopiaapplication.h>
#include <QContentFilter>
#include <QStackedLayout>
#include <QDocumentSelector>
#include <QContent>

#include "ui_selectcallform.h"

class SelectCallDialog : public QDialog , public Ui_SelectCallDialog{
	
	Q_OBJECT

    public:
		
    SelectCallDialog( QString selected, QString extension, QString defaultName = "", QString randomName = "", QWidget *parent=0, Qt::WFlags f = 0 );
    ~SelectCallDialog();

    private:
    QDir dir;

    private slots:
	void on_selectPushButton_clicked();
    void on_cancelPushButton_clicked();

    signals:
    void fileSelected(QString filename);

};

#endif