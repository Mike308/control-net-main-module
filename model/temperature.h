#ifndef TEMPERATURE_H
#define TEMPERATURE_H


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

    QString getData() const;
    void setData(const QString &value);

private:
    int id;
    int sensorId;
    float Temperature;
    QString data;
};

#endif // TEMPERATURE_H
