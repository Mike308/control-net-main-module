#include "humidity.h"

Humidity::Humidity()
{

}

int Humidity::getId() const
{
    return id;
}

void Humidity::setId(int value)
{
    id = value;
}

int Humidity::getSensorId() const
{
    return sensorId;
}

void Humidity::setSensorId(int value)
{
    sensorId = value;
}

float Humidity::getHumidity() const
{
    return humidity;
}

void Humidity::setHumidity(float value)
{
    humidity = value;
}

QString Humidity::getDate() const
{
    return date;
}

void Humidity::setDate(const QString &value)
{
    date = value;
}
