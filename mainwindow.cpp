#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    graphicsView = new ClickableGraphicsView();
    ui->graphicsLayout->addWidget(graphicsView);
    QString filename = "sm.jpg";
    QImage image(filename);
    graphicsView->setImage(image);
    connect(ui->closePointsButton, SIGNAL(clicked()),
            graphicsView, SLOT(closePoints()));
    connect(ui->clearItemsButton, SIGNAL(clicked()),
            graphicsView, SLOT(clearItems()));
    connect(ui->cancelButton, SIGNAL(clicked()),
            graphicsView, SLOT(cancel()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

