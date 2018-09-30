#include "sensor.h"

Sensor::Sensor()
{

}

int Sensor::getId() const
{
    return id;
}

void Sensor::setId(int value)
{
    id = value;
}

int Sensor::getModuleId() const
{
    return moduleId;
}

void Sensor::setModuleId(int value)
{
    moduleId = value;
}

QString Sensor::getSensorType() const
{
    return sensorType;
}

void Sensor::setSensorType(const QString &value)
{
    sensorType = value;
}

QString Sensor::getSensorCode() const
{
    return sensorCode;
}

void Sensor::setSensorCode(const QString &value)
{
    sensorCode = value;
}
