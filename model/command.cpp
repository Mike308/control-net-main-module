#include "command.h"

command::command()
{

}

int command::getId() const
{
    return id;
}

void command::setId(int value)
{
    id = value;
}

int command::getModuleId() const
{
    return moduleId;
}

void command::setModuleId(int value)
{
    moduleId = value;
}

QString command::getCommand() const
{
    return command;
}

void command::setCommand(const QString &value)
{
    command = value;
}

int command::getInterval() const
{
    return interval;
}

void command::setInterval(int value)
{
    interval = value;
}
