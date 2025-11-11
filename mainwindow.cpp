#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sensorsimulator.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Sensor Dashboard");

    auto *simulator = new SensorSimulator(this);

    connect(simulator, &SensorSimulator::dataUpdated, this, [](const QVector<Sensor> &sensors) {
        qDebug() << "---- New sensor data ----";
        for (const auto &s : sensors) {
            qDebug().noquote() << s.name << ":" << s.value << s.unit
                               << "at" << s.timestamp.toString("hh:mm:ss");
        }
    });

    simulator->start(1000); // generuj dane co sekundę
}

MainWindow::~MainWindow()
{
    delete ui;
}
