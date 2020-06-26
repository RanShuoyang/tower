#ifndef CHOOSEMODE_H
#define CHOOSEMODE_H

#include <QMainWindow>
#include <QMediaPlayer>

class easymode;
class choosemode : public QMainWindow
{
    Q_OBJECT
public:
    explicit choosemode(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

    QMediaPlayer *sound=nullptr;

    easymode * backmode=nullptr;

    void musicOn();
    void musicOff();
signals:
   //自定义的信号
    void chooseback();

public slots:

};

#endif // CHOOSEMODE_H
