#ifndef END_H
#define END_H

#include <QMainWindow>

class End : public QMainWindow
{
    Q_OBJECT
public:
    End(int End);

    int ending;

    void paintEvent(QPaintEvent *);

signals:

public slots:
};

#endif // END_H
