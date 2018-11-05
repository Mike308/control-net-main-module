#include "command.h"

Command::Command()
{

}

Command::Command(int id, int moduleId, QString command, int interval){
    this->id = id;
    this->moduleId = moduleId;
    this->command = command;
    this->interval = interval;
}

int Command::getId() const
{
    return id;
}

void Command::setId(int value)
{
    id = value;
}

int Command::getModuleId() const
{
    return moduleId;
}

void Command::setModuleId(int value)
{
    moduleId = value;
}

QString Command::getCommand() const
{
    return command;
}

void Command::setCommand(const QString &value)
{
    command = value;
}

int Command::getInterval() const
{
    return interval;
}

void Command::setInterval(int value)
{
    interval = value;
}
