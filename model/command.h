#ifndef COMMAND_H
#define COMMAND_H
#include <QString>
#include <QMetaType>
class Command
{

public:
    Command();
    Command(int id, int moduleId, QString command, int interval);
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
Q_DECLARE_METATYPE(Command)

#endif // COMMAND_H
