#include <QCoreApplication>
#include <QDebug>
#include <QList>

#include "dao/controlnetdb.h"
#include "model/module.h"
#include "model/temperature.h"
#include "model/sensor.h"
#include "supervisor.h"



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    ControlNetDb controlnetDb;
//    controlnetDb.createDataBase();
//    QList<Module> modules = controlnetDb.getModules();
//    qDebug() << "Size: " << modules.size();

//    for (Module module : modules){
//        qDebug () << module.getName();
//    }
    qRegisterMetaType<Temperature>();
    qRegisterMetaType<Sensor>();
    qRegisterMetaType<QList<Sensor>>();
    qRegisterMetaType<QList<Temperature>>();
    Supervisor s;
    s.begin();



    return a.exec();
}
