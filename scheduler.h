#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <QObject>

class Scheduler : public QObject
{
    Q_OBJECT
public:
    explicit Scheduler(QObject *parent = 0);

signals:

public slots:
};

#endif // SCHEDULER_H