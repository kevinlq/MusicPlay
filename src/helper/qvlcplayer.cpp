#include "qvlcplayer.h"
#include "vlc/vlc.h"
#include "vlc/libvlc_media.h"
#include <qmath.h>
#include <QStringList>
#include <QTextCodec>

// VLC的事件管理
void OnVLC_EndReached(const libvlc_event_t *event, void *data);
void OnVLC_PositionChanged(const libvlc_event_t *event, void *data);

QVlcPlayer::QVlcPlayer(QObject *parent)
    : QObject(parent),
      m_pVLC_Inst(NULL),
      m_pVLC_Player(NULL),
      m_pfn(NULL)
{
}

//
QVlcPlayer::~QVlcPlayer()
{
    this->Release();
}

//播放媒体
bool QVlcPlayer::Play(QString strPath)
{
    if (!m_pVLC_Inst)
    {
        this->Init();
    }
    if (strPath.isEmpty() || !m_pVLC_Inst)
    {
        return false;
    }

    this->Stop();

    bool bRet = false;
    libvlc_media_t *m;

#if defined(Q_OS_WIN)
    m_filePath = strPath.replace("/","\\",Qt::CaseSensitive);
#elif defined(Q_OS_LINUX)
    m_filePath = strPath;
#endif
    //将文件路径进行编码转换(不转换的话不能识别中文,进而会出现错误)
    m_filePath = UnicodeToUTF8(m_filePath);

    m = libvlc_media_new_path(m_pVLC_Inst,m_filePath.toAscii());
    if (m)
    {
        m_pVLC_Player = libvlc_media_player_new_from_media(m);
        if (m_pVLC_Player)
        {
            libvlc_media_player_play(m_pVLC_Player);
            // 事件管理
            libvlc_event_manager_t *vlc_evt_man = libvlc_media_player_event_manager(m_pVLC_Player);
            libvlc_event_attach(vlc_evt_man, libvlc_MediaPlayerEndReached, ::OnVLC_EndReached, this);
            libvlc_event_attach(vlc_evt_man, libvlc_MediaPlayerPositionChanged, ::OnVLC_PositionChanged, this);
            bRet = true;
        }
        libvlc_media_release(m);
    }
    return bRet;
}

void QVlcPlayer::Play()
{
    if (m_pVLC_Player)
    {
        libvlc_media_player_play(m_pVLC_Player);
    }
}

//暂停
void QVlcPlayer::Pause()
{
    if (m_pVLC_Player)
    {
        libvlc_media_player_pause(m_pVLC_Player);
    }
}

//停止播放媒体
void QVlcPlayer::Stop()
{
    if (m_pVLC_Player)
    {
        libvlc_media_player_stop(m_pVLC_Player);    /*stop playing*/
        libvlc_media_player_release(m_pVLC_Player); /*Free the media_player*/
        m_pVLC_Player = NULL;
    }
}

void QVlcPlayer::Volume(int nVol)
{
    if (m_pVLC_Player)
    {
        libvlc_audio_set_volume(m_pVLC_Player,nVol);
    }
}

//增加音量
void QVlcPlayer::VolumeIncrease()
{
    if (m_pVLC_Player)
    {
        int nVol = libvlc_audio_get_volume(m_pVLC_Player);
        Volume((int)ceil(nVol * 1.1));
    }
}

//减小音量
void QVlcPlayer::VolumeReduce()
{
    if (m_pVLC_Player)
    {
        int nVol = libvlc_audio_get_volume(m_pVLC_Player);
        Volume((int)floor(nVol * 0.9));
    }
}

void QVlcPlayer::SeekTo(int nPos)
{
    if (m_pVLC_Player)
    {
        libvlc_media_player_set_position(m_pVLC_Player, nPos/(float)100.0);
    }
}

//快进
void QVlcPlayer::SeekForward()
{
    int nPos = GetPos();
    //SeekTo(ceil(nPos * 1.1));
    SeekTo(nPos + 10);
}

//快退
void QVlcPlayer::SeekBackward()
{
    int nPos = GetPos();
    //SeekTo(floor(nPos * 0.9));
    SeekTo(nPos - 10);
}

void QVlcPlayer::SetCallback(pfnPosChanged pfn)
{
    m_pfn = pfn;
}

pfnPosChanged QVlcPlayer::GetCallback()
{
    return m_pfn;
}

bool QVlcPlayer::IsOpen()
{
    return NULL != m_pVLC_Player;
}

bool QVlcPlayer::IsPlaying()
{
    if (m_pVLC_Player)
    {
        return libvlc_media_player_is_playing(m_pVLC_Player);
    }

    return FALSE;
}

bool QVlcPlayer::IsPause()
{
    bool tem;
    if (m_pVLC_Player)
    {
        int state = libvlc_media_player_get_state(m_pVLC_Player);
        switch(state)
        {
        case libvlc_Paused:
        case libvlc_Stopped:
            tem = true;
            break;
        default:
            break;
        }
    }else{
        tem = false;
    }
    return tem;
}

//获取文件当前播放的位置
int QVlcPlayer::GetPos()
{
    if (m_pVLC_Player)
    {
        return (int)(100 * libvlc_media_player_get_position(m_pVLC_Player));
    }

    return 0;
}

//获取时间:当前播放的时间
qint64 QVlcPlayer::GetTime()
{
    if (m_pVLC_Player)
    {
        return libvlc_media_player_get_time(m_pVLC_Player);
    }

    return 0;
}

//设置当天媒体播放的时间，实现快进，快退
void QVlcPlayer::SetPlayTime(qint64 time)
{
    if (m_pVLC_Player)
    {
        libvlc_media_player_set_time(m_pVLC_Player,time);
    }
}

//获取长度:当前媒体的总时间长度
qint64 QVlcPlayer::GetLength()
{
    if (m_pVLC_Player)
    {
        return libvlc_media_player_get_length(m_pVLC_Player);
    }
    return 0;
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
int QVlcPlayer::GetPlayStatue()
{
    if (m_pVLC_Player)
    {
        return libvlc_media_player_get_state(m_pVLC_Player);
    }
    return 0;
}

//VLC实例初始化
void QVlcPlayer::Init()
{
    if (!m_pVLC_Inst)
    {
        m_pVLC_Inst = libvlc_new(0,NULL);
    }

    m_filePath = "";
}

//unicode转utf8
QString QVlcPlayer::UnicodeToUTF8(const QString &strWide)
{
    QString strUtf8;
    QStringList t;
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    for (int i = 0; i <strWide.length(); i+=4)
    {
        t.append(strWide.mid(i,4));
    }
    foreach (const QString &str, t) {
        strUtf8.append(str);
    }

    return codec->fromUnicode(strUtf8);
}

void QVlcPlayer::Release()
{
    this->Stop();

    if (m_pVLC_Inst)
    {
        libvlc_release(m_pVLC_Inst);
        m_pVLC_Inst = NULL;
    }
}

void OnVLC_EndReached(const libvlc_event_t *event,void *data)
{

}

void OnVLC_PositionChanged(const libvlc_event_t *event, void *data)
{
    switch (event->type)
    {
    case libvlc_MediaPlayerPositionChanged:
    {
        float fPos = event->u.media_player_position_changed.new_position;
        QVlcPlayer *pAVPlayer = (QVlcPlayer *) data;

        if (pAVPlayer)
        {
            pfnPosChanged pfn = pAVPlayer->GetCallback();

            if (pfn)
            {
                pfn(pAVPlayer, int(fPos * 100));
            }
        }
    }
        break;
    case libvlc_MediaPlayerSnapshotTaken:
        break;
    default:
        break;
    }
}
