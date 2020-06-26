#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class button : public QPushButton
{
    Q_OBJECT
public:
    button(QString normalImg,QString pressImg="");
    QString normalImgPath;
    QString pressImgPath;

    void down();
    void up();
signals:

public slots:
};

#endif // BUTTON_H
