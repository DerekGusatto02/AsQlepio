#ifndef MODEL_H
#define MODEL_H

#include "sensor.h"
#include <vector>

class Model {
private:
    std::vector<Sensor*> sensors;
public:
    Model(std::vector<Sensor*> sensors);
    Sensor* getSensor(int index) const;
    int searchSensor(unsigned int id) const;
    bool deleteSensor(unsigned int id);
    std::vector<float> getSimulation(Sensor* sensor) const;
    std::vector<Sensor*> getSensors_deepCopy(std::string filter);
    unsigned int getMaxId();
    unsigned int getNextId();
    void replaceSensor(Sensor* newSensor);
    void addSensor(Sensor* newSensor);
    Sensor* sendNewSensor(Sensor* type);
    std::vector<Sensor*> getSensors();



signals:
    void sensorsUpdated(const std::vector<Sensor*> sensors);

public slots:
    void sendSensors(const std::vector<Sensor*> sensors);
    void saveSensors(std::string filepath);
    void loadSensors(std::string filepath);



};

#endif // MODEL_H
