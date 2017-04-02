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
#include "playmusic.h"
#include "qtvlc.h"
#include "qvlcplayer.h"
#include <QDebug>
#include <QTimer>
#include "myhelper.h"
#include "app.h"

PlayMusic::PlayMusic(QObject *parent) : QObject(parent)
{
    initForm();
    initConnect();
}

PlayMusic::~PlayMusic()
{
    delete m_player;
    m_player = NULL;
}

//打开音乐
void PlayMusic::slotOpenMusic(QString name)
{
    if (name.isEmpty())
    {
        emit signalPlayStatue(MUSIC_PAUSE);
        qDebug()<<"当前返回为空";
        return;
    }else
    {
        m_player->Play(name);
        setPlayMusic();

        myHelper::Sleep(100);
        qint64 length = m_player->GetLength();
#if QDEBUG_OUT
//        qDebug() <<name;
//        qDebug()<<"媒体长度："<<length;
#endif

        //打开媒体后，发送媒体信息，包括：媒体长度、当前声音、当前位置
        emit signalSendPlayLength(length);
        //    emit signalSendPlayVolume(m_player->getVolume());
        //    emit signalSendPlayPostion(m_player->GetPos());
        emit signalPlayStatue(MUSIC_PLAY);
        myHelper::Sleep(100);
        emit signalSendPlayingMusic(name);
    }
}

//改变当前播放媒体音量
void PlayMusic::slotSetPlayVolume(int value)
{
    m_player->Volume(value);
}

void PlayMusic::slotSetPlayPostion(qint64 pos)
{
    m_player->SetPlayTime(pos);
}

void PlayMusic::slotReceivePlayCmdMusic(const QString & name)
{
    if (!name.isEmpty()){

        m_player->Play(name);
        this->setPlayMusic();
    }
    else
    {
        m_player->Pause();
    }
}

/*
typedef enum libvlc_state_t {
    libvlc_NothingSpecial = 0,
    libvlc_Opening,
    libvlc_Buffering,
    libvlc_Playing,
    libvlc_Paused,
    libvlc_Stopped,
    libvlc_Ended,
    libvlc_Error
} libvlc_state_t;
*/
void PlayMusic::slotUpdateInterface()
{
    //如果当前没有媒体播放，则不发送信息
//    if (!m_player->IsPlaying())
//    {
//        emit signalPlayStatue(MUSIC_PLAY_END);
//        return;
//    }
    if (libvlc_NothingSpecial == m_player->GetPlayStatue())
    {
        return;
    }
    if (libvlc_Ended == m_player->GetPlayStatue())
    {
        emit signalPlayStatue(MUSIC_PLAY_END);
        return;
    }

    qint64 pos = m_player->GetTime();

    emit signalSendPlayPostion(pos);
}

void PlayMusic::setPlayMusic()
{
    if (!m_player->IsPlaying())
        m_player->Play();
    App::IsPlaying = true;
    App::WriteConfig();
    emit signalPlayStatue(MUSIC_PLAY);
}

//用于接收bottomWidget发送过来的控制信号
void PlayMusic::setPauseMusic()
{
    m_player->Pause();

    emit signalPlayStatue(MUSIC_PAUSE);
}

void PlayMusic::initForm()
{
    m_player = new QVlcPlayer(this);

    //定时更新播放接口信息
    m_pollerTimer = new QTimer(this);
    //start timer to trigger every 300 ms the updateInterface slot
    m_pollerTimer->start(300);
}

void PlayMusic::initConnect()
{
    connect(m_pollerTimer,SIGNAL(timeout()),
            this,SLOT(slotUpdateInterface()));
}

void PlayMusic::sendPlayMusicCmd()
{
    //读取配置文件中播放模式信息，发送不同的命令
    App::ReadConfig();
    int mode = App::AppPlayMode;
    emit signalSendPlayNextMusic(mode);
}

