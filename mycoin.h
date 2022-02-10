#ifndef MYCOIN_H
#define MYCOIN_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    explicit MyCoin(QWidget *parent = nullptr);
    //参数传入的金币路径或者银币路径
    MyCoin(QString btnImg);
    //实现coin翻转
    void changeFlag();
    //重写鼠标按下和释放事件，在翻转时不让继续点击
    void mousePressEvent(QMouseEvent*);

    int posX,posY;//当前金币所在位置
    bool flag;//当前金币的正反
    QTimer* timer1;//金翻银定时器
    QTimer* timer2;//银翻金定时器
    int min=1;
    int max=8;
    bool isAnimation=false;//标志是否正在进行动画
    bool isWin=false;//是否胜利的标志

signals:

};

#endif // MYCOIN_H
