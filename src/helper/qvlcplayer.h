#ifndef QVLCPLAYER_H
#define QVLCPLAYER_H

#include <QObject>

typedef void (* pfnPosChanged) (void *data, int iPos);  // 文件位置变化

struct libvlc_instance_t;
struct libvlc_media_player_t;
struct libvlc_event_t;

class QVlcPlayer : public QObject
{
    Q_OBJECT
public:
    explicit QVlcPlayer(QObject *parent = 0);
    ~QVlcPlayer();

    bool Play(QString strPath);             // 播放路径为strPath的文件
    void Play ();                           // 播放
    void Pause();                           // 暂停
    void Stop ();                           // 停止

//    void PlayPreviouse();                 //播放上一首
//    void PlayNext();                      //播放下一首

    void Volume(int nVol);                  // 音量设置为nVol
    void VolumeIncrease();                  // 音量增大
    void VolumeReduce();                    // 音量减小

    void SeekTo(int nPos);                  // 跳到指定位置nPos
    void SeekForward();                     // 快进
    void SeekBackward();                    // 快退

    void SetCallback(pfnPosChanged pfn);    // 设置文件位置改变时的回调函数
    pfnPosChanged GetCallback();            // 获取文件位置改变时的回调函数

    bool    IsOpen();                       // 文件是否打开
    bool    IsPlaying();                    // 文件是否正在播放
    bool    IsPause();                      // 是否暂停
    int     GetPos();                       // 获取文件当前播放的位置
    qint64 GetTime();                       // 获取时间
    void SetPlayTime(qint64);               // 设置播放时间
    qint64 GetLength();                     // 获取长度

    int GetPlayStatue();
private:
    libvlc_instance_t     *m_pVLC_Inst;     // VLC实例
    libvlc_media_player_t *m_pVLC_Player;   // VLC播放器
    pfnPosChanged          m_pfn;           // 文件位置改变时的回调函数

    QString m_filePath;                     //文件路径

    void Init();                            // 初始化
    //编码转化
    QString UnicodeToUTF8(const QString &strWide);
    void Release();                         // 清理内存

};

#endif // QVLCPLAYER_H
