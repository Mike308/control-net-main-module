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

QString Temperature::getData() const
{
    return data;
}

void Temperature::setData(const QString &value)
{
    data = value;
}
