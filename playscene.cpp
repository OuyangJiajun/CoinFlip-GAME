#include "playscene.h"
#include <QMenuBar>
#include <QPainter>
#include <QDebug>
#include <QLabel>
#include "mycoin.h"
#include <QPropertyAnimation>

PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
{

}

PlayScene::PlayScene(int levelNum)
{
    levelIndex=levelNum;

    setFixedSize(320,588);
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    setWindowTitle("翻金币场景");

    //用代码实现菜单栏
    QMenuBar* bar = menuBar();
    setMenuBar(bar);
    QMenu* startMenu = bar->addMenu("开始");
    QAction* quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        close();
    });

    //添加音效资源
    backSound = new QSound(":/res/BackButtonSound.wav",this);
    QSound* flipSound= new QSound(":/res/ConFlipSound.wav",this);
    QSound* winSound= new QSound(":/res/LevelWinSound.wav",this);

    //放置返回按钮
    backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    QLabel* label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");//设置字体
    font.setPointSize(20);//设置字号
    label->setFont(font);//将字体格式设置到label
    QString str = QString("level:%1").arg(levelIndex);
    label->setText(str);
    label->setGeometry(30,height()-50,120,50);//同时设置大小和区域，相当于move和setfixsize

    //初始化当前关卡的二维数组
    dataConfig config;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            gameArray[i][j]=config.mData[levelIndex][i][j];
        }
    }

    //创建中心游戏场景
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            //创建金币下面的灰色背景
            QLabel* label=new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode(1).png"));
            label->setParent(this);
            label->move(57+i*50,200+j*50);

            //根据当前关卡的二维数组创建金币或银币
            MyCoin* coin;
            if(gameArray[i][j]==1)
            {
                coin = new MyCoin(":/res/Coin0001.png");
            }
            else
            {
                coin = new MyCoin(":/res/Coin0008.png");
            }
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);

            //给金币的属性赋初值
            coin->posX=i;
            coin->posY=j;
            coin->flag=gameArray[i][j];

            //创建好后放入二维mycoin数组维护
            coinBtn[i][j]=coin;

            //胜利后弹出图片
            QLabel* winLabel = new QLabel;
            QPixmap tmpPix;
            tmpPix.load(":/res/LevelCompletedDialogBg.png");
            winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
            winLabel->setPixmap(tmpPix);
            winLabel->setParent(this);
            winLabel->move((width()-tmpPix.width())*0.5,-tmpPix.height());

            //点击金币翻转
            connect(coin,&MyCoin::clicked,[=](){
                //播放翻金币音效
                flipSound->play();
                //翻转的过程中不让点
                for(int i=0; i<4;i++)
                {
                    for(int j=0;j<4;j++)
                    {
                        coinBtn[i][j]->isWin=true;
                    }
                }
                coin->changeFlag();
                gameArray[i][j]=gameArray[i][j]==0?1:0;//同时修改维护的二维数组
                //延时翻转周围金币
                QTimer::singleShot(300,this,[=](){
                    if(coin->posX+1<=3)//翻转右侧金币
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        gameArray[coin->posX+1][coin->posY]=gameArray[coin->posX+1][coin->posY]==0?1:0;
                    }
                    if(coin->posX-1>=0)//翻转左侧金币
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        gameArray[coin->posX-1][coin->posY]=gameArray[coin->posX-1][coin->posY]==0?1:0;
                    }
                    if(coin->posY+1<=3)//翻转下侧金币
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        gameArray[coin->posX][coin->posY+1]=gameArray[coin->posX][coin->posY+1]==0?1:0;
                    }
                    if(coin->posY-1>=0)//翻转上侧金币
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        gameArray[coin->posX][coin->posY-1]=gameArray[coin->posX][coin->posY-1]==0?1:0;
                    }

                    //翻转完可以动了，还原
                    for(int i=0; i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            coinBtn[i][j]->isWin=false;//翻转的过程中不让点
                        }
                    }

                    //判断是否胜利
                    isWin=true;
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(coinBtn[i][j]->flag==false)
                            {
                                isWin=false;
                                break;
                            }
                        }
                    }
                    if(isWin==true)
                    {
                        //游戏胜利，标志置true，屏蔽鼠标点击
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                coinBtn[i][j]->isWin=true;
                            }
                        }
                        //把胜利图片放下来
                        QPropertyAnimation* animation=new QPropertyAnimation(winLabel,"geometry");
                        animation->setDuration(1000);
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                        //胜利音效
                        winSound->play();
                    }
                });
            });
        }
    }



}

void PlayScene::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    //背景
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,width(),height(),pix);
    //图标
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
