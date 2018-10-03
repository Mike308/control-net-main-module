#ifndef CONTROLNETDB_H
#define CONTROLNETDB_H

#include <QObject>

#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QList>

#include "config.h"

#include "model/sensor.h"
#include "model/temperature.h"
#include "model/airpressure.h"
#include "model/humidity.h"
#include "model/module.h"
#include "model/command.h"



class ControlNetDb : public QObject
{
    Q_OBJECT

public:
    ControlNetDb();
    void createDataBase();
    void insertTemperature(Temperature temperature);
    void insertSensor(Sensor sensor);
    void insertHumidity(Humidity humidity);
    void insertCommand(Command command);
    void insertAirPressure(AirPressure airPressure);

    QList<Module> getModules();
    QList<Command> getCommands();






};

#endif // CONTROLNETDB_H
