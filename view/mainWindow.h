#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "welcome.h"
#include "editSensor.h"
#include "simulation.h"
#include "chooseTypeDialog.h"
#include "model/sensor.h"
#include "sensorImageVisitor.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QMenuBar>
#include <QScrollArea>

class MainWindow : public QMainWindow {
private:
    Q_OBJECT
    std::vector<Sensor*> visualizedSensors;

    QWidget* home;
    QMenu* menu;
    QAction *save, *import;

    QVBoxLayout* left;
    QVBoxLayout* sensorsPanel;
    QScrollArea* sensorsList;
    QWidget* searchResults;

    QHBoxLayout* searchbar;
    QLineEdit* searchEdit;
    QPushButton* searchButton;
    
    QWidget* content;
    QHBoxLayout* finalLayout;
    std::vector<QWidget*>* sensorWidgets;

    void closeEvent(QCloseEvent *event) override;

public:
    MainWindow(QWidget* parent=0);
    Welcome* getWelcomeWidget();
    EditSensor* getEditSensorWidget();
    Simulation* getSimulationWidget();
    void viewResults();
    void onSensorsUpdated(const std::vector<Sensor*> sensors);

    void loadFile();

signals:
    void needToSave(std::string filepath); //signal per salvare su file
    void needToLoad(std::string filepath); //signal per caricare da file
    void needToReloadSensors(std::string filter); //signar ricerca
    void isLoadingEditSensor(); //signal aprendo Edit
    void isLoadingSimulation(); //signal aprendo Simulation
    //void showSensorDetails(Sensor* sensor, int id);

public slots:
    void saveFile();
    void showWelcome();
    void showEditSensor(Sensor* type, int id);//id = -1 -> create
   // void showEditSensorfromButton(QVariant variant);
    void showSimulation(Sensor* sensor);
    void loadSensors(const std::vector<Sensor*>& sensors);
    void reloadSensors();


};

#endif // MAINWINDOW_H
