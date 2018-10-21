#include "nodebus.h"

NodeBus::NodeBus(){
    network = new QNRF24L01Network(RPI_V2_GPIO_P1_15, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_1MHZ);
    connect(network, SIGNAL(receivedMessageFromNode(QString,QString)), this, SLOT(onDataReceived(QString,QString)));
    network->connectToRadio();
    network->selectRecevingPipe(1, 0xF0F0F0F0F101);
    network->selectSendingPipes(0xF0F0F0F0E101);
    network->updateNodeAddressList("0");
    network->startListening();
}

void NodeBus::updateNodes(QString nodeId){
    network->updateNodeAddressList(nodeId);
}

void NodeBus::sendRequest(QString request, QString nodeId){
    network->sendDataToNode(nodeId, request);
}

void NodeBus::parseDataFromTemperatureModule(QString data){
    qDebug () << "Data: " << data;
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
        network->sendDataToNode("0", "AT+DS18B20,1?");
    }
}

void NodeBus::parseSensorsFromModule(QString data, QString node){
    QString sensorCnt = data.split("^").value(0);
    QStringList items = QString(data.split("^").value(1)).split(";");
    static QList<Sensor> sensors = QList<Sensor>();
    for (QString item : items){
        Sensor sensorObj;
        sensorObj.setSensorCode(item);
        sensorObj.setSensorType("temp_sensor");
        sensors.append(sensorObj);
    }
    if (sensors.length() > sensorCnt.toInt()){
        emit sensorsReceived(sensors, node);
    }else{
        network->sendDataToNode(node, "AT+SENS,1?");
    }
}


void NodeBus::onDataReceived(QString data, QString node){
    QString responseId = data.split("=").at(0);
    if (!responseId.compare("+T")){
        parseDataFromTemperatureModule(data.replace("+T=", ""));
    }else if (!responseId.compare("+S")){
        parseSensorsFromModule(data.replace("+S=", ""), node);
    }

}




