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

#ifndef AUDIODIALOG_H
#define AUDIODIALOG_H

#include <QtGui>
#include <qtopiaapplication.h>

#include "ui_audiodialogform.h"
#include "playaudiothread.h"

class AudioDialog : public QWidget, public Ui_AudioDialog
{
    Q_OBJECT

    public:
        AudioDialog(QString filename, QWidget *parent=0, Qt::WFlags f = 0 );
        ~AudioDialog();

    private:
        PlayAudioThread * player;
        bool playing;
        QString timeToString(int time);
        void updatePlayButton();
        int audioLength;

    private slots:
	    void on_playButton_clicked();
	    void on_stopButton_clicked();
	    void on_rewindButton_clicked();
	    void on_forwardButton_clicked();
        void on_slider_valueChanged(int value);
        void on_slider_sliderPressed();
        void on_slider_sliderReleased();
        void updatePosition(int time,bool force=false);
        void endReached();
        void on_saveButton_clicked();
        void on_cancelButton_clicked();

    signals:
        void saveOffset(int);
      
};

#endif
