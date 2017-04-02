/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2016-03-16
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:基于Qt的音乐播放器--桌面歌词的实现
Function:
**************************************************/
#ifndef MUSICDESKTOPLRCMANAGE_H
#define MUSICDESKTOPLRCMANAGE_H

#include <QObject>
#include <QWidget>
class QLabel;
class QVBoxLayout;
class LyrcToolBarWidget;
class QLinearGradient;

class MusicDesktopLrcManage : public QWidget
{
    Q_OBJECT
public:
    explicit MusicDesktopLrcManage(QWidget *parent = 0);
    ~MusicDesktopLrcManage();

    void startLrcMask(qint64 intervaltime);
    void stopLrcMask();
private:
    void initForm();
    void initWidget();
    void initConnect();

Q_SIGNALS:

private Q_SLOTS:
    void slotLock();
    void slotClose();
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    //    virtual void contextMenuEvent(QContextMenuEvent *event);
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void closeEvent(QCloseEvent *event);
    virtual void paintEvent(QPaintEvent *);

private:
    LyrcToolBarWidget *m_toolBarWidget;
    QLabel *m_labelLrc;
    QVBoxLayout *m_mainLayout;
    QPoint m_offset, m_geometry;

    bool m_widgetLock;

    qreal length;
    qreal lrcWidth;
};

#endif // MUSICDESKTOPLRCMANAGE_H
