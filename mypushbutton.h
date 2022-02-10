#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);//explicit防止隐式调用构造函数

    //重载构造函数，参数1为默认图片，参数2为按下后图片
    MyPushButton(QString normalImg, QString pressImg = "");

    //弹跳特效
    void zoom1();//向下跳
    void zoom2();//向上跳

    //重写鼠标按下和释放事件
    void mousePressEvent(QMouseEvent* ev);
    void mouseReleaseEvent(QMouseEvent* ev);

    //成员属性
    QString normalImgPath;//默认图片路径
    QString pressImgPath;//按下后图片路径

signals:

};

#endif // MYPUSHBUTTON_H
