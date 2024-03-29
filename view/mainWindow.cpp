#include "mainWindow.h"
#include "model/saver.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    this->setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("AsQlepio");
    setStyleSheet("QMainWindow {background-color: #f5f5f5;} QLabel.title {font-size: 36px;}"
    "QPushButton {border-width: 1px; border-style: solid; border-color: black; border-radius: 15px;}"
    "QPushButton.mainButton {background-color: rgba(78, 198, 58, 0.7);}"
    "QPushButton.mainButton:pressed {background-color: rgba(78, 198, 58, 0.9);}"
    "QPushButton.cancelButton {background-color: rgba(204, 45, 53, 0.7);}"
    "QPushButton.cancelButton:pressed {background-color: rgba(204, 45, 53, 0.85);}"
    "QPushButton.editButton {background-color: rgba(230, 198, 55, 0.7);}"
    "QPushButton.editButton:pressed {background-color: rgba(230, 198, 55, 0.9);}"
    "QScrollArea {background: transparent; border-right: 1px solid #9fa19f;}"
    "QScrollArea QWidget {background: transparent;}");

    home = new QWidget(this);

    menu = menuBar()->addMenu(tr("&File"));
    save = new QAction(tr("Salva"));
    save->setShortcut(Qt::CTRL | Qt::Key_S);
    save->setIcon(QIcon("img/save.png"));
    import = new QAction(tr("Apri..."));
    import->setShortcut(Qt::CTRL | Qt::Key_O);
    import->setIcon(QIcon("img/import.png"));
    menu->addAction(save);
    menu->addAction(import);

    connect(save, &QAction::triggered, this, &MainWindow::saveFile);
    connect(import, &QAction::triggered, this, &MainWindow::loadFile);

    searchEdit = new QLineEdit();
    searchEdit->setPlaceholderText("Cerca sensore...");
    searchEdit->setClearButtonEnabled(true);
    searchEdit->setMaximumWidth(299);

    searchButton = new QPushButton("Cerca");
    searchButton->setFixedSize(QSize(50, 25));

    std::string param = searchEdit->text().toStdString();
    connect(searchButton, &QPushButton::clicked, this, &MainWindow::reloadSensors);
    searchbar = new QHBoxLayout();
    searchbar->addWidget(searchEdit);
    searchbar->addWidget(searchButton);
    searchbar->setAlignment(Qt::AlignTop);

    sensorsPanel = new QVBoxLayout();

    searchResults = new QWidget();
    searchResults->setLayout(sensorsPanel);
    
    sensorsList = new QScrollArea();
    sensorsList->setWidgetResizable(true);
    sensorsList->setWidget(searchResults);
    sensorsList->setMinimumWidth(220);
    sensorsList->setMaximumWidth(355);
    
    left = new QVBoxLayout();
    left->addLayout(searchbar);
    left->addWidget(sensorsList);

    content = new Welcome();

    finalLayout = new QHBoxLayout();
    finalLayout->addLayout(left, 30);
    finalLayout->addWidget(content, 70);

    home->setLayout(finalLayout);

    this->setCentralWidget(home);
    this->sensorWidgets= new std::vector<QWidget*>();
}

void MainWindow::showEditSensor(Sensor* type, int id) {
    delete content;
    content = new EditSensor(type, id, this);
    emit isLoadingEditSensor();

    dynamic_cast<EditSensor*>(content)->requestData(type, id);
    finalLayout->addWidget(content, 70);
}

void MainWindow::showSimulation(Sensor* sensor) {
    delete content;
    content = new Simulation(this, sensor);
    emit isLoadingSimulation();
    finalLayout->addWidget(content, 70);
}

void MainWindow::showWelcome() {
    delete content;
    content = new Welcome();
    finalLayout->addWidget(content, 70);
}

Welcome* MainWindow::getWelcomeWidget(){
    Welcome* welcomeWidget = dynamic_cast<Welcome*>(content);
    if(welcomeWidget){
        return welcomeWidget;
    }
    return nullptr;
}

EditSensor* MainWindow::getEditSensorWidget(){
    EditSensor* editSensorWidget = dynamic_cast<EditSensor*>(content);
    if(editSensorWidget){
        return editSensorWidget;
    }
    return nullptr;
}

Simulation* MainWindow::getSimulationWidget(){
    Simulation* simulationWidget = dynamic_cast<Simulation*>(content);
    if(simulationWidget){
        return simulationWidget;
    }
    return nullptr;
}

void MainWindow::loadSensors(const std::vector<Sensor*>& sensors){
    visualizedSensors.clear();
    visualizedSensors = sensors;
    viewResults();
}

void MainWindow::onSensorsUpdated(const std::vector<Sensor*> sensors) {
    // Update view with the new sensor data
    // ...
}


/* RIVEDERE*/
void MainWindow::viewResults(){
    //Cancella vecchi sensori
    for(QWidget* widget : (*this->sensorWidgets)){
        sensorsPanel->removeWidget(widget);
        delete widget;
    }

    this->sensorWidgets->clear();

    for(std::vector<Sensor*>::const_iterator cit=(this->visualizedSensors).begin(); cit!=(this->visualizedSensors).end(); cit++) {
        QWidget* sensorWidget = new QWidget();
        sensorWidget->setFixedHeight(50);
        QHBoxLayout* layout = new QHBoxLayout(sensorWidget);
        // Create an icon based on the sensor type
        SensorImageVisitor imageVisitor;
        (*cit)->acceptImage(imageVisitor);
        QLabel* iconLabel = imageVisitor.getImage();
        layout->addWidget(iconLabel);
        QLabel* sensorIdLabel = new QLabel(QString::number((*cit)->getId()));
        layout->addWidget(sensorIdLabel);
        QLabel* sensorNameLabel = new QLabel(QString::fromStdString((*cit)->getName()));
        layout->addWidget(sensorNameLabel);
        QPushButton* details = new QPushButton("Dettagli");
        details->setProperty("class", "mainButton");
        details->setFixedSize(QSize(70, 30));;
        layout->addWidget(details);
        unsigned int sens_id = (*cit)->getId();
        Sensor* send_sensor = (*cit);
        connect(details, &QPushButton::clicked, this, [this, sens_id, send_sensor](){this->showEditSensor(send_sensor, sens_id);});
        sensorsPanel->addWidget(sensorWidget);
        sensorsPanel->setAlignment(Qt::AlignTop);

        this->sensorWidgets->push_back(sensorWidget);
    }
}
void MainWindow::saveFile(){
    QString filepath = QFileDialog::getSaveFileName(this, tr("Salva"), "", tr("File di testo (*txt);; Tutti i tipi di file(*)"));
    if(!filepath.isEmpty()){
        emit needToSave(filepath.toStdString());
    }
}

void MainWindow::loadFile(){
    QString filepath = QFileDialog::getOpenFileName(this, tr("Apri"), "", tr("File di testo (*txt);; Tutti i tipi di file(*)"));
    if(!filepath.isEmpty()){
        emit needToLoad(filepath.toStdString());
    }
}

void MainWindow::reloadSensors(){
    std::string filter = searchEdit->text().toStdString();
    if(filter != ""){
        emit needToReloadSensors(filter);
    }else{
        emit needToReloadSensors(std::string(""));
    }

}


void MainWindow::closeEvent(QCloseEvent *event){

    QMessageBox::StandardButton confirmsave = QMessageBox::question(this, "Application", tr("Vuoi salvare?\n"), QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
    if(confirmsave == QMessageBox::Cancel){
        event->ignore();
    }else if(confirmsave == QMessageBox::Yes){
        MainWindow::saveFile();
        event->accept();
    }

}
