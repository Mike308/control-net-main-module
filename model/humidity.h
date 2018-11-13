#ifndef HUMIDITY_H
#define HUMIDITY_H
#include <QString>
#include <QMetaType>

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

    QString getSensorCode() const;
    void setSensorCode(const QString &value);

private:
    int id;
    int sensorId;
    float humidity;
    QString date;
    QString sensorCode;
};
Q_DECLARE_METATYPE(Humidity)
#endif // HUMIDITY_H
