#ifndef INTRODUCE_H
#define INTRODUCE_H

#include <QMainWindow>

#include <choosemode.h>

class introduce : public QMainWindow
{
    Q_OBJECT
public:
    explicit introduce(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

    choosemode * choose_back;


signals:

public slots:
};

#endif // INTRODUCE_H
