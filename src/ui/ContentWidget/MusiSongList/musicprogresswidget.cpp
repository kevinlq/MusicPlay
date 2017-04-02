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
#include "musicprogresswidget.h"
#include <QPainter>
#include <QLabel>
#include <QToolButton>
#include <QProgressBar>
#include "controlvalues.h"

MusicProgressWidget::MusicProgressWidget(QWidget *parent) :
    QProgressDialog(parent)
{
    setModal(true);
    setWindowFlags( Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setWindowModality(Qt::ApplicationModal);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setCancelButton(NULL);
    setLabel(NULL);
    setFixedSize(400, 155);

    initWidget();
}

MusicProgressWidget::~MusicProgressWidget()
{
    delete m_background;
    delete m_textLabel;
    delete m_progressBar;
}

void MusicProgressWidget::setTitle(const QString &name)
{
    m_textLabel->setText(name);
}

void MusicProgressWidget::slotShow()
{
    QPixmap pix(DEFAULT_SKIN);
    m_background->setPixmap(pix.scaled( size() ));
    QProgressDialog::show();
}

void MusicProgressWidget::paintEvent(QPaintEvent *event)
{
}


void MusicProgressWidget::initWidget()
{
    m_background = new QLabel(this);
    m_background->setGeometry(20, 20, 360, 115);
    QWidget *backgroundMask = new QWidget(this);
    backgroundMask->setGeometry(20, 45, 360, 90);
    backgroundMask->setStyleSheet("background:rgba(255,255,255,200);");

    QLabel *topTitleName = new QLabel(this);
    topTitleName->setText(tr("Progress Bar"));
    topTitleName->setGeometry(30, 20, 221, 25);
    topTitleName->setStyleSheet("color:#FFFFFF;font-weight:bold;");

    QToolButton *topTitleCloseButton = new QToolButton(this);
    topTitleCloseButton->setGeometry(360, 22, 20, 20);
    topTitleCloseButton->setIcon(QIcon(":/share/searchclosed"));
    //topTitleCloseButton->setStyleSheet(MusicUIObject::MToolButtonStyle03);
    topTitleCloseButton->setEnabled(false);

    const QString MProgressBar01 = "QProgressBar{ border:none; \
            background:rgb(210, 225, 240); text-align:center;}QProgressBar::chunk{ background:rgb(60, 140, 220);}";

    m_progressBar = new QProgressBar(this);
    setBar(m_progressBar);
    m_progressBar->setStyleSheet(MProgressBar01);

    m_textLabel = new QLabel(this);
    m_textLabel->setAlignment(Qt::AlignCenter);
    m_textLabel->setGeometry(40, 50, 320, 25);
}


void MusicProgressWidget::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    m_progressBar->setGeometry(40, 85, 320, 25);
}
