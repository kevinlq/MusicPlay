/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2016-03-11
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:自定义搜索框的实现
**************************************************/
#include "searchlineedit.h"

#include <QLineEdit>
#include <QToolButton>
#include <QHBoxLayout>
#include <QDebug>
#include <QFocusEvent>
#include <QApplication>
#include <QClipboard>
#include "controlvalues.h"

SearchLineEdit::SearchLineEdit(QWidget *parent)
    :QLineEdit(parent)
{
    this->initForm();
    this->initConnect();
    this->translator();
}

SearchLineEdit::~SearchLineEdit()
{
}

void SearchLineEdit::initForm()
{
    this->setFixedSize(260,24);
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    m_tbnSearch = new QToolButton(this);

    m_tbnSearch->setFixedSize(25,24);
    m_tbnSearch->setAutoRaise(true);
    m_tbnSearch->setCursor(Qt::PointingHandCursor);
    m_tbnSearch->setStyleSheet("QToolButton{border-image:url(:/image/search/search_dark.png);"
                               "background:transparent;}");

    m_mainLayout = new QHBoxLayout();
    m_mainLayout->addStretch();
    m_mainLayout->addWidget(m_tbnSearch);

    //设置文本边框，防止文本覆盖按钮
    setTextMargins(0,0,20,0);
    setContentsMargins(0,0,0,0);
    m_mainLayout->setContentsMargins(2,2,4,0);
    this->setLayout(m_mainLayout);

    setStyleSheet("height:24px;border:1px ;border-radius:6px;"
                  "background-color:#E1DDDD");
}

void SearchLineEdit::initConnect()
{
    connect(m_tbnSearch,SIGNAL(clicked(bool)),
            this,SLOT(slotSendSearchContent()));
}

//翻译控件
void SearchLineEdit::translator()
{
    setPlaceholderText("输入要查找的歌曲名称");
    setToolTip("查找歌曲");
    m_tbnSearch->setToolTip("查找");
}

void SearchLineEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);

    this->clear();
    this->setPlaceholderText("");
    setStyleSheet("height:24px;border:1px ;border-radius:6px;"
                  "background-color:#FFFFFF");
    m_tbnSearch->setStyleSheet("QToolButton{border-image:url(:/image/search/search.png);"
                               "background:transparent;}");

}

void SearchLineEdit::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);
    this->setPlaceholderText("搜索音乐");
    setStyleSheet("height:24px;border:1px ;border-radius:6px;"
                  "background-color:#E1DDDD");
    m_tbnSearch->setStyleSheet("QToolButton{border-image:url(:/image/search/search_dark.png);"
                               "background:transparent;}");
}

void SearchLineEdit::slotSendSearchContent()
{
    QString str = "";
    if (this->text().isEmpty())
        str = this->placeholderText();
    else
        str = this->text();

    qDebug()<<"\nsearch content:"<<str<<endl;
    emit signalSearchContent(str);
}


