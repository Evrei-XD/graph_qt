#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void makePlot();
    void setupePlot();

private:
    Ui::MainWindow *ui;
    QTimer *dataTimer;
//    QSharedPointer *timeTicker;
//    QCPAxisTickerTime *timeTicker;
};
#endif // MAINWINDOW_H
