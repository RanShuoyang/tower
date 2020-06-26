#include "end.h"
#include "QPainter"
#include <QMessageBox>

End::End(int End)
{
    this->setWindowTitle("TowerDefence");
    this->setWindowIcon(QIcon(":/base.png"));
    this->setFixedSize(1600,830);
    ending=End;
}


void End::paintEvent(QPaintEvent *){
    QString text;
    if(ending==1){text="恭喜你！你赢得了这场紧张刺激的游戏!!!";}
    if(ending==2){text="你太菜了！这么简单你居然都赢不了!!!";}
    QPainter painter(this);
    QPixmap back(":/bg.png");
    painter.drawPixmap(0,0,back);
    QTransform transform;
    painter.setPen(QPen(Qt::black));
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(40);
    painter.setFont(font);
    QFontInfo info=painter.fontInfo();
    info.family();
    info.italic();
    painter.setTransform(transform);
    painter.drawText(rect(), Qt::AlignCenter, text);

}
