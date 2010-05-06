/***************************************************************************
 *   Copyright (C) 2008 by Egil Anonsen
 *   eanonsen@hotmail.com
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef PLAYAUDIOTHREAD_H
#define PLAYAUDIOTHREAD_H

#include <QAudioOutput>
#include <QThread>
#include <QFile>
#include <QtGlobal>
#include <qtopiaapplication.h>
#include <QString>

/**
*	@author Ugo Bataillard
*	@version 1.0
* 	This class is used to play audio files and implements the playback with multithreading.
*/
class PlayAudioThread : public QThread
{
	Q_OBJECT
	
    public :
        static const int FREQUENCY = 11025;
        static const int CHANNELS = 1;
        static const int BITSPERSAMPLE = 16;
        static const int BYTESPERDS = (int) ((FREQUENCY/10.0) * CHANNELS * BITSPERSAMPLE/8) + ((int) ((FREQUENCY/10.0) * CHANNELS * BITSPERSAMPLE/8)) % 2;

	public:
   		PlayAudioThread(QString filename = "");
		~PlayAudioThread();
        
        virtual bool play(int offset = -1);
        virtual void pauseResume();
        int getDuration();
        virtual void stop();

        virtual void run();
        
        bool loadFile(QString filename);
        bool setOffset(int offset);

	signals:
	    void currentSec(int);
        void playEnded();

	private slots:
		

	private:
		QAudioOutput *audioOutput;
        QFile *file;
        int offset;
        bool active;

};






#endif
