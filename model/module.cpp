#include "module.h"

Module::Module()
{

}

int Module::getId() const
{
    return id;
}

void Module::setId(int value)
{
    id = value;
}

QString Module::getName() const
{
    return name;
}

void Module::setName(const QString &value)
{
    name = value;
}

QString Module::getType() const
{
    return type;
}

void Module::setType(const QString &value)
{
    type = value;
}
