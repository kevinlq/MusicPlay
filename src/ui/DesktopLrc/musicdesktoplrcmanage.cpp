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
#include "musicdesktoplrcmanage.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include "lyrctoolbarwidget.h"      //工具栏
#include <QLinearGradient>
#include <QTimer>
#include <QPainter>

MusicDesktopLrcManage::MusicDesktopLrcManage(QWidget *parent)
    :QWidget(parent)
{
    initForm();
    initWidget();
    initConnect();
}

MusicDesktopLrcManage::~MusicDesktopLrcManage()
{
    delete m_toolBarWidget;
    delete m_labelLrc;
}

void MusicDesktopLrcManage::initForm()
{
    //设置窗体标题栏隐藏--Qt::WindowStaysOnTopHint |
    this->setWindowFlags(Qt::FramelessWindowHint |
                         Qt::WindowSystemMenuHint |
                         Qt::WindowMinMaxButtonsHint |
                         Qt::WindowStaysOnTopHint);    //设置窗口在最前端
    //设置背景透明
    this->setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);
    setFixedSize(700,200);
    setGeometry(350,460,this->width(),this->height());
    this->setObjectName("desktopWiget");
}

void MusicDesktopLrcManage::initWidget()
{
    m_toolBarWidget = new LyrcToolBarWidget(this);

    m_labelLrc = new QLabel(this);
    m_labelLrc->setAlignment(Qt::AlignHCenter |Qt::AlignVCenter);
    m_labelLrc->setText("欢迎使用音乐播放器");
    m_labelLrc->setFont(QFont("Times New Roman", 30, QFont::Bold));
    m_labelLrc->setStyleSheet("color:#9AD66A");

    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->addWidget(m_toolBarWidget);
    m_mainLayout->addWidget(m_labelLrc);
    m_mainLayout->setContentsMargins(0,0,0,0);

    //m_toolBarWidget->hide();
}

void MusicDesktopLrcManage::initConnect()
{
    connect(m_toolBarWidget,SIGNAL(signalClose()),
            this,SLOT(slotClose()));
    connect(m_toolBarWidget,SIGNAL(signalLock()),
            this,SLOT(slotLock()));
}

void MusicDesktopLrcManage::slotLock()
{
    m_toolBarWidget->hide();
}

void MusicDesktopLrcManage::paintEvent(QPaintEvent *)
{
    /*
    QPainter painter(this);
    // painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    //使用该行代码可以实现反锯齿，使歌词显示更漂亮，但是会明显增加CPU占用率
    QFont font(tr("Times New Roman"),30,QFont::Bold);
    painter.setFont(font);
    QLinearGradient lg(0,20,0,50);
    lg.setColorAt(0,QColor(0,170,255,255));
    lg.setColorAt(0.2,QColor(61,214,191,250));
    lg.setColorAt(0.5,QColor(85,255,255,255));
    lg.setColorAt(0.8,QColor(61,214,191,250));
    lg.setColorAt(1,QColor(0,170,255,255));
    painter.setBrush(lg);
    painter.setPen(Qt::NoPen);
    QPainterPath textPath;
    textPath.addText(0,50,font,m_labelLrc->text());
    painter.drawPath(textPath);

    length = textPath.currentPosition().x();

    painter.setPen(Qt::yellow);
    painter.drawText(0,14,lrcWidth,50,Qt::AlignLeft,m_labelLrc->text());
    */
}

void MusicDesktopLrcManage::slotClose()
{
    this->hide();
}

void MusicDesktopLrcManage::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_offset = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    QWidget::mousePressEvent(event);
}

void MusicDesktopLrcManage::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        setCursor(Qt::PointingHandCursor);
        move(event->globalPos() - m_offset);
        event->accept();
    }
    QWidget::mousePressEvent(event);
}

void MusicDesktopLrcManage::enterEvent(QEvent *event)
{
    if (m_widgetLock){
        return;
    }

    QWidget::enterEvent(event);
    setStyleSheet("QWidget#desktopWiget{border: 1px solid #555555;"
                  "background-color:rgba(0,0,0,40)}");

}

void MusicDesktopLrcManage::leaveEvent(QEvent *event)
{
    if (m_widgetLock){
        return;
    }
    QWidget::leaveEvent(event);
    m_toolBarWidget->hide();
    setStyleSheet("QWidget#desktopWiget{background-color:transparent;}");
}

void MusicDesktopLrcManage::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);
}

