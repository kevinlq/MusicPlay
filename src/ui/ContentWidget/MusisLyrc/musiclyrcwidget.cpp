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
#include "musiclyrcwidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include "app.h"
#include "controlvalues.h"
#include <QtDebug>
#include <QFile>
#include <QTextEdit>
#include <QTime>
#include <QTextBlock>
#include <QTextCodec>

MusicLyrcWidget::MusicLyrcWidget(QWidget *parent)
    :QFrame(parent)
{
    initForm();
}

MusicLyrcWidget::~MusicLyrcWidget()
{
}

void MusicLyrcWidget::mouseMoveEvent(QMouseEvent *event)
{
    //
}

void MusicLyrcWidget::initForm()
{
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    installEventFilter(this);

    m_labelLyrc = new QLabel;
    m_labelLyrc->setObjectName("labelLyrc");
    m_labelLyrc->setText("本歌曲暂无歌词");
    m_labelLyrc->setFont(QFont(App::AppFontName, 20, QFont::Bold));
    m_labelLyrc->setCursor(Qt::PointingHandCursor);
    m_labelLyrc->setAlignment(Qt::AlignHCenter |Qt::AlignVCenter);
    //设置歌词颜色
    m_labelLyrc->setStyleSheet("color:#ED9464");

    //设置label自动换行(有些歌词太长，显示不完整)
    m_labelLyrc->adjustSize();
    m_labelLyrc->setWordWrap(true);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_labelLyrc);
    mainLayout->setContentsMargins(10,10,10,10);
    setLayout(mainLayout);

    m_lrcText = new QTextEdit;
}

void MusicLyrcWidget::analysisLyrc(const QString &name)
{
    QString fileName = name;
    QString lrcName = fileName.remove(fileName.right(3)) + "lrc";
    QFile file(lrcName);

    if (!file.open(QFile::ReadOnly | QIODevice::Text))
    {
        m_labelLyrc->setText("没有找到对应歌词!");
    }else
    {
        m_labelLyrc->setText("正在加载歌词");
        QTextStream in(&file);
        in.setCodec("UTF-8");
        m_lrcText->setText(in.readAll());
    }
}

void MusicLyrcWidget::slotReceiveMusicInfo(const QString &name)
{
#if QDEBUG_OUT
    qDebug()<<"当前歌曲名称:"<<name;
#endif
    this->analysisLyrc(name);
}

//接收当前播放的时间
void MusicLyrcWidget::slotReceiveCurrentPlayTime(qint64 time)
{
#if QDEBUG_OUT
//    qDebug()<<"当前播放时间:"<<time;
#endif
    QTime curTime (0,(time/60000) % 60,(time / 1000) %60,time %1000);
    if (m_lrcText->find(curTime.toString("mm:ss").left(7)))
    {
        QString str = m_lrcText->textCursor().block().text().replace(
                    QRegExp("\\[\\d{2}:\\d{2}\\.\\d{2}\\]"),"");

        m_labelLyrc->setText(str);
        qDebug()<<QString(str);
    }
}
