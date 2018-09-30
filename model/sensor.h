#ifndef SENSOR_H
#define SENSOR_H


class sensor
{
public:
    sensor();

    int getId() const;
    void setId(int value);

    int getModuleId() const;
    void setModuleId(int value);

    QString getSensorType() const;
    void setSensorType(const QString &value);

    QString getSensorCode() const;
    void setSensorCode(const QString &value);

private:
    int id;
    int moduleId;
    QString sensorType;
    QString sensorCode;
};

#endif // SENSOR_H
