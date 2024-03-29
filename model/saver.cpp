#include "saver.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QIODevice>

SensorSaver::SensorSaver(const QVector<Sensor*>& s) : sensors(s) {}

void SensorSaver::saveToFile(const QString& filename) {
    QJsonArray sensorArray;

    for (const Sensor* sensor : sensors) {
        QJsonObject sensorObject = sensor->toJson();
        sensorArray.append(sensorObject);
    }

    QJsonObject mainObject;
    mainObject["sensors"] = sensorArray;

    QJsonDocument doc(mainObject);
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        // gestisci l'errore
        return;
    }

    file.write(doc.toJson());
}
