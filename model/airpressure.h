#ifndef AIRPRESSURE_H
#define AIRPRESSURE_H
#include <QObject>
#include <QString>
class AirPressure
{

public:
    AirPressure();
    int getId() const;
    void setId(int value);

    int getSensorId() const;
    void setSensorId(int value);

    float getPressure() const;
    void setPressure(float value);

    QString getDate() const;
    void setDate(const QString &value);

private:
    int id;
    int sensorId;
    float pressure;
    QString date;
};

#endif // AIRPRESSURE_H
