#ifndef NODEBUS_H
#define NODEBUS_H

#include <QObject>
#include <QList>
#include <QTimer>

#include "nrfnetwork/qnrf24l01network.h"

#include "model/temperature.h"
#include "model/sensor.h"

#include "dao/controlnetdb.h"
#include "nodebus_config.h"


class NodeBus : public QObject
{
    Q_OBJECT
public:
    NodeBus();
    void sendRequest(QString request, QString nodeId);
    void updateNodes(QString nodeId);

private:
    QNRF24L01Network *network;
    QTimer *timeoutTimer;
    QString currentNodeId;
    QString currentRequest;
    void parseDataFromTemperatureModule(QString data, QString node);
    void parseSensorsFromModule(QString data, QString node);
    void parseDataFromHumidityModule(QString data);

signals:
    void temperaturesReceived(QList<Temperature> temperatures);
    void humidityReceived(float humidity);
    void temperatureReceived(float temperature);
    void sensorsReceived(QList<Sensor> sensors, QString nodeId);



public slots:
    void onDataReceived(QString data, QString node);
    void onTimeoutRequest();
};

#endif // NODEBUS_H
