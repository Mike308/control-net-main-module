#include "qnrf24l01.h"

QNRF24L01::QNRF24L01(QObject *parent) : QObject(parent)
{

}

QNRF24L01::QNRF24L01(uint16_t cePin, uint16_t csPin, uint32_t spiSpeed){
    qDebug () << "Testy...";
    radio = new RF24(cePin, csPin, spiSpeed);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this, SLOT(listenSlot()));
    frames = new QStringList();

}

void QNRF24L01::connectToRadio(){
    qDebug () << "Connecting to RF24...";
    radio->begin();
}

void QNRF24L01::selectSendingPipes(uint64_t address){
    radio->openWritingPipe(address);
}

void QNRF24L01::selectRecevingPipe(uint8_t i, uint64_t address){
    radio->openReadingPipe(i, address);
}

void QNRF24L01::sendData(QString data){
    char * buf;
    QByteArray ba = data.toLatin1();
    buf = ba.data();
    timer->stop();
    this->isWritingData = true;
    radio->stopListening();
    radio->powerDown();
    radio->powerUp();
    bool result = radio->write(buf, 32);
    qDebug () << "Write: " << data << "|status: " << result;
    radio->startListening();
    this->isWritingData = false;
    timer->start(1000);
}

void QNRF24L01::startListening(){
    timer->start(1000);
}

void QNRF24L01::listenSlot(){
    char msg[32];
    uint8_t pipeNum = 0;
    int len = 0;
    static int frameCnt = 0;
    qDebug() << "Start listening";
    while(radio->available(&pipeNum)){
        len = radio->getDynamicPayloadSize();
        if (!this->isWritingData){
            radio->read(&msg, len);
            QString stringMsg = QString(msg);
            qDebug () << frameCnt << "|" << "Received frame: " << stringMsg << "pipe num: " << pipeNum;
            if (stringMsg.contains('$') == false){
                frames->append(stringMsg);
            }else{
                stringMsg.replace("$", "");
                frames->append(stringMsg);
                emit dataReceived(frames->join(""), pipeNum);
                frames->clear();
                emit updatedStatus(receivingData);
            }
            frameCnt++;
        }
    }
    emit updatedStatus(endOfReceiving);
}





