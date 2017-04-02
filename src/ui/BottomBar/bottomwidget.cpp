/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2016-03-11
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:基于Qt的音乐播放器----底部工具栏的实现
Function:包括播放、停止、上一首、下一首、声音控制，播放进度条、
         歌词显示按钮、播放模式选择
**************************************************/
#include "bottomwidget.h"
#include <QPushButton>
#include <QSlider>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QTime>
#include "app.h"
#include "playmodemenu.h"

BottomWidget::BottomWidget(QWidget *parent) :
    QWidget(parent)
{
    initForm();
    initWidget();
    initLayout();
    initConnect();
}

BottomWidget::~BottomWidget()
{
}

//接收到的媒体总时间:用于设置播放进度条范围
void BottomWidget::slotReceivePlayLength(qint64 length)
{
    m_totalTime = length;

    //这3个参数分别代表了时，分，秒；60000毫秒为1分钟，所以分钟第二个参数是先除6000,第3个参数是直接除1
    QTime total_time(0,(length/60000)%60,(length / 1000)%60);

    //将媒体长度进行转换
#if QDEBUG_OUT
    //    qDebug()<<"转换后为："<< total_time<<"分钟";
#endif
    //取出整数和小数分开进行显示
    m_labelTotalTime->setText(total_time.toString("mm:ss"));
    m_progressSlider->setRange(0,length);
}

void BottomWidget::slotSetPlayVolume(int value)
{
    int volume = value;
    qDebug()<<"当前播放音量:"<<volume;
    //对声音范围进行设置
    if (volume >= 100)
        volume = 100;
    else if (volume < 0)
        volume = 0;
    m_voiceSlider->setValue(value);
}

//接收playmusic发送过来的媒体播放位置值
void BottomWidget::slotReceivePlayPostion(qint64 postion)
{
    qint64 temp = postion;
    QTime current_time(0,(temp/60000)%60,(temp/1000)%60);
#if QDEBUG_OUT
    //    qDebug()<<"当前播放时间:"<<current_time;
#endif
    //取出整数部分和小数部分进行显示
    m_labelCurTime->setText(current_time.toString("mm:ss"));
    m_progressSlider->setValue(temp);
}

//切换声音控制状态槽函数
void BottomWidget::slotNoVoice()
{
    if (!m_isNoVoice)
    {
        m_pbnNoVoice->setIcon(QIcon(":/image/playControl/no_voice.png"));
        m_voiceSlider->setValue(0);
        m_pbnNoVoice->setToolTip("恢复音量");
        m_isNoVoice = true;
    }else
    {
        m_pbnNoVoice->setIcon(QIcon(":/image/playControl/volume_1.png"));
        m_voiceSlider->setValue(m_curMusicVoice);
        qDebug()<<"m_curMusicVoice:"<<m_curMusicVoice;
        m_pbnNoVoice->setToolTip("静音");
        m_isNoVoice = false;
    }
    //m_isNoVoice = !m_isNoVoice;
}

void BottomWidget::slotShowOrHideLyrc()
{
    if (!m_isShowLyrc)
    {
        m_pbnDesktopLyrc->setToolTip("关闭歌词");

        emit signalHidOrShowLyrc(SHOW_LYRC);
    }else
    {
        m_pbnDesktopLyrc->setToolTip("打开歌词");
        emit signalHidOrShowLyrc(HIDE_LYRC);
    }
    m_isShowLyrc = !m_isShowLyrc;
}


//当声音滑块值变化时，进入该槽函数
void BottomWidget::slotVoiceValue(int value)
{
    if (value != 0)
    {
        m_curMusicVoice = value;
        m_isNoVoice = false;
        m_pbnNoVoice->setIcon(QIcon(":/image/playControl/volume_1.png"));
    }

    emit signalSendPlayVolume(value);
}

//当播放进度条 被拖动改变时，发送相应的值，改变音乐播放进度
void BottomWidget::slotPlayPostionChange(int value)
{
    Q_UNUSED(value);
    qint64 time = m_progressSlider->value();
    emit signalSendPlayPostion(time);
}

void BottomWidget::slotChangePlayModeIcon(int mode)
{
    int temp = mode;
    switch (temp)
    {
    case ORDER_PLAY:
    {
        m_pbnPlayMode->setIcon(QIcon(":/image/playControl/order_play_pressed.png"));
        m_pbnPlayMode->setToolTip("顺序播放");
        break;
    }
    case LIST_CIRCUAL:
    {
        m_pbnPlayMode->setIcon(QIcon(":/image/playControl/list_cirtual.png"));
        m_pbnPlayMode->setToolTip("列表循环");
        break;
    }
    case SINGLE_CIRCUAL:
    {
        m_pbnPlayMode->setIcon(QIcon(":/image/playControl/single_play.png"));
        m_pbnPlayMode->setToolTip("单曲循环");
        break;
    }
    case SINGLE_PLAY:
    {
        m_pbnPlayMode->setIcon(QIcon(":/image/playControl/signal.png"));
        m_pbnPlayMode->setToolTip("单曲播放");
        break;
    }
    case RADOM_PLAY:
    {
        m_pbnPlayMode->setIcon(QIcon(":/image/playControl/radom_pressed.png"));
        m_pbnPlayMode->setToolTip("随机播放");
        break;
    }
    default:
        break;

    }
}

