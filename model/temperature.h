#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include <QString>

class Temperature
{

public:
    Temperature();

    int getId() const;
    void setId(int value);

    int getSensorId() const;
    void setSensorId(int value);

    float getTemperature() const;
    void setTemperature(float value);

    QString getDate() const;
    void setDate(const QString &value);

private:
    int id;
    int sensorId;
    float temperature;
    QString date;
};

#endif // TEMPERATURE_H
