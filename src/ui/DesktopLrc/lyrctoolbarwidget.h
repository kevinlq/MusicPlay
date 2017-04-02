/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2016-03-19
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:基于Qt的音乐播放器--桌面歌词工具栏设置
Function:
**************************************************/
#ifndef LYRCTOOLBARWIDGET_H
#define LYRCTOOLBARWIDGET_H

#include <QWidget>

class LyrcPushButton;
class QHBoxLayout;

class LyrcToolBarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LyrcToolBarWidget(QWidget *parent = 0);
    ~LyrcToolBarWidget();
Q_SIGNALS:
    void signalLock();
    void signalClose();
private Q_SLOTS:
private:
    void initForm();
    void initWidget();
    void initLayout();
    void initConnect();

private:
    LyrcPushButton *m_pbnMainMusic;
    LyrcPushButton *m_pbnPreviousMusic;
    LyrcPushButton *m_pbnNextMusic;
    LyrcPushButton *m_pbnPlayMusic;
    LyrcPushButton *m_pbnSetting;
    LyrcPushButton *m_pbnLock;
    LyrcPushButton *m_pbnClose;

    QHBoxLayout *m_mainLayout;
};

#endif // LYRCTOOLBARWIDGET_H
