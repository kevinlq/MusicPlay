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
#ifndef BOTTOMWIDGET_H
#define BOTTOMWIDGET_H

#include "controlvalues.h"
#include <QWidget>
class QPushButton;
class QSlider;
class QHBoxLayout;
class QLabel;
class PlayModeMenu;

class BottomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BottomWidget(QWidget *parent = 0);
    ~BottomWidget();
Q_SIGNALS:
    void signalPreviousMusic();         //上一首
    void signalPlayOrPause(int);        //播放或者暂停
    void signalNextMusic();             //下一首
    void signalPlayProgressChange(int); //播放进度改变
    void signalHidOrShowLyrc(int);      //显示或者隐藏桌面歌词
    void signalSendPlayVolume(int);     //发送当前媒体音量
    void signalSendPlayPostion(qint64); //发送当前媒体播放进度

    void signalPlayCmd(int);

public Q_SLOTS:
    void slotReceivePlayLength(qint64); //接收媒体长度
    void slotSetPlayVolume(int);        //设置播放音量
    void slotReceivePlayPostion(qint64);//接收播放位置
private Q_SLOTS:
    void slotPlayOrPause();             //播放模式
    void slotSetPlayOrPause(int);       //设置播放模式
    void slotNoVoice();
    void slotShowOrHideLyrc();          //显示或者隐藏桌面歌词
//    void slotPlayMode();                //播放模式
    void slotVoiceValue(int);           //声音改变槽函数
    void slotPlayPostionChange(int);    //播放进度条改变槽函数

    //改变播放模式图标
    void slotChangePlayModeIcon(int);

private:
    void initForm();                    //样式初始化
    void initWidget();                  //界面初始化
    void initLayout();                  //布局初始化
    void initConnect();                 //信号和槽初始化

    void playMusic();

private:
    QPushButton *m_pbnPreviousMusic;    //上一首
    QPushButton *m_pbnPlayOrPause;      //播放或者暂停
    QPushButton *m_pbnNextMusic;        //下一首
    QSlider *m_progressSlider;          //播放进度条
    QPushButton *m_pbnNoVoice;          //静音按钮
    QSlider *m_voiceSlider;             //声音进度条
    QPushButton *m_pbnPlayMode;         //播放模式
    PlayModeMenu *m_pMOdeMenu;          //播放模式菜单

    QPushButton *m_pbnDesktopLyrc;      //显示桌面歌词

    QLabel *m_labelTotalTime;           //歌曲总时间
    QLabel *m_labelCurTime;             //歌曲当前播放时间

    QHBoxLayout *m_mainLayout;          //主布局

    bool m_isPlay;                      //是否播放
    bool m_isNoVoice;                   //是否静音
    bool m_isShowLyrc;                  //是否显示歌词
    volatile  quint8 m_curMusicVoice;   //当前声音大小
    PlayMode m_curPlayMode;             //当前播放模式

    volatile qint64 m_totalTime;        //当前播放媒体总时间
    volatile qint64 m_currentTime;      //当前播放时间
    
};

#endif // BOTTOMWIDGET_H
