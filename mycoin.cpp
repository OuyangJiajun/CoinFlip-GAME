#include "mycoin.h"
#include <QDebug>

MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
{

}

MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret=pix.load(btnImg);
    if(!ret)
    {
        QString str=QString("图片 %1 加载失败").arg(btnImg);
        qDebug()<<str;
        return;
    }
    setFixedSize(pix.width(),pix.height());//按钮大小
    setStyleSheet("QPushButton{border:0px;}");//可以以css的语法来对组件设置样式
    setIcon(pix);
    setIconSize(QSize(pix.width(),pix.height()));//icon要占满按钮

    //新建定时器对象
    timer1=new QTimer(this);
    timer2=new QTimer(this);

    //监听timer1实现金翻银
    connect(timer1,&QTimer::timeout,[=]()mutable{
        QString str=QString(":/res/Coin000%1.png").arg(min++);
        bool ret = pix.load(str);
        if(!ret)
        {
            qDebug()<<str<<"加载失败";
            return;
        }
        setIcon(pix);
        if(min>max)
        {
            timer1->stop();
            min=1;
            isAnimation=false;
        }
    });

    //监听timer2实现银翻金
    connect(timer2,&QTimer::timeout,[=]()mutable{
        QString str=QString(":/res/Coin000%1.png").arg(max--);
        bool ret = pix.load(str);
        if(!ret)
        {
            qDebug()<<str<<"加载失败";
            return;
        }
        setIcon(pix);
        if(max<min)
        {
            timer2->stop();
            max=8;
            isAnimation=false;
        }
    });
}

void MyCoin::changeFlag()
{
    if(flag)//金翻银
    {
        flag=false;
        isAnimation=true;
        timer1->start(30);

    }
    else//银翻金
    {
        flag=true;
        isAnimation=true;
        timer2->start(30);
    }
}

 void MyCoin::mousePressEvent(QMouseEvent* ev)
 {
     if(isAnimation||isWin)
         return;
     else
         return QPushButton::mousePressEvent(ev);
 }
