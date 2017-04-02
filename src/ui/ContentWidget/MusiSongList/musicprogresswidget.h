/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2016-03-12
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:基于Qt的音乐播放器----添加歌曲进度条界面
Function:
**************************************************/
#ifndef MUSICPROGRESSWIDGET_H
#define MUSICPROGRESSWIDGET_H

#include <QProgressDialog>

class MusicProgressWidget : public QProgressDialog
{
    Q_OBJECT
public:
    explicit MusicProgressWidget(QWidget *parent = 0);
    
    ~MusicProgressWidget();

    void setTitle(const QString &name);

public Q_SLOTS:
    void slotShow();

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    void initWidget();

    QLabel *m_background, *m_textLabel;
    QProgressBar *m_progressBar;
    
};

#endif // MUSICPROGRESSWIDGET_H
