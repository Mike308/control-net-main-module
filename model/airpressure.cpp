#include "airpressure.h"

AirPressure::AirPressure()
{

}

int AirPressure::getId() const
{
    return id;
}

void AirPressure::setId(int value)
{
    id = value;
}

int AirPressure::getSensorId() const
{
    return sensorId;
}

void AirPressure::setSensorId(int value)
{
    sensorId = value;
}

float AirPressure::getPressure() const
{
    return pressure;
}

void AirPressure::setPressure(float value)
{
    pressure = value;
}

QString AirPressure::getDate() const
{
    return date;
}

void AirPressure::setDate(const QString &value)
{
    date = value;
}
