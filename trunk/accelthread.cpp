#include "accelthread.h"

struct input_event {
    struct timeval time;
    uint16_t type;
    uint16_t code;
    int32_t value;
};

AccelThread::AccelThread(){
    file = new QFile("/dev/input/event3");

    
    side = true;
    
}

AccelThread::~AccelThread(){
    stop();
    delete file;
}

void AccelThread::run(){
    active = true;
    struct input_event ev;
    QList<int> measures;
    int32_t sum = 0;
    if (!file->open(QIODevice::ReadOnly)){
        qDebug() << "AccelThread: Cannot open the file" << file->fileName();
        return;
    }
    for(int i=0;i<5;i++){
        ev.code = -1;
        while (ev.code != 2){
            if ( blockingRead(file,(char *) &ev, sizeof(struct input_event)) != sizeof(struct input_event)){
                perror("AccelThread: Error reading");
                return;
            }
        }    
        sum = 0;
        for(int i = 0; i<measures.size(); i++){
            sum += measures.at(i);
        }
        side = sum >0;
        qDebug("AccelThread: type:%u code:%u value:%d\n", ev.type, ev.code, ev.value); 
        measures.append(ev.value);
    }
    file->close();
    while (active) {
        if (!file->open(QIODevice::ReadOnly)){
        	qDebug() << "AccelThread: Cannot open the file" << file->fileName();
		return;
    	}
        ev.code = -1;
	    while (ev.code != 2){
	        if ( blockingRead(file,(char *) &ev, sizeof(struct input_event)) != sizeof(struct input_event)){
                perror("AccelThread: Error reading");
                return;
            }
        }
        qDebug("AccelThread: type:%u code:%u value:%d\n", ev.type, ev.code, ev.value); 
        measures.removeFirst();
        measures.append(ev.value);
        sum = 0;
        for(int i = 0; i<measures.size(); i++){
            sum += measures.at(i);
        }
        side = sum >0;
        emit facingUp(side); 
	    file->close();
        msleep(50);
    }
    qDebug() << "AccelThread: return";
}

int AccelThread::blockingRead(QFile * file, char * buffer, int count)
{
    int n_read = 0;
    while (n_read != count) {
        int result = file->read(buffer + n_read, count - n_read);
        if (result < 0)
            return result;
        else if (result == 0)
            return n_read;
        n_read += result;
    }
    return n_read;
//     QByteArray arrayBuffer;
//     while (arrayBuffer.size() != count) {
//         arrayBuffer.append(file->read(count - arrayBuffer.size()));
//     }
//     return arrayBuffer.data();
}

void AccelThread::stop(){
    active = false;
}

bool AccelThread::isFacingUp(){
    return side;
}
