#include "temperature.h"

Temperature::Temperature()
{

}

int Temperature::getId() const
{
    return id;
}

void Temperature::setId(int value)
{
    id = value;
}

int Temperature::getSensorId() const
{
    return sensorId;
}

void Temperature::setSensorId(int value)
{
    sensorId = value;
}

float Temperature::getTemperature() const
{
    return temperature;
}

void Temperature::setTemperature(float value)
{
    temperature = value;
}

QString Temperature::getDate() const
{
    return date;
}

void Temperature::setDate(const QString &value)
{
    date = value;
}

QString Temperature::getSensorCode() const
{
    return sensorCode;
}

void Temperature::setSensorCode(const QString &value)
{
    sensorCode = value;
}
