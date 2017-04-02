#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>
#include "controlvalues.h"

class MusicLyrcWidget;
class QHBoxLayout;
class MusicSongsSummarizied;

class Contentwidget : public QWidget
{
    Q_OBJECT
public:
    explicit Contentwidget(QWidget *parent = 0);
    ~Contentwidget();
private:
    void initForm();
    void initWidget();
    void initLayout();
    void initConnect();
    
Q_SIGNALS:
    //发送要播放的音乐(包括音乐具体信息)
    void signalPlayMusic(QString music);

    //向上发送播放上一首、下一首请求，歌曲列表收到该信号后会向下返回要播放的歌曲信息
    void signalSendPlayNext();
    void signalSendPlayPreviouse();

    //向下发送请求回来的歌曲信息
    void signalSendPlayNextMusic(const QString&);
    void signalSendPlayPreviouseMusic(const QString &);

    /*************向上请求第一次要播放的歌曲信息***************/
    void signalRequestFirstPlayMusic();
    //请求成功，向下层发送
    void signalSendFirstPlayMusic(const QString &);

    //获取当前播放的音乐--解析歌词
    void signalRequestPlayingMusic(const QString &);
    void signalRequestCurPlayTime(qint64);

    //根据播放模式，请求歌曲
    void signalRequestPlayCmd(int);
    void signalSendPlayCmdMusic(const QString &);
    
public slots:
    //接收bottombar发送过来的播放命令
    void slotReceiveFirstPlayMusic(int);
protected:
    virtual void paintEvent(QPaintEvent *);

private:
    MusicSongsSummarizied *m_songsSummarizied;
    MusicLyrcWidget *m_musicLyrcWidget;

    QHBoxLayout *m_mainLayout;
    
};

#endif // CONTENTWIDGET_H
