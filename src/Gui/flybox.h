#ifndef FLYBOX_H
#define FLYBOX_H

#include <QWidget>

class FlyBox : public QWidget
{
    Q_OBJECT
public:
    explicit FlyBox(QWidget *parent = 0);

    bool setSize(unsigned int m) { size = m; return false; }
    bool setCellCapacity(unsigned int n) { cellCapacity = n; return false; }

signals:

public slots:

private:
    unsigned int size;
    unsigned int cellCapacity;
};

#endif // FLYBOX_H