void BottomWidget::initForm()
{
    //设定底部控制栏为固定宽度
    setFixedHeight(BOTTOM_HEIGHT);

    m_isPlay = false;           //默认没有播放
    m_isNoVoice = false;
    m_isShowLyrc = false;
    m_curMusicVoice = VOICE_DEFAULT_VALUE;
    m_curPlayMode = DEFAULT_PLAY_MODE;

    m_totalTime = 0;
}

void BottomWidget::initWidget()
{
    //上一首
    m_pbnPreviousMusic = new QPushButton(this);
    m_pbnPreviousMusic->setFlat(true);
    m_pbnPreviousMusic->setCursor(Qt::PointingHandCursor);
    m_pbnPreviousMusic->setToolTip("上一首");
    m_pbnPreviousMusic->setObjectName("pbnPreviousMusic");
    m_pbnPreviousMusic->setIcon(QIcon(":/image/playControl/prev.png"));
    m_pbnPreviousMusic->setIconSize(QSize(35,35));
    //暂停/播放
    m_pbnPlayOrPause = new QPushButton(this);
    m_pbnPlayOrPause->setFlat(true);
    m_pbnPlayOrPause->setCursor(Qt::PointingHandCursor);
    m_pbnPlayOrPause->setToolTip("播放");
    m_pbnPlayOrPause->setObjectName("pbnPlayOrPause");
    m_pbnPlayOrPause->setIcon(QIcon(":/image/playControl/play.png"));
    m_pbnPlayOrPause->setIconSize(QSize(35,35));
    //下一首
    m_pbnNextMusic = new QPushButton(this);
    m_pbnNextMusic->setFlat(true);
    m_pbnNextMusic->setCursor(Qt::PointingHandCursor);
    m_pbnNextMusic->setToolTip("下一首");
    m_pbnNextMusic->setObjectName("pbnNextMusic");
    m_pbnNextMusic->setIcon(QIcon(":/image/playControl/next.png"));
    m_pbnNextMusic->setIconSize(QSize(35,35));
    //播放进度条
    m_progressSlider = new QSlider(Qt::Horizontal,this);
    m_progressSlider->setValue(0);
    //静音按钮
    m_pbnNoVoice = new QPushButton(this);
    m_pbnNoVoice->setFlat(true);
    m_pbnNoVoice->setMaximumSize(21,17);
    m_pbnNoVoice->setCursor(Qt::PointingHandCursor);
    m_pbnNoVoice->setToolTip("静音");
    m_pbnNoVoice->setObjectName("pbnNoVoice");
    m_pbnNoVoice->setIcon(QIcon(":/image/playControl/volume_1.png"));
    m_pbnNoVoice->setIconSize(QSize(21,17));
    //声音进度条
    m_voiceSlider = new QSlider(Qt::Horizontal,this);
    m_voiceSlider->setFixedWidth(80);
    m_voiceSlider->setValue(m_curMusicVoice);
    m_voiceSlider->setRange(0,100);
    //播放模式
    m_pbnPlayMode = new QPushButton(this);
    m_pbnPlayMode->setFlat(true);
    m_pbnPlayMode->setCursor(Qt::PointingHandCursor);
    m_pbnPlayMode->setToolTip("播放模式");
    m_pbnPlayMode->setIcon(QIcon(":/image/playControl/order_play_pressed.png"));
    m_pbnPlayMode->setIconSize(QSize(22,18));
    m_pbnPlayMode->setObjectName("pbnPlayMode");
    m_pbnPlayMode->setStyleSheet("QPushButton#pbnPlayMode::menu-indicator{image:None;}");
    m_pMOdeMenu = new PlayModeMenu;
    m_pbnPlayMode->setMenu(m_pMOdeMenu);


    //显示或者隐藏桌面歌词
    m_pbnDesktopLyrc = new QPushButton(this);
    m_pbnDesktopLyrc->setFlat(true);
    m_pbnDesktopLyrc->setCursor(Qt::PointingHandCursor);
    m_pbnDesktopLyrc->setToolTip("打开歌词");
    m_pbnDesktopLyrc->setIcon(QIcon(":/image/playControl/context_lrc.png"));
    m_pbnDesktopLyrc->setIconSize(QSize(35,35));
    m_pbnDesktopLyrc->setObjectName("pbnDesktopLyrc");

    //显示播放时间
    m_labelCurTime = new QLabel(this);
    m_labelCurTime->setObjectName("whiteLabel");
    m_labelCurTime->setText("00:00");
    m_labelCurTime->setFont(QFont("Times", 12, QFont::Bold));
    m_labelTotalTime = new QLabel(this);
    m_labelTotalTime->setObjectName("whiteLabel");
    m_labelTotalTime->setText("00:00");
    m_labelTotalTime->setFont(QFont("Times", 12, QFont::Bold));
}

