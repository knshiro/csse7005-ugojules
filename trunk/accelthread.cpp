#include "accelthread.h"

struct input_event {
    struct timeval time;
    uint16_t type;
    uint16_t code;
    int32_t value;
};

AccelThread::AccelThread(){
    file = new QFile("/dev/input/event3");
    
}

AccelThread::~AccelThread(){
    stop();
    delete file;
}

void AccelThread::run(){
    active = true;
    struct input_event ev;
    while (active) {
        if (blockingRead(file,(char *) &ev, sizeof(struct input_event))){
            perror("Error reading");
        }
        else {
            qDebug("type:%u code:%u value:%d\n", ev.type, ev.code, ev.value);
        } 
    }
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
