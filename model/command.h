#ifndef COMMAND_H
#define COMMAND_H
#include <QObject>

class Command : public QObject
{
public:
    Command();
    int getId() const;
    void setId(int value);

    int getModuleId() const;
    void setModuleId(int value);

    QString getCommand() const;
    void setCommand(const QString &value);

    int getInterval() const;
    void setInterval(int value);

private:
    int id;
    int moduleId;
    QString command;
    int interval;

};

#endif // COMMAND_H
