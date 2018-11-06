#ifndef NODEBUS_H
#define NODEBUS_H

#include <QObject>
#include <QList>
#include <QTimer>

#include "nrfnetwork/qnrf24l01network.h"

#include "model/temperature.h"
#include "model/sensor.h"
#include "model/command.h"

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
    void parseCommandsFromModule(QString data, QString node);

signals:
    void temperaturesReceived(QList<Temperature> temperatures);
    void humidityReceived(float humidity);
    void temperatureReceived(float temperature);
    void sensorsReceived(QList<Sensor> sensors, QString node);
    void commandReceived(QList<Command> commands, QString node);



public slots:
    void onDataReceived(QString data, QString node);
    void onTimeoutRequest();
};

#endif // NODEBUS_H
