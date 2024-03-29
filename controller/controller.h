#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "view/mainWindow.h"
#include "model/model.h"

class Controller : public QObject {
    Q_OBJECT
private:
    Model* model;
    MainWindow* view;

public:
    Controller(Model* model, MainWindow* view, QObject* parent=0);


signals:
    void simulationReady(std::vector<float> distribution);

public slots:
    void handleSensoreDataRequest(unsigned int id);
    void updateSensors(std::string filter);
    void notifyToSave(std::string filepath);
    void notifyToLoad(std::string filepath);
    void notifyToDelete(unsigned int id);
    void sendSimulation(Sensor* sensor);
    void loadEditSensor();
    void loadSimulation();
    void sendNewSensor(Sensor* type);
    void handleSaveSensor(Sensor* sensor);
    void setSimulation(Sensor* sensor);


};

#endif // CONTROLLER_H
