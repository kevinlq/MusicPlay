#ifndef QTVLC_H
#define QTVLC_H

#include <QObject>

#include "vlc/vlc.h"        //VLC相关模块接口头文件


#define POSITION_RESOLUTION 1000
typedef void (* pfnPosChanged) (void *data, int iPos);  // 文件位置变化

class QtVlc : public QObject
{
    Q_OBJECT
public:
    explicit QtVlc(QObject *parent = 0);
    ~QtVlc();

    void setOpen(QString filePath);         //打开所要播放的媒体
    bool isLive();                          //是否存在
    bool setPlay();                         //播放媒体
    bool setPause();                        //暂停播放
    bool setStop();                         //停止
    void setClose();                        //关闭
    bool getPlayingStatue();                //获取播放状态

    qint64 getMediaLength();               //获取媒体长度
    void setMediaTime(double seekTime);     //设置媒体时间
    qint64 getMediaTime();                 //获取媒体时间

    int getVolume();                        //获取音量
    void setVolume(int newVolume);          //设置音量
    int getPosition();                      //获取当前媒体播放位置
    void setPosition(int newPosition);      //设置播放位置

    qint64 getDuration();                  //获取媒体文件播放长度

private:
    void init();
    void Release();                         //清理内存

private:
    libvlc_instance_t *m_vlcInst;           //VLC播放实例
    libvlc_media_player_t*m_vlcPlayer;      //VLC播放器
    libvlc_media_t *m_vlcMedia;             //VLC媒体实例

    QString m_filePath;
    pfnPosChanged m_pfn;                    //文件位置改变时的回调函数
    bool m_isPlaying;                       //是否正在播放

};

#endif // QTVLC_H
