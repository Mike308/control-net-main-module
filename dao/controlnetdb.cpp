#include "controlnetdb.h"

ControlNetDb::ControlNetDb()
{

}

void ControlNetDb::createDataBase(){
    QSqlDatabase controlNetDb = QSqlDatabase::addDatabase("QODBC");
    QString connectionString = "Driver={libmyodbc.so}; DATABASE=";
    connectionString.append(DB_NAME).append(";");
    qDebug () << "Connection string: " << connectionString;
    controlNetDb.setDatabaseName(connectionString);
    controlNetDb.setUserName(DB_USER);
    controlNetDb.setPassword(DB_PASSWORD);
    bool result = controlNetDb.open();
    qDebug() << "Conection result: " << result;

}

void ControlNetDb::insertCommand(Command command){
    QSqlQuery insertCommandQuery;
    insertCommandQuery.prepare("insert scheduled_commands (module_id, command, command_interval) values (:module_id, :command, :command_interval)");
    insertCommandQuery.bindValue(":module_id", command.getModuleId());
    insertCommandQuery.bindValue(":command", command.getCommand());
    insertCommandQuery.bindValue(":command_interval", command.getInterval());
    insertCommandQuery.exec();
}

void ControlNetDb::insertSensor(Sensor sensor){
    QSqlQuery insertSensorQuery;
    insertSensorQuery.prepare("insert sensors (module_id, sensor_type, sensor_code, sensor_slot) values (:module_id, :sensor_type, :sensor_code, :sensor_slot)");
    insertSensorQuery.bindValue(":module_id", sensor.getModuleId());
    insertSensorQuery.bindValue(":sensor_type", sensor.getSensorType());
    insertSensorQuery.bindValue(":sensor_slot", 0);
    insertSensorQuery.exec();
}

void ControlNetDb::insertTemperature(Temperature temperature){
    QSqlQuery insertTemperatureQuery;
    insertTemperatureQuery.prepare("insert temperatures (sensor_id, temperature, date) values (:sensor_id, :temperature, :date)");
    insertTemperatureQuery.bindValue(":sensor_id", temperature.getSensorId());
    insertTemperatureQuery.bindValue(":temperature", temperature.getTemperature());
    insertTemperatureQuery.bindValue(":date", temperature.getDate());
    insertTemperatureQuery.exec();
}

void ControlNetDb::insertHumidity(Humidity humidity){
    QSqlQuery insertHumidityQuery;
    insertHumidityQuery.prepare("insert humidity_table (sensor_id, humidity, date) values (:sensor_id, :humidity, :date)");
    insertHumidityQuery.bindValue(":sensor_id", humidity.getSensorId());
    insertHumidityQuery.bindValue(":humidity", humidity.getHumidity());
    insertHumidityQuery.bindValue(":date", humidity.getDate());
    insertHumidityQuery.exec();
}

void ControlNetDb::insertAirPressure(AirPressure airPressure){
   QSqlQuery insertAirPressureQuery;
   insertAirPressureQuery.prepare("insert into air_pressure (sensor_id, pressure, date) values (:sensor_id, :pressure, :date)");
   insertAirPressureQuery.bindValue(":sensor_id", airPressure.getSensorId());
   insertAirPressureQuery.bindValue(":pressure", airPressure.getPressure());
   insertAirPressureQuery.bindValue(":date", airPressure.getDate());
   insertAirPressureQuery.exec();
}

int ControlNetDb::getModuleId(QString moduleAddress){
    QSqlQuery getModuleIdQuery;
    getModuleIdQuery.prepare("select id from modules where address = :address");
    getModuleIdQuery.bindValue(":address", moduleAddress);
    getModuleIdQuery.executedQuery();
    int id = 0;
    while (getModuleIdQuery.next()){
        id = getModuleIdQuery.value("id").toInt();
    }
    return id;
}


int ControlNetDb::getSensorId(QString sensorAddress){
    QSqlQuery getSensorIdQuery;
    getSensorIdQuery.prepare("select id from sensors where sensor_code = :sensor_code");
    getSensorIdQuery.bindValue(":sensor_code", sensorAddress);
    getSensorIdQuery.executedQuery();
    int id = 0;
    while (getSensorIdQuery.next()){
        id = getSensorIdQuery.value("id").toInt();
    }
    return id;
}

QList<Module> ControlNetDb::getModules(){
    QSqlQuery getModulesQuery;
    QList<Module> modules;
    getModulesQuery.exec("select * from modules");
    while (getModulesQuery.next()){
        Module module;
        module.setAddress(getModulesQuery.value("address").toString());
        module.setName(getModulesQuery.value("name").toString());
        module.setType(getModulesQuery.value("type").toString());
        module.setId(getModulesQuery.value("id").toInt());
        modules.append(module);
    }
    return modules;
}

QList<Command> ControlNetDb::getCommands(){
    QSqlQuery getCommandsQuery;
    QList<Command> commands;
    getCommandsQuery.exec("select * from scheduled_commands");
    while (getCommandsQuery.next()) {
        Command command;
        command.setId(getCommandsQuery.value("id").toInt());
        command.setModuleId(getCommandsQuery.value("module_id").toInt());
        command.setCommand(getCommandsQuery.value("command").toString());
        command.setInterval(getCommandsQuery.value("command_interval").toInt());
        commands.append(command);
    }
    return commands;
}







