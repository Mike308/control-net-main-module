#include "supervisor.h"
#include <QDateTime>
Supervisor::Supervisor(QObject *parent) : QObject(parent)
{
    initTimer = new QTimer();
    nodeBus = new NodeBus();
    scheduler = new Scheduler();
    connect(nodeBus, SIGNAL(temperaturesReceived(QList<Temperature>)), this, SLOT(onTemperaturesReceived(QList<Temperature>)));
    connect(nodeBus, SIGNAL(sensorsReceived(QList<Sensor>,QString)), this, SLOT(onGetSensors(QList<Sensor>,QString)));
    connect(nodeBus, SIGNAL(temperatureReceived(Temperature)), this, SLOT(onTemperatureReceived(Temperature)));
    connect(nodeBus, SIGNAL(humidityReceived(Humidity)), this, SLOT(onHumidityReceived(Humidity)));
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
    static int moduleCnt = 0;
    if (moduleCnt < modules.length()){
        Module currentModule = getNextModule();
#if DEBUG == 1
        qDebug () << "Request for command from: " << currentModule.getAddress();
#endif
        nodeBus->sendRequest("AT+CMD?", currentModule.getAddress());
        moduleCnt++;
    }else{
        initTimer->stop();
        moduleCnt = 0;
        scheduler->begin();
    }
}

void Supervisor::onSendInitSensorRequest(){
}

void Supervisor::onTemperaturesReceived(QList<Temperature> temperatures){
#if DEBUG == 1
    qDebug () << "Datetime: " << QDateTime::currentDateTime();
#endif
    for (Temperature temperature : temperatures){
        int sensorId = database->getSensorId(temperature.getSensorCode());
        qDebug () << "Sensor Id: " << sensorId << "for: " << temperature.getSensorCode() << "value: " << temperature.getTemperature();
        temperature.setSensorId(sensorId);
        temperature.setDate(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"));
#if INSERT_INTO_DB == 1
        database->insertTemperature(temperature);
#endif
    }
}

void Supervisor::onGetSensors(QList<Sensor> sensors, QString nodeId){
    for (Sensor sensor : sensors){
        sensor.setModuleId(database->getModuleId(nodeId));
#if INSERT_INTO_DB == 1
        database->insertSlotSensor(sensor.getSensorCode());
#endif
        sensor.setSensorSlotId(database->getLastInsertedSlot());
#if INSERT_INTO_DB == 1
        if (!database->checkIfSensorExists(sensor.getSensorCode())){
            database->insertSensor(sensor);
        }
#endif

#if DEBUG == 1
        qDebug () << "Sensor: " << sensor.getSensorType() << "|" << sensor.getSensorCode();
#endif

    }
    initTimer->start(30000);
}

void Supervisor::onTemperatureReceived(Temperature temperature){
#if DEBUG == 1
    qDebug () << "Temperature from dht11: " << temperature.getTemperature();
#endif
    temperature.setDate(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"));
    temperature.setSensorId(database->getSensorId(temperature.getSensorCode()));
    database->insertTemperature(temperature);
}

void Supervisor::onHumidityReceived(Humidity humidity){
#if DEBUG == 1
    qDebug () << "Humidity from dht11: " << humidity.getHumidity();
#endif
    humidity.setDate(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"));
    humidity.setSensorId(database->getSensorId(humidity.getSensorCode()));
    database->insertHumidity(humidity);
}

void Supervisor::onCommandAlerted(QString command, QString nodeId){
#if DEBUG == 1
    qDebug () << "Command alerted";
#endif
    nodeBus->sendRequest(command, nodeId);
}

void Supervisor::onCommandReceived(QList<Command> commands, QString nodeId){
    initTimer->stop();
#if DEBUG == 1
    qDebug () << "Commands received: ";
#endif
    for (Command command : commands){
#if DEBUG == 1
        qDebug () << "Command: " << command.getCommand() << "|" << command.getModuleId();
#endif
        if (!database->checkIfCommandExists(command.getCommand(), nodeId)){
            int moduleId = database->getModuleId(nodeId);
            command.setModuleId(moduleId);
            database->insertCommand(command);
        }
    }
    nodeBus->sendRequest("AT+SENS?", QString::number(commands.value(0).getModuleId()));
}

Module Supervisor::getNextModule(){
    static int i = -1;
    ++i;
#if DEBUG == 1
    qDebug () << "I value: " << i;
#endif
    if (i > (modules.length() -1)){
#if DEBUG == 1
        qDebug() << "STOP...";
#endif
        i = 0;
    }
    return modules.at(i);
}
