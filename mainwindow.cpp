#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFile>

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
    connect(m_simulator, &SensorSimulator::dataUpdated, this, &MainWindow::onDataUpdated);
    connect(ui->btnStart, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(ui->btnStop, &QPushButton::clicked, this, &MainWindow::onStopClicked);
    connect(ui->btnSave, &QPushButton::clicked, this, &MainWindow::onSaveClicked);
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

void MainWindow::onSaveClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save CSV", "", "CSV Files (*.csv)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot write to file.");
        return;
    }

    QTextStream out(&file);

    // Nagłówek
    out << "Sensor,Value,Unit,Time\n";

    // Zawartość tabeli
    int rows = ui->tableLog->rowCount();
    int cols = ui->tableLog->columnCount();

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            auto *item = ui->tableLog->item(r, c);
            if (item)
                out << item->text();
            if (c < cols - 1)
                out << ",";
        }
        out << "\n";
    }

    file.close();
    QMessageBox::information(this, "Saved", "Data exported successfully.");
}
