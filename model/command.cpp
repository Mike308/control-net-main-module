#include "command.h"

Command::Command()
{

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
