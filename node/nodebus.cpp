#include "nodebus.h"

NodeBus::NodeBus(){
    timeoutTimer = new QTimer();
    network = new QNRF24L01Network(RPI_V2_GPIO_P1_15, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_1MHZ);
    connect(network, SIGNAL(receivedMessageFromNode(QString,QString)), this, SLOT(onDataReceived(QString,QString)));
    connect(timeoutTimer, SIGNAL(timeout()), this, SLOT(onTimeoutRequest()));
    network->connectToRadio();
    network->selectRecevingPipe(1, 0xF0F0F0F0F101);
    network->selectSendingPipes(0xF0F0F0F0E101);
    network->updateNodeAddressList("0");
    network->updateNodeAddressList("1");
    network->startListening();
}

void NodeBus::updateNodes(QString nodeId){
    network->updateNodeAddressList(nodeId);
}

void NodeBus::sendRequest(QString request, QString nodeId){
    currentNodeId = nodeId;
    currentRequest = request;
    network->sendDataToNode(nodeId, request);
    timeoutTimer->start(4000);
}

void NodeBus::parseDataFromTemperatureModule(QString data, QString node){
#if DEBUG == 1
    qDebug () << "Data to parsed from temperature module: " << data;
#endif
    QString sensorCnt = data.split("^").value(0);
    QStringList sensors = QString(data.split("^").value(1)).split(";");
    static QList<Temperature> temperatures = QList<Temperature>();

    for (QString sensor : sensors){
        float temperature = sensor.split("#").value(0).toFloat();
        QString sensorAdress = sensor.split("#").value(1);
        Temperature temperatureObj;
        temperatureObj.setSensorCode(sensorAdress);
        temperatureObj.setTemperature(temperature);
        temperatures.append(temperatureObj);
    }
    if (temperatures.length() > sensorCnt.toInt()){
        emit temperaturesReceived(temperatures);
        temperatures.clear();
    }else{
        network->sendDataToNode(node, "AT+DS18B20,1?");
    }
}

void NodeBus::parseSensorsFromModule(QString data, QString node){
#if DEBUG == 1
    qDebug () << "Data to parsed from module: " << data << "|" << node;
#endif
    QString sensorCnt = data.split("^").value(0);
    if (data.contains(";")){
        QStringList items = QString(data.split("^").value(2)).split(";");
        QString sensorType = QString(data.split("^").value(1));
        static QList<Sensor> sensors = QList<Sensor>();
        for (QString item : items){
            Sensor sensorObj;
            sensorObj.setSensorCode(item);
            sensorObj.setSensorType(sensorType);
            sensors.append(sensorObj);
        }
        if (sensors.length() > sensorCnt.toInt()){
            emit sensorsReceived(sensors, node);
        }else{
            network->sendDataToNode(node, "AT+SENS,1?");
        }
    }else{
        QList<Sensor> sensors = QList<Sensor>();
        QString sensorType = QString(data.split("^").value(1));
        QString sensorAddress = data.replace("^", "");
        Sensor sensor;
        sensor.setSensorCode(sensorAddress);
        sensor.setSensorType(sensorType);
        sensors.append(sensor);
        emit sensorsReceived(sensors, node);
    }
}

void NodeBus::parseDataFromHumidityModule(QString data){
    QStringList items = data.split(";");
    float humidity = QString(items.value(0)).toFloat();
    float temperature = QString(items.value(1)).toFloat();
    emit temperatureReceived(temperature);
    emit humidityReceived(humidity);
}

void NodeBus::parseCommandsFromModule(QString data, QString node){
    if (data.contains("^")){
        QStringList items = data.split("^");
        QList<Command> commands = QList<Command>();
        for (QString item : items){
            Command command(0, node.toInt(), item, 0);
            commands.append(command);
        }
        emit commandReceived(commands, node);
    }else{
        QList<Command> commands = QList<Command>();
        Command command(0, node.toInt(), data, 0);
        commands.append(command);
        emit commandReceived(commands, node);
    }
}


void NodeBus::onDataReceived(QString data, QString node){
#if DEBUG == 1
    qDebug () << "Received data from node: " << data << "|" << node;
#endif
    timeoutTimer->stop();
    QString responseId = data.split("=").at(0);
    if (!responseId.compare("+T")){
        parseDataFromTemperatureModule(data.replace("+T=", ""), node);
    }else if (!responseId.compare("+S")){
        parseSensorsFromModule(data.replace("+S=", ""), node);
    }else if (!responseId.compare("+H*T")){
        parseDataFromHumidityModule(data.replace("+H*T=", ""));
    }else if (!responseId.compare("+CMD")){
        parseCommandsFromModule(data.replace("+CMD=", ""), node);
    }
}

void NodeBus::onTimeoutRequest(){
#if DEBUG == 1
    qDebug () << "Request repeated..." << currentRequest << "|" << currentNodeId;
#endif
    sendRequest(currentRequest, currentNodeId);
}




