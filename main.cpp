#include <QApplication>
#include "view/mainWindow.h"
#include "controller/controller.h"
#include "model/model.h"
#include "model/healthyRange.h"
#include <iostream>
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    //Create model

   /* OxygenSaturation* s = new OxygenSaturation(1,"Oxygen", 98,Range(70,100), new UniformDistribution());
    HeartRate* s1 = new HeartRate(2, std::string("Heart"), 89, Range(30,240), false, new NormalDistribution());
    Temperature* s2 = new Temperature(3, "Temp", 97, Range(32,45), true, new NormalDistribution());
    BloodPressure* s4 = new BloodPressure(4, "Blood", 79, Range(0,300), new UniformDistribution());
    BreathFrequency* s5 = new BreathFrequency(5, "Breath", 78, Range(0,100), 33, true, new SinDistribution());
*/
    std::vector<Sensor*> sensors;

    Model model(sensors);



    //Create view
    MainWindow view;

    //Create controller
    Controller controller(&model, &view);

    //Start
    view.show();
    return app.exec();
}
