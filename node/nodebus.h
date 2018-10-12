#ifndef NODEBUS_H
#define NODEBUS_H

#include <QObject>


#include "nrfnetwork/qnrf24l01network.h"

#include "model/temperature.h"


class NodeBus : public QObject
{
    Q_OBJECT
public:
    explicit NodeBus(QObject *parent = 0);
    void sendRequest(QString request, QString nodeId);
    void updateNodes(QString nodeId);

private:
    QNRF24L01Network *network;
    QTimer *timer;
    void parseDataFromTemperatureModule(QString data);


signals:
    void temperaturesReceived(QList<Temperature> temperatures);



public slots:
    void onDataReceived(QString data, QString node);
};

#endif // NODEBUS_H
