#ifndef SENSOR_H
#define SENSOR_H
#include <QString>
#include <QMetaType>
class Sensor
{

public:
    Sensor();

    int getId() const;
    void setId(int value);

    int getModuleId() const;
    void setModuleId(int value);

    QString getSensorType() const;
    void setSensorType(const QString &value);

    QString getSensorCode() const;
    void setSensorCode(const QString &value);

    int getSensorSlotId() const;
    void setSensorSlotId(int value);

private:
    int id;
    int sensorSlotId;
    int moduleId;
    QString sensorType;
    QString sensorCode;
};
Q_DECLARE_METATYPE(Sensor)
#endif // SENSOR_H
