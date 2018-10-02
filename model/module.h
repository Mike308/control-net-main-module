#ifndef MODULE_H
#define MODULE_H
#include <QObject>

class Module : public QObject
{
    Q_OBJECT
public:
    Module();

    int getId() const;
    void setId(int value);

    QString getName() const;
    void setName(const QString &value);

    QString getType() const;
    void setType(const QString &value);

    QString getAddress() const;
    void setAddress(const QString &value);

private:
    int id;
    QString name;
    QString type;
    QString address;

};

#endif // MODULE_H
