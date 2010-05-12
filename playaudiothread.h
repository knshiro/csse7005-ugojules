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
        int getOffset();


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
