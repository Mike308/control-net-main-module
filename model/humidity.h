#ifndef HUMIDITY_H
#define HUMIDITY_H
#include <QString>

class Humidity
{

public:
    Humidity();

    int getId() const;
    void setId(int value);

    int getSensorId() const;
    void setSensorId(int value);

    float getHumidity() const;
    void setHumidity(float value);

    QString getDate() const;
    void setDate(const QString &value);

private:
    int id;
    int sensorId;
    float humidity;
    QString date;
};

#endif // HUMIDITY_H
