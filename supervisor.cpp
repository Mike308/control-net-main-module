#include "supervisor.h"
#include <QDateTime>
Supervisor::Supervisor(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    nodeBus = new NodeBus();
    connect(nodeBus, SIGNAL(temperaturesReceived(QList<Temperature>)), this, SLOT(onGetTemperatures(QList<Temperature>)));
    connect(nodeBus, SIGNAL(sensorsReceived(QList<Sensor>,QString)), this, SLOT(onGetSensors(QList<Sensor>,QString)));
    connect(timer, SIGNAL(timeout()), this, SLOT(onSendRequest()));
}

void Supervisor::begin(){
    nodeBus->sendRequest("AT+SENS?", "0");
    timer->start(60000);
}

void Supervisor::onSendRequest(){
    nodeBus->sendRequest("AT+DS18B20?", "0");
}

void Supervisor::onGetTemperatures(QList<Temperature> temperatures){
    qDebug () << "Datetime: " << QDateTime::currentDateTime();
    for (Temperature temperature : temperatures){
        qDebug () << "Temperature: " << temperature.getTemperature() << "|" << temperature.getSensorCode();
    }
}

void Supervisor::onGetSensors(QList<Sensor> sensors, QString nodeId){
    for (Sensor sensor : sensors){
        qDebug () << "Sensor: " << sensor.getSensorCode();
    }
}
