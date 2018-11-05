#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <QObject>
#include <QTimer>

#include "model/command.h"

class Scheduler : public QObject
{
    Q_OBJECT
public:
    explicit Scheduler(QObject *parent = 0);


signals:
    void commandAlerted(QString command, QString nodeId);

private:
    QTimer *taskTimer;
    bool executeNextCommand = true;
    QList<Command> commandList;
    Command nextCommand();



public slots:
    void onTaskTimerTimeout();

};

#endif // SCHEDULER_H
