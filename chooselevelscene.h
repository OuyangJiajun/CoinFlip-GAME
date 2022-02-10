#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H
#include "mypushbutton.h"
#include <playscene.h>
#include <QMainWindow>
#include <QSound>

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    //绘图事件
    void paintEvent(QPaintEvent*);

    MyPushButton* backBtn=NULL;
    PlayScene* play=NULL;
    QSound* backSound;

signals:

};

#endif // CHOOSELEVELSCENE_H
