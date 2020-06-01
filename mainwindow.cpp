/*
* mainwindow.cpp
*
*  Created on  : Dec 10, 2017
*  Author      : Vinay Divakar
*  website     : www.deeplyemebedded.org
*/

#include<QDebug>
#include<QThread>
#include<QFont>
#include <random>
#include <QRandomGenerator>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

/* Global objects */
//SPI spi_device1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
//    QWSServer::setCursorVisible(false);
    this->setStyleSheet("background-color: white;");

    /* Initialize SPI */
//    if (spi_device1.SPI_DEV1_init(SPIDEV_BYTES_NUM, SPIDEV1_BUS_SPEED_HZ, SPI_SS_LOW,
//                                  SPIDEV_DELAY_US, SPIDEV_DATA_BITS_NUM,
//                                  SPI_MODE3) == -1)
//        qDebug()<<"(Main)spidev1.0 initialization failed\r\n";

//    else
//        qDebug()<<"(Main)spidev1.0 initialized - READY\r\n";

    /* Configure font settings for Label */
    QFont font;
    font.setPointSize(21);
    font.setPixelSize(true);
//    font.setBold(true);
    ui->label_adc_data->setFont(font);
    ui->label_adc_data->setAlignment(Qt::AlignCenter);
    ui->label_adc_data->setStyleSheet("background-color : white; color : green;");

    /* Configure setup for Thank You Label */
    ui->label_ty->setAlignment(Qt::AlignCenter);
    ui->label_ty->setStyleSheet("background-color : white; color : blue;");

    /* Add graph and set the curve line color to green */
    ui->CustomPlot->addGraph();
    ui->CustomPlot->graph(0)->setPen(QPen(Qt::red));
    ui->CustomPlot->graph(0)->setAntialiasedFill(false);

    /* Configure x-Axis as time in secs */
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%s");
    ui->CustomPlot->xAxis->setTicker(timeTicker);
    ui->CustomPlot->axisRect()->setupFullAxesBox();


    /* Configure x and y-Axis to display Labels */
    ui->CustomPlot->xAxis->setTickLabelFont(QFont(QFont().family(),6));
    ui->CustomPlot->yAxis->setTickLabelFont(QFont(QFont().family(),6));
    ui->CustomPlot->xAxis->setLabel("Время (с)");

    /* Make top and right axis visible, but without ticks and label */
    ui->CustomPlot->xAxis2->setVisible(true);
    ui->CustomPlot->yAxis->setVisible(true);

    ui->CustomPlot->xAxis2->setLabelColor("background-color : white; color : blue;");
    ui->CustomPlot->xAxis2->setTickLabelColor("color : yellow;");
    ui->CustomPlot->xAxis2->setSelectedTickLabelColor("color : yellow;");
    qDebug() << ui->CustomPlot->xAxis2->labelColor();
    ui->CustomPlot->xAxis2->setTicks(false);//false
    ui->CustomPlot->yAxis2->setTicks(false);//false
    ui->CustomPlot->xAxis2->setTickLabels(false);//false
    ui->CustomPlot->yAxis2->setTickLabels(false);//false

    /* Set up and initialize the graph plotting timer */
    connect(&timer_plot, SIGNAL(timeout()),this,SLOT(realtimePlot()));
    timer_plot.start(5);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/****************************************************************
 * Function Name : realtimePlot
 * Description   : Displays the real time graph on the GUI
 * Returns       : None
 * Params        : None
 ****************************************************************/
void MainWindow::realtimePlot()
{
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0;//100
    static double lastPointKey = 0;
    double data = 0;
    if(key - lastPointKey > 0.033)//0.002
    {
        data = QRandomGenerator::global()->generateDouble();
//        qDebug() << QString::number(data);
//        adc_data_g = data;
        ui->CustomPlot->graph(0)->addData(key, data);
        lastPointKey = key;
    }

    /* make key axis range scroll right with the data at a constant range of 8. */
    ui->CustomPlot->graph(0)->rescaleValueAxis();
    ui->CustomPlot->xAxis->setRange(key, 5, Qt::AlignRight);
    ui->CustomPlot->replot();
}

/****************************************************************
 * Function Name : on_pushButton_released
 * Description   : Displays THANK YOU! when pressed and released
 * Returns       : None
 * Params        : None
 ****************************************************************/
void MainWindow::on_pushButton_released()
{
    ui->label_ty->setText("THANK YOU!");
}
