#include "supervisor.h"
#include <QDateTime>
Supervisor::Supervisor(QObject *parent) : QObject(parent)
{
    initTimer = new QTimer();
    nodeBus = new NodeBus();
    scheduler = new Scheduler();
    connect(nodeBus, SIGNAL(temperaturesReceived(QList<Temperature>)), this, SLOT(onTemperaturesReceived(QList<Temperature>)));
    connect(nodeBus, SIGNAL(sensorsReceived(QList<Sensor>,QString)), this, SLOT(onGetSensors(QList<Sensor>,QString)));
    connect(nodeBus, SIGNAL(temperatureReceived(float)), this, SLOT(onTemperatureReceived(float)));
    connect(nodeBus, SIGNAL(humidityReceived(float)), this, SLOT(onHumidityReceived(float)));
    connect(nodeBus, SIGNAL(commandReceived(QList<Command>,QString)), this, SLOT(onCommandReceived(QList<Command>)));
    connect(initTimer, SIGNAL(timeout()), this, SLOT(onSendRequest()));
    connect(scheduler, SIGNAL(commandAlerted(QString,QString)), this, SLOT(onCommandAlerted(QString,QString)));
    database = new ControlNetDb();
    database->createDataBase();

}

void Supervisor::begin(){
    modules = database->getModules();
    initTimer->start(30000);
}

void Supervisor::onSendRequest(){
    Module currentModule = getNextModule();
    qDebug () << "Request for command from: " << currentModule.getAddress();
    nodeBus->sendRequest("AT+SENS?", currentModule.getAddress());
}

void Supervisor::onTemperaturesReceived(QList<Temperature> temperatures){
    qDebug () << "Datetime: " << QDateTime::currentDateTime();
    for (Temperature temperature : temperatures){
        qDebug () << "Temperature: " << temperature.getTemperature() << "|" << temperature.getSensorCode();
    }
}

void Supervisor::onGetSensors(QList<Sensor> sensors, QString nodeId){
    for (Sensor sensor : sensors){
        qDebug () << "Sensor: " << sensor.getSensorCode() << " sensor type: " << sensor.getSensorType();
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

void Supervisor::onCommandReceived(QList<Command> commands){
    qDebug () << "Commands received: ";
    for (Command command : commands){
        qDebug () << "Command: " << command.getCommand() << "|" << command.getModuleId();
    }
}

Module Supervisor::getNextModule(){
    static int i = -1;
    ++i;
    qDebug () << "I value: " << i;
    if (i > (modules.length() -1)){
        qDebug() << "STOP...";
        initTimer->stop();
        scheduler->begin();
        i = 0;
    }
    return modules.at(i);
}
