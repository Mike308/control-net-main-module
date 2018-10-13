#include "supervisor.h"

Supervisor::Supervisor(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    nodeBus = new NodeBus();
    connect(nodeBus, SIGNAL(temperaturesReceived(QList<Temperature>)), this, SLOT(onGetTemperatures(QList<Temperature>)));
    connect(timer, SIGNAL(timeout()), this, SLOT(onSendRequest()));
}

void Supervisor::begin(){
    timer->start(10000);
}

void Supervisor::onSendRequest(){
    nodeBus->sendRequest("AT+DS18B20?", "0");
}

void Supervisor::onGetTemperatures(QList<Temperature> temperatures){
    for (Temperature temperature : temperatures){
        qDebug () << "Temperature: " << temperature.getTemperature();
    }
}
