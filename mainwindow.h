#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sensorsimulator.h"
#include "chartwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDataUpdated(const QVector<Sensor> &sensors);
    void onStartClicked();
    void onStopClicked();
    void onSaveClicked();

private:
    Ui::MainWindow *ui;
    SensorSimulator *m_simulator;
    ChartWidget *m_chartWidget;

    void setupConnections();
    void setupTable();
};

#endif // MAINWINDOW_H
