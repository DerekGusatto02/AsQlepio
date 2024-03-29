#include "controller.h"

Controller::Controller(Model* model, MainWindow* view, QObject* parent) : QObject(parent), model(model), view(view) {
    
    connect(view->getWelcomeWidget(), &Welcome::buttonClicked, view->getWelcomeWidget(), &Welcome::showChooseTypeDialog);
    connect(view, &MainWindow::needToSave, this, &Controller::notifyToSave);
    connect(view, &MainWindow::needToLoad, this, &Controller::notifyToLoad);
    connect(view, &MainWindow::needToReloadSensors, this, &Controller::updateSensors);
    connect(view, &MainWindow::isLoadingEditSensor, this, &Controller::loadEditSensor);
    connect(view, &MainWindow::isLoadingSimulation, this, &Controller::loadSimulation);
    connect(view->getWelcomeWidget()->getChooseTypeDialog(), &ChooseTypeDialog::newSensor, view, &MainWindow::showEditSensor);
}

void Controller::updateSensors(std::string filter){
    (this->view)->loadSensors((this->model)->getSensors_deepCopy(filter));
}


void Controller::handleSensoreDataRequest(unsigned int id){
    Sensor* sensor = (model->getSensor(model->searchSensor(id)))->clone();
    if(view->getEditSensorWidget()!=nullptr){
        view->getEditSensorWidget()->setSensor(sensor);
       } 
}

void Controller::notifyToSave(std::string filepath){
    model->saveSensors(filepath);
}

void Controller::notifyToLoad(std::string filepath){
    model->loadSensors(filepath);
}

void Controller::notifyToDelete(unsigned int id){
    model->deleteSensor(id);
    updateSensors("");
    view->showWelcome();
}

void Controller::sendSimulation(Sensor* sensor){
    std::vector<float> distribution = model->getSimulation(sensor);
    emit simulationReady(distribution);
}

void Controller::sendNewSensor(Sensor* type){
    if(view->getEditSensorWidget()!=nullptr){
        view->getEditSensorWidget()->setSensor(model->sendNewSensor(type));
    }
}

void Controller::handleSaveSensor(Sensor* sensor){

    model->replaceSensor(sensor);
    this->updateSensors("");
}

void Controller::setSimulation(Sensor* sensor){
    if(view->getSimulationWidget()!=nullptr){
        view->getSimulationWidget()->loadSimulation(model->getSimulation(sensor));
    }

}

void Controller::loadEditSensor(){
    connect(view->getEditSensorWidget(), &EditSensor::startSimulation, view, &MainWindow::showSimulation);
    connect(view->getEditSensorWidget(), &EditSensor::sensorDataRequested, this, &Controller::handleSensoreDataRequest);
    connect(view->getEditSensorWidget(), &EditSensor::removeSensor, this, &Controller::notifyToDelete);
    connect(view->getEditSensorWidget(), &EditSensor::backToHome, view, &MainWindow::showWelcome);
    connect(view->getEditSensorWidget(), &EditSensor::getNewSensor, this, &Controller::sendNewSensor);
    connect(view->getEditSensorWidget(), &EditSensor::needToSaveSensor, this, &Controller::handleSaveSensor);
}
void Controller::loadSimulation(){
    connect(view->getSimulationWidget(), &Simulation::showEditSensor, view, &MainWindow::showEditSensor);
    connect(view->getSimulationWidget(), &Simulation::needSimulation, this, &Controller::setSimulation);
}
