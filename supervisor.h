#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include <QObject>
#include <QTimer>
#include <QDebug>

#include "model/temperature.h"
#include "model/sensor.h"
#include "model/humidity.h"

#include "node/nodebus.h"
#include "scheduler.h"
#include "dao/controlnetdb.h"
#include "supervisor_config.h"



class Supervisor : public QObject
{
    Q_OBJECT
public:
    explicit Supervisor(QObject *parent = 0);
    void begin();

private:
    QTimer *initTimer;
    QTimer *initSensorsTimer;
    NodeBus *nodeBus;
    Scheduler *scheduler;
    ControlNetDb *database;
    QList<Module> modules;
    Module getNextModule();

signals:

public slots:
    void onTemperaturesReceived(QList<Temperature> temperatures);
    void onGetSensors(QList<Sensor>, QString nodeId);
    void onSendRequest();
    void onCommandAlerted(QString command, QString nodeId);
    void onTemperatureReceived(Temperature temperature);
    void onHumidityReceived(Humidity humidity);
    void onCommandReceived(QList<Command> commands);
    void onSendInitSensorRequest();



};

#endif // SUPERVISOR_H
