#include "mypushbutton.h"
#include <QString>
#include <QDebug>
#include <qpropertyanimation.h>

MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
{

}

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    normalImgPath = normalImg;
    pressImgPath = pressImg;
    QPixmap pix;
    bool ret = pix.load(normalImg);//加载成功返回true，失败false
    if(!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }
    setFixedSize(pix.width(),pix.height());//给按钮设置固定大小
    setStyleSheet("QPushButton{border:0px;}");//给按钮设置不规则图片的样式，样式语法自行百度，这里的作用是去掉图片白边
    setIcon(pix);//给按钮设置图标
    setIconSize(QSize(pix.width(), pix.height()));//设置图标大小
}

void MyPushButton::zoom1()//按下动画
{
    //创建动态对象
   QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");
   //设置事件间隔
   animation->setDuration(200);
   //起始位置
   animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
   //结束位置
   animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
   //设置弹跳曲线
   animation->setEasingCurve(QEasingCurve::OutBounce);
   //执行动画
   animation->start();
}

void MyPushButton::zoom2()//弹起动画
{
    //创建动态对象
   QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");
   //设置事件间隔
   animation->setDuration(200);
   //起始位置
   animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
   //结束位置
   animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
   //设置弹跳曲线
   animation->setEasingCurve(QEasingCurve::OutBounce);
   //执行动画
   animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent* ev)
{
    if(this->pressImgPath!="")
    {
        QPixmap pix;
        bool ret = pix.load(pressImgPath);//加载成功返回true，失败false
        if(!ret)
        {
            qDebug()<<"图片加载失败";
            return;
        }
        setFixedSize(pix.width(),pix.height());//给按钮设置固定大小
        setStyleSheet("QPushButton{border:0px;}");//给按钮设置不规则图片的样式，样式语法自行百度，这里的作用是去掉图片白边
        setIcon(pix);//给按钮设置图标
        setIconSize(QSize(pix.width(), pix.height()));//设置图标大小
    }

    //鼠标按下就拦截，因此还要让父类执行切换图片外的其他内容
    return QPushButton::mousePressEvent(ev);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent* ev)
{
    if(this->pressImgPath!="")//说明有按下切换图片，释放就要切换回来
    {
        QPixmap pix;
        bool ret = pix.load(normalImgPath);//加载成功返回true，失败false
        if(!ret)
        {
            qDebug()<<"图片加载失败";
            return;
        }
        setFixedSize(pix.width(),pix.height());//给按钮设置固定大小
        setStyleSheet("QPushButton{border:0px;}");//给按钮设置不规则图片的样式，样式语法自行百度，这里的作用是去掉图片白边
        setIcon(pix);//给按钮设置图标
        setIconSize(QSize(pix.width(), pix.height()));//设置图标大小
    }
    //鼠标释放就拦截，因此还要让父类执行切换图片外的其他内容
    return QPushButton::mouseReleaseEvent(ev);
}
