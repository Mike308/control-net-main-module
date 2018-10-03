#ifndef MODULE_H
#define MODULE_H
#include <QString>

class Module
{

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
