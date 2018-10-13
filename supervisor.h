#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include <QObject>
#include <QTimer>
#include <QDebug>

#include "model/temperature.h"
#include "node/nodebus.h"

class Supervisor : public QObject
{
    Q_OBJECT
public:
    explicit Supervisor(QObject *parent = 0);
    void begin();

private:
    QTimer *timer;
    NodeBus *nodeBus;



signals:

public slots:
    void onGetTemperatures(QList<Temperature> temperatures);
    void onSendRequest();



};

#endif // SUPERVISOR_H