void BottomWidget::initLayout()
{
    QHBoxLayout *playLayout = new QHBoxLayout;
    playLayout->addSpacing(20);
    playLayout->addWidget(m_pbnPreviousMusic);
    playLayout->addWidget(m_pbnPlayOrPause);
    playLayout->addWidget(m_pbnNextMusic);
    playLayout->setSpacing(10);
    playLayout->setContentsMargins(2,4,2,4);

    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->addLayout(playLayout);
    m_mainLayout->addWidget(m_labelCurTime);
    m_mainLayout->addWidget(m_progressSlider);
    m_mainLayout->addWidget(m_labelTotalTime);
    m_mainLayout->addSpacing(6);
    m_mainLayout->addWidget(m_pbnNoVoice);
    m_mainLayout->addWidget(m_voiceSlider);
    m_mainLayout->addWidget(m_pbnPlayMode);
    m_mainLayout->addWidget(m_pbnDesktopLyrc);
    m_mainLayout->addSpacing(20);
    m_mainLayout->setContentsMargins(0,0,0,0);
    setLayout(m_mainLayout);
}

void BottomWidget::initConnect()
{
    connect(m_pbnPreviousMusic,SIGNAL(clicked()),
            this,SIGNAL(signalPreviousMusic()));
    connect(m_pbnPlayOrPause,SIGNAL(clicked()),
            this,SLOT(slotPlayOrPause()));
    connect(m_pbnNextMusic,SIGNAL(clicked()),
            this,SIGNAL(signalNextMusic()));
    connect(m_progressSlider,SIGNAL(valueChanged(int)),
            this,SIGNAL(signalPlayProgressChange(int)));
    connect(m_pbnNoVoice,SIGNAL(clicked()),
            this,SLOT(slotNoVoice()));

    connect(m_pbnDesktopLyrc,SIGNAL(clicked()),
            this,SLOT(slotShowOrHideLyrc()));
    connect(m_voiceSlider,SIGNAL(valueChanged(int)),
            this,SLOT(slotVoiceValue(int)));
    connect(m_progressSlider,SIGNAL(actionTriggered(int)),
            this,SLOT(slotPlayPostionChange(int)));

    //初始化播放模式菜单传递过来的信息
    connect(m_pMOdeMenu,SIGNAL(signalSendPlayMode(int)),
            this,SLOT(slotChangePlayModeIcon(int)));
}

void BottomWidget::playMusic()
{
    App::ReadConfig();
    int mode = App::AppPlayMode;
    switch (mode)
    {
    case SINGLE_CIRCUAL:
        emit signalPlayCmd(SINGLE_CIRCUAL);
        break;
    case SINGLE_PLAY:
        emit signalPlayCmd(SINGLE_PLAY);
        break;
    case ORDER_PLAY:
        emit signalPlayCmd(ORDER_PLAY);
    case RADOM_PLAY:
        emit signalPlayCmd(RADOM_PLAY);
        break;
    default:
        break;
    }
}

//进行播放和暂停状态切换
void BottomWidget::slotPlayOrPause()
{
    //在这之前必须判断当前列表中是否有歌曲
    if (!m_isPlay)
    {
        m_isPlay = true;
        m_pbnPlayOrPause->setToolTip("暂停");
        emit signalPlayOrPause(MUSIC_PLAY);
        m_pbnPlayOrPause->setIcon(QIcon(":/image/playControl/pause.png"));
    }else
    {
        m_isPlay = false;
        m_pbnPlayOrPause->setToolTip("播放");
        emit signalPlayOrPause(MUSIC_PAUSE);
        m_pbnPlayOrPause->setIcon(QIcon(":/image/playControl/play.png"));
    }
}

//接收主界面发送过来的信息，改变按钮状态
void BottomWidget::slotSetPlayOrPause(int statue)
{
    if (MUSIC_PLAY == statue)
    {
        m_isPlay = true;
        m_pbnPlayOrPause->setToolTip("暂停");
        m_pbnPlayOrPause->setIcon(QIcon(":/image/playControl/pause.png"));
    }else if (MUSIC_PAUSE == statue)
    {
        m_isPlay = false;
        m_pbnPlayOrPause->setToolTip("播放");
        m_pbnPlayOrPause->setIcon(QIcon(":/image/playControl/play.png"));
    }else if (MUSIC_PLAY_END == statue)
    {
        m_isPlay = false;
        m_pbnPlayOrPause->setToolTip("播放");
        m_pbnPlayOrPause->setIcon(QIcon(":/image/playControl/play.png"));
        m_labelCurTime->setText("00:00");
        m_labelTotalTime->setText("00:00");

        /*当前歌曲播放完毕后，根据播放模式，进行播放
         * 列表循环:
         * 单曲循环
         * 单曲播放
        */
        playMusic();
        //emit signalNextMusic();
    }
}
