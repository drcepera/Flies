#include "window.h"

Window::Window(QWidget *parent)
    : QWidget(parent)
{
    // create graphical and fly info output area
    scrollArea = new QScrollArea;
    box = new FlyBox;
    flyInfoOutput = new QTextEdit;
    outputWidgetStack = new QStackedWidget;
    outputWidgetStack->addWidget(box);
    outputWidgetStack->addWidget(flyInfoOutput);
    scrollArea->addScrollBarWidget(outputWidgetStack, Qt::AlignLeft | Qt::AlignTop);

    QString groupBoxStyle = "QGroupBox {border: 2px solid gray; border-radius: 5;}"
            " QGroupBox::title {border-radius: 6px; subcontrol-position:top left; top:-3px}";

    // create user input widgets
    // box parameters
    boxParamGroupBox = new QGroupBox("Box settings");
    //boxParamGroupBox->setStyleSheet(groupBoxStyle);
    boxParamGridLayout = new QGridLayout;
    boxSizeLabel = new QLabel("Fly box size:");
    boxParamGridLayout->addWidget(boxSizeLabel,0,0,1,1,Qt::AlignRight);
    boxSizeEdit = new QLineEdit("1");
    boxParamGridLayout->addWidget(boxSizeEdit,0,1,1,1,Qt::AlignLeft);
    cellCapacityLabel = new QLabel("Cell capacity:");
    boxParamGridLayout->addWidget(cellCapacityLabel,1,0,1,1,Qt::AlignRight);
    cellCapacityEdit = new QLineEdit("1");
    boxParamGridLayout->addWidget(cellCapacityEdit,1,1,1,1,Qt::AlignLeft);
    boxParamGroupBox->setLayout(boxParamGridLayout);

    // fly parameters
    flyInputGroupBox = new QGroupBox("New fly settings");
    //flyInputGroupBox->setStyleSheet(groupBoxStyle);
    flyInputGridLayout = new QGridLayout;
    flyDecisionTimeLabel = new QLabel("Fly decision time (s):");
    flyInputGridLayout->addWidget(flyDecisionTimeLabel,0,0,1,1,Qt::AlignRight);
    flyDecisionTimeEdit = new QLineEdit("1");
    flyInputGridLayout->addWidget(flyDecisionTimeEdit,0,1,1,1,Qt::AlignLeft);
    addFlyButton = new QPushButton("Add");
    flyInputGridLayout->addWidget(addFlyButton,1,0,1,1,Qt::AlignRight);
    flyInputGroupBox->setLayout(flyInputGridLayout);

    // simulation control
    simulationGroupBox = new QGroupBox("Simulation control");
    //simulationGroupBox->setStyleSheet(groupBoxStyle);
    simulationGridLayout = new QGridLayout;
    startStopSimulationButton = new QPushButton("Start");
    simulationGridLayout->addWidget(startStopSimulationButton,0,0,1,1,Qt::AlignLeft);
    clearSimulationButton = new QPushButton("Clear");
    simulationGridLayout->addWidget(clearSimulationButton,0,1,1,1,Qt::AlignRight);
    clearSimulationButton->setEnabled(false);
    simulationGroupBox->setLayout(simulationGridLayout);

    // build user input layout
    inputLayout = new QVBoxLayout;
    inputLayout->addWidget(boxParamGroupBox);
    inputLayout->addWidget(flyInputGroupBox);
    inputLayout->addWidget(simulationGroupBox);
    inputLayout->addStretch();


    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(inputLayout);
    setLayout(mainLayout);

}

Window::~Window()
{

}
