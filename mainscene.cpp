#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QSound>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //配置主场景
    setFixedSize(320,588);//设置固定大小
    setWindowIcon(QIcon(":/res/Coin0001.png"));//设置图标，窗口左上角和windows任务栏都用这个
    setWindowTitle("翻金币主场景");//设置标题

    //退出按钮实现
    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();//关闭窗口
    });

    //开始按钮的音效
    QSound* startSound=new QSound(":/res/TapButtonSound.wav",this);

    //开始按钮放置
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    //实例化选择关卡场景
    chooseScene = new ChooseLevelScene;

    //开始按钮按下与选择关卡场景的连接
    connect(startBtn,&MyPushButton::clicked,[=](){
        //播放音效
        startSound->play();
        //弹起动画
        startBtn->zoom1();//因为没有延时，zoom1实际上被zoom2覆盖了
        startBtn->zoom2();
        //自身隐藏并进入选择关卡场景，为了能看到弹起动画做了延时
        QTimer::singleShot(500,this,[=](){
            //设置chooseScene场景的位置
            chooseScene->setGeometry(this->geometry());
            this->hide();
            chooseScene->show();
        });
    });

    //选择关卡场景返回按钮按下与主场景的连接
    connect(chooseScene->backBtn,&QPushButton::clicked,[=](){
        //播放选择关卡场景下返回按钮音效
        chooseScene->backSound->play();
        //为了能看到返回按钮的切换图片做了延时
        QTimer::singleShot(500,this,[=](){
            this->setGeometry(chooseScene->geometry());
            chooseScene->hide();
            this->show();
        });
    });
}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    //画背景
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,320,588,pix);//在0，0开始画pix，拉伸图片为320*588
    //画背景上的图标
    pix.load(":/res/Title.png");
    pix.scaled(pix.width()*0.5,pix.height()*0.5);//对图像进行缩放
    painter.drawPixmap(10,30,pix);
}
