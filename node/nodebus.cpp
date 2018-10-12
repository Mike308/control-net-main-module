#include "nodebus.h"

NodeBus::NodeBus(QObject *parent) : QObject(parent){
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
    QString sensorCnt = data.split("^");

}

void NodeBus::onDataReceived(QString data, QString node){

}




