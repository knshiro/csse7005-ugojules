#ifndef ACCELTHREAD_H
#define ACCELTHREAD_H

#include <QThread>
#include <QFile>
#include <QtGlobal>
#include <qtopiaapplication.h>
#include <QString>

#include <stdio.h>
#include <time.h>
#include <sys/times.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

/**
*   @author Ugo Bataillard
*   @version 1.0
*
*/
class AccelThread : public QThread
{
    Q_OBJECT
    
    public :
       //static enum Side { UP, DOWN };

    public:
        AccelThread();
        ~AccelThread();
        
        virtual void run();
        virtual void stop();

        //Side getSide();
        bool isFacingUp();

    signals:
        // currentSide(Side side); 
        void facingUp(bool);

    private:
        int blockingRead(QFile * file, char * buffer, int count);
        bool side; //True is UP, False is DOWN
        bool active;
        QFile * file;

};



#endif
