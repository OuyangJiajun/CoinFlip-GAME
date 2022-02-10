#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include <QDebug>
#include <QLabel>
#include <QTimer>


ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(320,588);
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    setWindowTitle("选择关卡场景");

    //用代码实现菜单栏
    QMenuBar* bar = menuBar();
    setMenuBar(bar);
    QMenu* startMenu = bar->addMenu("开始");
    QAction* quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        close();
    });

    //返回按钮音效
    backSound = new QSound(":/res/BackButtonSound.wav",this);

    //放置返回按钮
    backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //选关按钮音效
    QSound* chooseSound = new QSound(":/res/TapButtonSound.wav",this);

    //创建选择关卡的按钮
    for(int i=0;i<20;i++)
    {
        MyPushButton* menuBtn=new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+i%4*70,130+i/4*70);//使用一层循环实现逻辑上的二维，往往用i%n和i/n
        QLabel* label=new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());//label本身没有设置大小函数，继承QWidget
        label->setText(QString::number(i+1));
        label->move(25+i%4*70,130+i/4*70);
        label->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);//设置文字在label水平居中和垂直居中
        label->setAttribute(Qt::WA_TransparentForMouseEvents);//设置鼠标穿透

        //连接关卡选择按钮与对应关卡
        connect(menuBtn,&QPushButton::clicked,[=](){
            //播放选择关卡音效
            chooseSound->play();

            play=new PlayScene(i+1);
            this->hide();
            play->setGeometry(this->geometry());
            play->show();

            //翻金币场景返回按钮按下与选择关卡场景的连接，注意这个connect只能写在内层，因为只在这个作用域内play实例化了，其他时候play为NULL，play为NULL时play->backBtn会导致异常退出
            connect(play->backBtn,&QPushButton::clicked,[=](){
                //播放返回按钮音效
                play->backSound->play();
                //为了能看到返回按钮的切换图片做了延时
                QTimer::singleShot(500,this,[=](){
                    this->setGeometry(play->geometry());
                    this->show();
                    delete play;
                    play=NULL;
                });
            });
        });
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    //画背景
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,320,588,pix);//在0，0开始画pix，拉伸图片为320*588
    //画背景上的图标
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
