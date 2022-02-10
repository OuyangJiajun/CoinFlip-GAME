#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "mypushbutton.h"
#include <QMainWindow>
#include "dataconfig.h"
#include "mycoin.h"
#include <QSound>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum);

    //绘图事件
    void paintEvent(QPaintEvent*);

    int levelIndex;//记录所选关卡
    MyPushButton* backBtn=NULL;
    int gameArray[4][4];//维护当前关卡具体数据的二维数组
    MyCoin* coinBtn[4][4];//维护当前关卡具体数据的二维mycoin数组
    bool isWin;//胜利的标志
    QSound* backSound;

signals:
};

#endif // PLAYSCENE_H
