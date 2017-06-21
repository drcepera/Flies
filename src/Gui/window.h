#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QStackedWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QScrollArea>
#include <QValidator>
#include <QList>

#include "flybox.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();

private:
    QHBoxLayout * mainLayout;
    QVBoxLayout * inputLayout;
    QScrollArea * scrollArea;
    FlyBox * box;
    QTextEdit * flyInfoOutput;
    QStackedWidget * outputWidgetStack;

    QGroupBox *     boxParamGroupBox;
    QGridLayout *   boxParamGridLayout;
    QGroupBox *     flyInputGroupBox;
    QGridLayout *   flyInputGridLayout;
    QGroupBox *     simulationGroupBox;
    QGridLayout *   simulationGridLayout;

    QLabel *    boxSizeLabel;
    QLineEdit * boxSizeEdit;
    QLabel *    cellCapacityLabel;
    QLineEdit * cellCapacityEdit;
    QLabel *    flyDecisionTimeLabel;
    QLineEdit * flyDecisionTimeEdit;

    QLabel *    infoOutLabel;
    QScrollArea * infoOutScroll;

    QPushButton * addFlyButton;
    QPushButton * startStopSimulationButton;
    QPushButton * clearSimulationButton;

    QValidator * intValidator;
    QValidator * floatValidator;

    QList<QLineEdit*> lineEdits;

private slots:
    void onStartBtnPressed();
};

#endif // WINDOW_H
