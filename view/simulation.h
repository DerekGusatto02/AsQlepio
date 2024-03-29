#ifndef SIMULATION_H
#define SIMULATION_H

#include <QLabel>
#include <QPushButton>
#include <QtCharts>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "model/sensor.h"

class Simulation : public QWidget {
    Q_OBJECT
private:
    std::vector<float> distribution;
    Sensor* _sensor;
    unsigned int _id;
    QLabel* sensorName;

    QPushButton* backToSensor;
    QPushButton* deleteSensor;
    QHBoxLayout* actions;

    QPushButton* startSimulation;
    QChart* simulationGraph;

    QSplineSeries* series;
    QScatterSeries* notHealthySeries;

    QChartView* chartView;

    QVBoxLayout* simulationLayout;
public:
    Simulation(QWidget* parent=0, Sensor* sensor = nullptr);
    void drawSimulationGraph();
    void setDistribution(const std::vector<float>& distribution);
signals:
    void needSimulation(Sensor* sensor);
    void showEditSensor(Sensor* sensor, int id);

public slots:
    void loadSimulation(std::vector<float> distribution);
};

#endif // SIMULATION_H
