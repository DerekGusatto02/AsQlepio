#include "model.h"
#include "sensor.h"
#include "mesureDistribution.h"
#include "saver.h"
#include "loader.h"
#include <QString>
#include <iostream>
#include <typeinfo>

Model::Model(std::vector<Sensor*> sensors) {
    this->sensors = sensors;
}

Sensor* Model::getSensor(int index) const {
    return sensors[index]->clone();
}

int Model::searchSensor(unsigned int id) const{
    int index = -1;
    int i = 0;
    for(auto it=sensors.begin(); it != sensors.end() && index == -1; it++){
        if((*it)->getId() == id){
            index = i;
        }
        i++;
    }

    return index;
}
bool Model::deleteSensor(unsigned int id){
    int index = searchSensor(id);
    if(index != -1){
        sensors.erase(sensors.begin() + index);
        return true;
    }
    return false;
}

std::vector<float> Model::getSimulation(Sensor* sensor) const {
    MesureDistribution* md = (sensor->getMesureDistribution());
    std::vector<float> simulation = md->getDistribution(sensor->getRange());
    return simulation;
}


void Model::saveSensors(std::string filepath){
    SensorSaver* s = new SensorSaver(QVector<Sensor*>(this->sensors.begin(), this->sensors.end()));
    s->saveToFile(QString::fromStdString(filepath));
}
void Model::loadSensors(std::string filepath){
    SensorLoader* l = new SensorLoader;
    this->sensors = l->loadFromFile(QString::fromStdString(filepath));
}

std::vector<Sensor*> Model::getSensors(){
    return this->sensors;
}

std::vector<Sensor*> Model::getSensors_deepCopy(std::string filter){
    std::vector<Sensor*> copy;
    if(filter == ""){
        for(const Sensor* sensor : this->getSensors()){
            copy.push_back(sensor->clone());
        }
    }else{
        for(const Sensor* sensor : this->sensors){
            if((std::to_string(sensor->getId()).find(filter) != std::string::npos) || ((sensor->getName()).find(filter) != std::string::npos)) {// If the filter is a substring of the ID
                copy.push_back(sensor->clone());
            }
        }
    }

    return copy;
}

unsigned int Model::getMaxId(){
    unsigned int max = 0;
    for(auto it=sensors.begin(); it != sensors.end(); it++){
        if((*it)->getId() > max){
            max = (*it)->getId();
        }
    }
    return max;

}
unsigned int Model::getNextId(){
    return this->getMaxId()+1;
}

void Model::replaceSensor(Sensor* newSensor){
    unsigned int id = newSensor->getId();
    unsigned int index = this->searchSensor(id);
    delete sensors[index];
    sensors[index] = newSensor;
}

void Model::addSensor(Sensor* newSensor){
    sensors.push_back(newSensor);
}

Sensor* Model::sendNewSensor(Sensor* type){
    Sensor* newSensor = type->clone();
    delete type;
    newSensor->setId(this->getNextId());
    this->addSensor(newSensor);
    return newSensor->clone();
}
