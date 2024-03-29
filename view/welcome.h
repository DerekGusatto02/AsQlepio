#ifndef WELCOME_H
#define WELCOME_H

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "chooseTypeDialog.h"

class Welcome : public QWidget {
     Q_OBJECT
private:
    QVBoxLayout* welcomeLayout;

    QHBoxLayout* title;
    QLabel* welcomeLabel;
    QLabel* logotype;
    QLabel* introduction;
    QPushButton* newSensor;
    ChooseTypeDialog* chooseType;

    QLabel* test;
public:
    Welcome(QWidget* parent=0);
    ChooseTypeDialog* getChooseTypeDialog();

signals:
    void buttonClicked();

public slots:
    void showChooseTypeDialog();
};

#endif // WELCOME_H
