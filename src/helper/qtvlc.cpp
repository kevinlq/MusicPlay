#include "qtvlc.h"
#include <QDebug>

// VLC的事件管理
void OnVLC_EndReached(const libvlc_event_t *event, void *data);
void OnVLC_PositionChanged(const libvlc_event_t *event, void *data);

QtVlc::QtVlc(QObject *parent) : QObject(parent)
{
    m_vlcInst = NULL;
    m_vlcPlayer = NULL;
    m_vlcMedia = NULL;
    m_pfn = NULL;
    m_filePath = "";        //默认播放路径为空
    m_isPlaying = false;    //默认没有播放
}

//析构函数
QtVlc::~QtVlc()
{
    //this->Release();
}

//打开播放媒体路径
void QtVlc::setOpen(QString filePath)
{
    //转换媒体文件路径
#if defined(Q_OS_WIN)
    m_filePath = filePath.replace("/","\\",Qt::CaseSensitive);
#elif defined(Q_OS_LINUX)
    m_filePath = filePath;
#endif

    const char *vlc_args[] = {"-I",
                              "dummy",
                              "--volume=400",
                              "--audio-replay-gain-mode=track",
                              "--audio-filter",
                              "--language=zh_CN"
                             };

    m_vlcInst = libvlc_new(sizeof(vlc_args)/sizeof(vlc_args[0]),vlc_args);

    //字符类型转换
    QByteArray ba = m_filePath.toLatin1();
    const char *path = ba.constData();
    //通过文件路径创建一个VLC实例
    m_vlcMedia = libvlc_media_new_path(m_vlcInst,path);
    if ( m_vlcInst != 0 && m_vlcMedia != 0)
    {
        //创建一个媒体播放
        m_vlcPlayer = libvlc_media_player_new_from_media(m_vlcMedia);
        libvlc_release(m_vlcInst);
        libvlc_media_release(m_vlcMedia);
    }else
    {
        qDebug()<<"打开的文件位置不合适，请重新检查!";
        return;
    }
}

bool QtVlc::isLive()
{
    bool islive = false;
    if (m_vlcPlayer == 0)
    {
        islive = false;
    }else
    {
        islive = libvlc_media_player_is_playing(m_vlcPlayer);
    }
    return islive;
}

//播放当前媒体
bool QtVlc::setPlay()
{
    if (m_vlcPlayer != 0)
    {
        if (isLive())
        {
            setStop();
        }else
        {
            libvlc_media_player_play(m_vlcPlayer);
        }
        m_isPlaying = true;
        return true;
    }
    return false;
}

//暂停
bool QtVlc::setPause()
{
    if (m_vlcPlayer != 0)
    {
        libvlc_media_player_pause(m_vlcPlayer);
        return true;
    }
    return false;
}

//停止媒体流
bool QtVlc::setStop()
{
    if (m_vlcPlayer != 0)
    {
        libvlc_media_player_stop(m_vlcPlayer);      //停止播放
        libvlc_media_player_release(m_vlcPlayer);   //释放播放对象
        m_vlcPlayer = NULL;
        return true;
    }
    return false;
}

//关闭播放流
void QtVlc::setClose()
{
    if (m_vlcPlayer != 0)
    {
        libvlc_media_player_release(m_vlcPlayer);
        m_vlcPlayer = 0;
        qDebug()<<"关闭媒体流成功!"<<m_filePath;
    }else
    {
        qDebug()<<"关闭媒体流失败!"<<m_filePath;
    }
}


//获取播放状态
bool QtVlc::getPlayingStatue()
{
    return m_isPlaying;
}

//返回媒体长度:单位毫秒
qint64 QtVlc::getMediaLength()
{
    qint64 length;
    if (m_vlcMedia != 0)
    {
        length =  libvlc_media_player_get_length(m_vlcPlayer);
    }
    return length;
}

void QtVlc::setMediaTime(double seekTime)
{
    libvlc_media_player_set_time(m_vlcPlayer,qint64(seekTime *1000));
}

qint64 QtVlc::getMediaTime()
{
    qint64 time;
    if (m_vlcMedia != 0)
    {
        libvlc_media_parse(m_vlcMedia);
        time = libvlc_media_player_get_time(m_vlcPlayer)/1000.0;
    }
    return time;
}

//获取当前媒体音量
int QtVlc::getVolume()
{
    int volume = 0;
    if (m_vlcMedia != 0)
    {
        volume = libvlc_audio_get_volume(m_vlcPlayer);
    }
    return volume;
}

//设置音量
void QtVlc::setVolume(int newVolume)
{
    if (m_vlcPlayer != 0)
    {
        libvlc_audio_set_volume(m_vlcPlayer,newVolume);
    }
}

//获取当前媒体播放位置
int QtVlc::getPosition()
{
    int postion = 0;
    if (m_vlcPlayer != 0)
    {
        postion = libvlc_media_player_get_position(m_vlcPlayer);
        //postion = libvlc_media_player_get_time(m_vlcPlayer);
    }
    return postion;
}

//设置播放位置
void QtVlc::setPosition(int newPosition)
{
    // It's possible that the vlc doesn't play anything
    // so check before
    libvlc_media_t *curMedia = libvlc_media_player_get_media (m_vlcPlayer);
    if (curMedia == NULL)
        return;

    double pos = (float)(newPosition)/(double)POSITION_RESOLUTION;
    libvlc_media_player_set_position (m_vlcPlayer, pos);
}

qint64 QtVlc::getDuration()
{
    return libvlc_media_get_duration(m_vlcMedia);
}

//清理内存
void QtVlc::Release()
{
    this->setStop();

    if (m_vlcInst)
    {
        libvlc_release(m_vlcInst);
        m_vlcInst = NULL;
    }
}

