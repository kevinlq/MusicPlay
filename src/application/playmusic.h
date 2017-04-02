/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2016-03-11
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:基于Qt的音乐播放器--音乐播放控制实现
Function:进行音乐播放的逻辑控制
**************************************************/
#ifndef PLAYMUSIC_H
#define PLAYMUSIC_H

#include <QObject>
#include "controlvalues.h"

class QtVlc;
class QVlcPlayer;
class QTimer;

class PlayMusic : public QObject
{
    Q_OBJECT
public:
    explicit PlayMusic(QObject *parent = 0);
    ~PlayMusic();

Q_SIGNALS:
    void signalPlayStatue(int);                 //当前播放状态
    void signalSendPlayLength(qint64);          //发送媒体长度
    void signalSendPlayVolume(int);             //发送当前媒体音量
    void signalSendPlayPostion(qint64);         //发送当前媒体播放位置
    void signalSendPlayingMusic(const QString &);//发送当前正在播放的歌曲，用于解析歌词
    void signalSendCurPlayTime(qint64);          //发送当前播放时间
    void signalSendPlayNextMusic(int mode);     //播放完毕后发送播放下一首信号

public  Q_SLOTS:
    void slotOpenMusic(QString name);
//    void slotSetPlayOrPause(int state);
    void slotSetPlayVolume(int);                    //设置播放音量
    void slotSetPlayPostion(qint64);                //设置播放位置
    void slotReceivePlayCmdMusic(const QString&);   //接收请求回来的歌曲进行播放

private Q_SLOTS:
    void slotUpdateInterface();                     //更新播放接口信息

public:
    void setPlayMusic();
    void setPauseMusic();
private:
    void initForm();
    void initConnect();

    void sendPlayMusicCmd();
private:
    QVlcPlayer *m_player;
    QTimer *m_pollerTimer;
};

#endif // PLAYMUSIC_H
