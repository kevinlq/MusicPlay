/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2016-03-12
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:基于Qt的音乐播放器---歌词界面的实现
Function:
**************************************************/
#ifndef MUSICLYRCWIDGET_H
#define MUSICLYRCWIDGET_H

#include <QFrame>
class QLabel;
class QTextStream;
class QTextEdit;

class MusicLyrcWidget : public QFrame
{
    Q_OBJECT
public:
    explicit MusicLyrcWidget(QWidget *parent);
    ~MusicLyrcWidget();
protected:
    virtual void mouseMoveEvent(QMouseEvent *);
private:
    void initForm();
    void analysisLyrc(const QString &name);         //解析歌词

public Q_SLOTS:
    void slotReceiveMusicInfo(const QString &name); //接收歌曲信息，准备解析歌词
    void slotReceiveCurrentPlayTime(qint64);        //接收当前播放的时间
private:
    QLabel *m_labelLyrc;
    QTextEdit *m_lrcText;
};

#endif // MUSICLYRCWIDGET_H
