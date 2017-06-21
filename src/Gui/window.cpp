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
    scrollArea->setWidget(outputWidgetStack);

//    QString groupBoxStyle = "QGroupBox {border: 2px solid gray; border-radius: 5;}"
//            " QGroupBox::title {border-radius: 6px; subcontrol-position:top left; top:-3px}";

    // create user input widgets
    // box parameters
    boxParamGroupBox = new QGroupBox("Box settings");
    //boxParamGroupBox->setStyleSheet(groupBoxStyle);
    boxParamGridLayout = new QGridLayout;
    boxSizeLabel = new QLabel("Fly box size:");
    boxParamGridLayout->addWidget(boxSizeLabel,0,0,1,1,Qt::AlignRight);
    boxSizeEdit = new QLineEdit("1");
//    boxSizeEdit->setInputMask("9");
    boxParamGridLayout->addWidget(boxSizeEdit,0,1,1,1,Qt::AlignLeft);
    cellCapacityLabel = new QLabel("Cell capacity:");
    boxParamGridLayout->addWidget(cellCapacityLabel,1,0,1,1,Qt::AlignRight);
    cellCapacityEdit = new QLineEdit("1");
//    cellCapacityEdit->setInputMask("900");
    boxParamGridLayout->addWidget(cellCapacityEdit,1,1,1,1,Qt::AlignLeft);
    boxParamGroupBox->setLayout(boxParamGridLayout);

    // fly parameters
    flyInputGroupBox = new QGroupBox("New fly settings");
    //flyInputGroupBox->setStyleSheet(groupBoxStyle);
    flyInputGridLayout = new QGridLayout;
    flyDecisionTimeLabel = new QLabel("Fly decision time (s):");
    flyInputGridLayout->addWidget(flyDecisionTimeLabel,0,0,1,1,Qt::AlignRight);
    flyDecisionTimeEdit = new QLineEdit;
//    flyDecisionTimeEdit->setInputMask("009.d");
    flyDecisionTimeEdit->setText("1");
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

    infoOutLabel = new QLabel;
//    infoOutLabel->setMaximumWidth(300);
    infoOutLabel->setWordWrap(true);
    infoOutScroll = new QScrollArea;
    infoOutScroll->setWidgetResizable(true);
    infoOutScroll->setMaximumHeight(50);
    infoOutScroll->setVisible(false);
//    infoOutScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    infoOutScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    infoOutScroll->setWidget(infoOutLabel);
    inputLayout->addWidget(infoOutScroll);
    inputLayout->addStretch();

    // fill main layout
    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(inputLayout);
    setLayout(mainLayout);

    // set validators to input lines
    intValidator = new QIntValidator(1,999);
    boxSizeEdit->setValidator(intValidator);
    cellCapacityEdit->setValidator(intValidator);
    floatValidator = new QDoubleValidator(0.1, 99.9, 1);
    flyDecisionTimeEdit->setValidator(floatValidator);
    // ..and make list of them
    lineEdits << boxSizeEdit << cellCapacityEdit << flyDecisionTimeEdit;
    // .. and set tips for lineEdits
    boxSizeEdit->setToolTip("1-999 integers");
    cellCapacityEdit->setToolTip("1-999 integers");
    flyDecisionTimeEdit->setToolTip("0,1-99,9 comma separated");

    // connect controls signals
    connect(this->startStopSimulationButton,SIGNAL(clicked(bool)), SLOT(onStartBtnPressed()));

}

Window::~Window()
{

}

void Window::onStartBtnPressed()
{
    infoOutLabel->setText("");
    infoOutScroll->setVisible(false);
    for(int i=0; i<lineEdits.size(); i++)
    {
        if(!lineEdits[i]->hasAcceptableInput())
        {
            lineEdits[i]->setStyleSheet("background-color: rgb(180,50,50)");
            return;
        }
        else
        {
            lineEdits[i]->setStyleSheet("background-color: palette(base)");
        }
    }

    if( ! box->setSize(boxSizeEdit->text().toInt()) )
    {
        infoOutLabel->setText(infoOutLabel->text() + "<font color=red>Cannot set such size due to flies positions!</font>");
        infoOutScroll->setVisible(true);
    }
    if( ! box->setSize(boxSizeEdit->text().toInt()) )
    {
        infoOutLabel->setText(infoOutLabel->text() + "<br>" + "<font color=red>Cannot set such capacity due to flies and size configuration!</font>");
        infoOutScroll->setVisible(true);
    }
}
