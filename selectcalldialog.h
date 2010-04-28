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

#include "neophonebookentry.h"
#include "ui_addcontactform.h"

class SelectCallDialog : public QDialog {
	
	Q_OBJECT

    public:
		
    SelectCallDialog( QContentFilter filter, QWidget *parent=0, Qt::WFlags f = 0 );
    ~SelectCallDialog();

    private:
    QStackedLayout *layout;
    QDocumentSelector *documentSelector;

    private slots:
	void openDocument(QContent);

    signals:
    void documentSelected(QContent);

};
#endif