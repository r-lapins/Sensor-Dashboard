#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_simulator(new SensorSimulator(this))
    , m_chartWidget(new ChartWidget(this))
{
    ui->setupUi(this);
    setWindowTitle("Sensor Dashboard");

    // dodaj wykres do layoutu
    auto *layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());
    if (layout)
        layout->insertWidget(1, m_chartWidget); // między LCD a tabelą

    setupConnections();
    setupTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    connect(m_simulator, &SensorSimulator::dataUpdated, this, &MainWindow::onDataUpdated);
    connect(ui->btnStart, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(ui->btnStop, &QPushButton::clicked, this, &MainWindow::onStopClicked);
}

void MainWindow::setupTable()
{
    ui->tableLog->setColumnCount(4);
    ui->tableLog->setHorizontalHeaderLabels({"Sensor", "Value", "Unit", "Time"});
    ui->tableLog->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::onStartClicked()
{
    m_simulator->start(1000);
}

void MainWindow::onStopClicked()
{
    m_simulator->stop();
}

void MainWindow::onDataUpdated(const QVector<Sensor> &sensors)
{
    // aktualizacja LCD
    for (const auto &s : sensors) {
        if (s.name == "Temperature") ui->lcdTemp->display(s.value);
        else if (s.name == "Pressure") ui->lcdPress->display(s.value);
        else if (s.name == "Humidity") ui->lcdHum->display(s.value);
    }

    // aktualizacja wykresu
    m_chartWidget->updateData(sensors);

    // dodanie logu do tabeli
    int row = ui->tableLog->rowCount();
    ui->tableLog->insertRow(row);

    for (const auto &s : sensors) {
        ui->tableLog->setItem(row, 0, new QTableWidgetItem(s.name));
        ui->tableLog->setItem(row, 1, new QTableWidgetItem(QString::number(s.value, 'f', 2)));
        ui->tableLog->setItem(row, 2, new QTableWidgetItem(s.unit));
        ui->tableLog->setItem(row, 3, new QTableWidgetItem(s.timestamp.toString("hh:mm:ss")));
        ++row;
        ui->tableLog->insertRow(row);
    }
}
