#include "button.h"
#include "QDebug"
#include <QPropertyAnimation>
button::button(QString normalImg,QString pressImg){
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;
    QPixmap pixmap;
    pixmap.load(normalImgPath);
    bool ret = pixmap.load(normalImgPath);
    if(!ret){
        qDebug()<<normalImg<<"加载失败";
        return;
    }
    //设置固定图片大小
    this->setFixedSize(pixmap.width(),pixmap.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:Opx;}");
    //设置图标
    this->setIcon(pixmap);
    //设置图标大小
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}
void button::down(){
    QPropertyAnimation * animation=new QPropertyAnimation(this,"geometry");
    //设置动画区间间隔
    animation->setDuration(200);

    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+5,this->width(),this->height()));

    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
void button::up(){
    QPropertyAnimation * animation=new QPropertyAnimation(this,"geometry");
    //设置动画区间间隔
    animation->setDuration(200);

    animation->setStartValue(QRect(this->x(),this->y()+5,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
