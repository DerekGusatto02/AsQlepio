#include "welcome.h"



Welcome::Welcome(QWidget* parent) : QWidget(parent) {
    setStyleSheet("QLabel.title {color: #3c9020;}");

    welcomeLabel = new QLabel("Benvenuto in ");
    welcomeLabel->setProperty("class", "title");

    QImage* logo = new QImage(":/img/logotype.png");

    logotype = new QLabel();
    logotype->setPixmap(QPixmap::fromImage(*logo));
    logotype->adjustSize();

    title = new QHBoxLayout();
    title->addWidget(welcomeLabel);
    title->addWidget(logotype);
    title->setAlignment(Qt::AlignHCenter);

    introduction = new QLabel("AsQlepio è un software di simulazione di sensori che riproduce le funzionalità di un monitor ospedaliero.\nÈ possibile simulare 5 diversi sensori e visualizzare i dati raccolti in un grafico.\nPer iniziare, crea un nuovo sensore.");
    introduction->setAlignment(Qt::AlignHCenter);
    introduction->setContentsMargins(0, 30, 0, 30);

    newSensor = new QPushButton("Crea nuovo sensore");
    newSensor->setProperty("class", "mainButton");
    newSensor->setFixedSize(160, 30);
    newSensor->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    
    welcomeLayout = new QVBoxLayout(this);
    welcomeLayout->addStretch();
    welcomeLayout->addLayout(title);
    welcomeLayout->addWidget(introduction);
    welcomeLayout->addWidget(newSensor, 1, Qt::AlignHCenter);
    welcomeLayout->setAlignment(Qt::AlignCenter);
    welcomeLayout->addStretch();

    connect(newSensor, &QPushButton::clicked, this, [this]() {emit buttonClicked();});
    chooseType = new ChooseTypeDialog();
}


void Welcome::showChooseTypeDialog() {
    chooseType->show();
}

ChooseTypeDialog* Welcome::getChooseTypeDialog(){
    return this->chooseType;
}
