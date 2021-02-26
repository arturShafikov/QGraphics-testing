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
    connect(ui->clearItemsButton, SIGNAL(clicked()),
            graphicsView, SLOT(clearItems()));
    connect(ui->cancelButton, SIGNAL(clicked()),
            graphicsView, SLOT(cancel()));
    connect(ui->boundButton, SIGNAL(clicked()),
            graphicsView, SLOT(drawBoundingRect()));
    connect(ui->deletePointButton, SIGNAL(clicked()),
            graphicsView, SLOT(deletePoint()));
    connect(ui->createButton, SIGNAL(clicked()),
            graphicsView, SLOT(enableCreationMode()));
    connect(ui->editButton, &QPushButton::clicked,
            graphicsView, &ClickableGraphicsView::enableEditMode);
    connect(ui->hideButton, &QPushButton::clicked,
            this, &MainWindow::hideButtonChecked);
    ui->hideButton->setCheckable(true);
    ui->editButton->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::hideButtonChecked(bool checked)
{
    if (checked) {
        ui->hideButton->setText("Show");
    } else {
        ui->hideButton->setText("Hide");
    }
    graphicsView->hide(checked);
}

