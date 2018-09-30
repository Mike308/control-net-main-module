#include "temperature.h"

temperature::temperature()
{

}

int temperature::getId() const
{
    return id;
}

void temperature::setId(int value)
{
    id = value;
}

int temperature::getSensorId() const
{
    return sensorId;
}

void temperature::setSensorId(int value)
{
    sensorId = value;
}

float temperature::getTemperature() const
{
    return temperature;
}

void temperature::setTemperature(float value)
{
    temperature = value;
}

QString temperature::getData() const
{
    return data;
}

void temperature::setData(const QString &value)
{
    data = value;
}
