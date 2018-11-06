#include "supervisor.h"
#include <QDateTime>
Supervisor::Supervisor(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    nodeBus = new NodeBus();
    scheduler = new Scheduler();
    connect(nodeBus, SIGNAL(temperaturesReceived(QList<Temperature>)), this, SLOT(onTemperaturesReceived(QList<Temperature>)));
    connect(nodeBus, SIGNAL(sensorsReceived(QList<Sensor>,QString)), this, SLOT(onGetSensors(QList<Sensor>,QString)));
    connect(nodeBus, SIGNAL(temperatureReceived(float)), this, SLOT(onTemperatureReceived(float)));
    connect(nodeBus, SIGNAL(humidityReceived(float)), this, SLOT(onHumidityReceived(float)));
    connect(initTimer, SIGNAL(timeout()), this, SLOT(onSendRequest()));
    connect(scheduler, SIGNAL(commandAlerted(QString,QString)), this, SLOT(onCommandAlerted(QString,QString)));
    database = new ControlNetDb();
    database->createDataBase();

}

void Supervisor::begin(){
    modules = database->getModules();
    for (Module module : modules){
        nodeBus->sendRequest("AT+SENS?", module.getAddress());
    }
}

void Supervisor::onSendRequest(){
    Module currentModule = getNextModule();
    nodeBus->sendRequest("AT+CMD?", currentModule.getAddress());
}

void Supervisor::onTemperaturesReceived(QList<Temperature> temperatures){
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

void Supervisor::onTemperatureReceived(float temperature){
    qDebug () << "Temperature from dht11: " << temperature;
}

void Supervisor::onHumidityReceived(float humidity){
    qDebug () << "Humidity from dht11: " << humidity;
}

void Supervisor::onCommandAlerted(QString command, QString nodeId){
    qDebug () << "Command alerted";
    nodeBus->sendRequest(command, nodeId);
}

void Supervisor::getNextModule(){
    static int i = -1;
    i++;
    if (i > modules.length() -1){
        i = 0;
        initTimer->stop();
    }
    return modules.at(i);
}
