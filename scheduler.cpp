#include "scheduler.h"
#include <QDebug>

Scheduler::Scheduler(QObject *parent) : QObject(parent)
{
    Command getTemperature(1, 0, "AT+DS18B20?", 3600);
    Command getDHT11(2, 1, "AT+DHT11?", 3600);
    commandList.append(getTemperature);
    commandList.append(getDHT11);
    taskTimer = new QTimer();
    connect(taskTimer, SIGNAL(timeout()), this, SLOT(onTaskTimerTimeout()));
}

void Scheduler::begin(){
    taskTimer->start(60000);
}

void Scheduler::onTaskTimerTimeout(){
    Command currentCommand = nextCommand();
    emit commandAlerted(currentCommand.getCommand(), QString::number(currentCommand.getModuleId()));
}

Command Scheduler::nextCommand(){
    static int i = -1;
    i++;
    if (i > commandList.length() - 1){
        i = 0;
    }
    return commandList.at(i);
}
