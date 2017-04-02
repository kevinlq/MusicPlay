#include "contentwidget.h"
#include <QBitmap>
#include <QPainter>
#include "MusisLyrc/musiclyrcwidget.h"
#include <QHBoxLayout>
#include "MusiSongList/musicsongssummarizied.h"
#include <QDebug>
#include "app.h"

Contentwidget::Contentwidget(QWidget *parent) :
    QWidget(parent)
{
    initForm();
    initWidget();
    initLayout();
    initConnect();
}

Contentwidget::~Contentwidget()
{
    delete m_songsSummarizied;
    delete m_musicLyrcWidget;
}

void Contentwidget::initForm()
{
}

void Contentwidget::initWidget()
{
    m_songsSummarizied = new MusicSongsSummarizied(this);
    m_musicLyrcWidget = new MusicLyrcWidget(this);
}

void Contentwidget::initLayout()
{
    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->addWidget(m_songsSummarizied,Qt::AlignLeft);
    m_mainLayout->addWidget(m_musicLyrcWidget,Qt::AlignRight);
    m_mainLayout->setContentsMargins(0,0,0,0);
    setLayout(m_mainLayout);
}

void Contentwidget::initConnect()
{
    //关联歌曲汇总类中传递过来的信号--播放音乐信号
    connect(m_songsSummarizied,SIGNAL(signalPlayMusic(QString)),
            this,SIGNAL(signalPlayMusic(QString)));

    //关联下边请求获取播放歌曲名称信息
    connect(this,SIGNAL(signalSendPlayNext()),
            m_songsSummarizied,SIGNAL(signalRequestNextMusic()));
    connect(this,SIGNAL(signalSendPlayPreviouse()),
            m_songsSummarizied,SIGNAL(signalRequestPreviousMusic()));
    //关联上边发送过来的歌曲信息
    connect(m_songsSummarizied,SIGNAL(signalSendNextMusic(QString)),
            this,SIGNAL(signalSendPlayNextMusic(QString)));
    connect(m_songsSummarizied,SIGNAL(signalSendPreviousMusic(QString)),
            this,SIGNAL(signalSendPlayPreviouseMusic(QString)));

    /***************向歌曲汇总类请求第一次播放歌曲信息*************/
    connect(this,SIGNAL(signalRequestFirstPlayMusic()),
            m_songsSummarizied,SIGNAL(signalRequestFirstPlayMusic()));
    //向下发送歌曲信息
    connect(m_songsSummarizied,SIGNAL(signalSendFirstPlayMusic(QString)),
            this,SIGNAL(signalSendFirstPlayMusic(QString)));

    /*****************接收当前播放的音乐，解析歌词****************/
    connect(this,SIGNAL(signalRequestPlayingMusic(QString)),
            m_musicLyrcWidget,SLOT(slotReceiveMusicInfo(QString)));
    connect(this,SIGNAL(signalRequestCurPlayTime(qint64)),
            m_musicLyrcWidget,SLOT(slotReceiveCurrentPlayTime(qint64)));
    /***************根据播放模式请求要播放的歌曲**********************/
    connect(this,SIGNAL(signalRequestPlayCmd(int)),
            m_songsSummarizied,SIGNAL(signalRequestPlayCmd(int)));
    connect(m_songsSummarizied,SIGNAL(signalSendPlayCmdMusic(QString)),
            this,SIGNAL(signalSendPlayCmdMusic(QString)));
}


void Contentwidget::slotReceiveFirstPlayMusic(int cmd)
{
    //发送之前先检测当前是否正在播放音乐
    App::ReadConfig();
    if (!App::IsPlaying)
    {
        if (MUSIC_PLAY == cmd)
        {
            emit signalRequestFirstPlayMusic();
#if QDEBUG_OUT
            qDebug()<<"向MusicSongsSummarizied发送请求播放第一首歌曲命令";
#endif
        }
    }

}

//重绘事件
void Contentwidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen objPen(Qt::transparent);
    painter.setPen(objPen);
    QBrush objBrush(QColor(255,255,255,120));
    painter.setBrush(objBrush);
    painter.drawRect(this->rect());
}
