#include "simulation.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>

Simulation::Simulation(QWidget* parent, Sensor* sensor) : QWidget(parent), _sensor(sensor) {
    sensorName = new QLabel(QString::fromStdString(_sensor->getName()));
    sensorName->setProperty("class", "title");
    sensorName->setAlignment(Qt::AlignCenter);

    backToSensor = new QPushButton("Indietro");
    backToSensor->setProperty("class", "editButton");
    backToSensor->setFixedSize(200, 30);
    startSimulation = new QPushButton("Avvia simulazione");
    startSimulation->setProperty("class", "mainButton");
    startSimulation->setFixedSize(200, 30);
    connect(startSimulation, &QPushButton::clicked, this, [this](){emit needSimulation(this->_sensor);});
    int sens_id = _sensor->getId();
    Sensor* send_sensor = _sensor;
    connect(backToSensor, &QPushButton::clicked, this, [this, sens_id, send_sensor](){ emit showEditSensor(send_sensor, sens_id);});

    actions = new QHBoxLayout();
    actions->addWidget(backToSensor);
    actions->addWidget(startSimulation);

    simulationGraph = new QChart();
    chartView = new QChartView(simulationGraph);
    chartView->setMinimumWidth(750);
    chartView->setMinimumHeight(300);

    simulationLayout = new QVBoxLayout(this);
    simulationLayout->addStretch();
    simulationLayout->addWidget(sensorName);
    simulationLayout->addLayout(actions);
    simulationLayout->addWidget(startSimulation, 1, Qt::AlignHCenter);
    simulationLayout->addWidget(chartView);
    simulationLayout->addStretch();
}

void Simulation::drawSimulationGraph() {
    delete series;
    delete notHealthySeries;

    std::vector<float> data = this->distribution;

    series = new QSplineSeries();
    QPen pen(QColor("black")); 
    series->setPen(pen);
    series->setName("Andamento misurazioni");

    notHealthySeries = new QScatterSeries();
    notHealthySeries->setColor(QColor("red")); 
    notHealthySeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    notHealthySeries->setName("Valori anormali");

    int i = 0;
    for(auto it=data.begin(); it!=data.end(); ++i, it++) {

        if(!_sensor->isHealthy(*it)) {
            notHealthySeries->append(i, *it);
        }
        series->append(i, *it);
    }

    QList<QAbstractAxis*> axes = simulationGraph->axes();
    for(QAbstractAxis* axis : axes){
        simulationGraph->removeAxis(axis);
        delete axis;
    }
    QValueAxis* axisX = new QValueAxis();
    axisX->setRange(0, 24);
    axisX->setTickCount(24);
    axisX->setLabelFormat("%d");

    QValueAxis* axisY = new QValueAxis();
    axisY->setRange(_sensor->getRange().getMinimum(), _sensor->getRange().getMinimum());

    simulationGraph->addAxis(axisX, Qt::AlignBottom);
    simulationGraph->addAxis(axisY, Qt::AlignRight);
    

    simulationGraph->addSeries(series);
    simulationGraph->addSeries(notHealthySeries);
    
    chartView->setRenderHint(QPainter::Antialiasing);
    simulationLayout->addWidget(chartView);
    simulationLayout->addStretch();
}


void Simulation::loadSimulation(std::vector<float> distribution){
    this->distribution = distribution;
    this->drawSimulationGraph();
}

