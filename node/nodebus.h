#ifndef NODEBUS_H
#define NODEBUS_H

#include <QObject>
#include <QList>

#include "nrfnetwork/qnrf24l01network.h"

#include "model/temperature.h"
#include "model/sensor.h"

#include "dao/controlnetdb.h"


class NodeBus : public QObject
{
    Q_OBJECT
public:
    NodeBus();
    void sendRequest(QString request, QString nodeId);
    void updateNodes(QString nodeId);

private:
    QNRF24L01Network *network;
    void parseDataFromTemperatureModule(QString data);
    void parseSensorsFromModule(QString data, QString node);

signals:
    void temperaturesReceived(QList<Temperature> temperatures);
    void sensorsReceived(QList<Sensor> sensors, QString nodeId);



public slots:
    void onDataReceived(QString data, QString node);
};

#endif // NODEBUS_H
