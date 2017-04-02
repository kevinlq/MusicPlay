#include "lyrctoolbarwidget.h"
#include "lyrcpushbutton.h"
#include <QHBoxLayout>

LyrcToolBarWidget::LyrcToolBarWidget(QWidget *parent) : QWidget(parent)
{
    initForm();
    initWidget();
    initLayout();
    initConnect();
}

LyrcToolBarWidget::~LyrcToolBarWidget()
{
    delete m_pbnMainMusic;
    delete m_pbnPreviousMusic;
    delete m_pbnPlayMusic;
    delete m_pbnNextMusic;
    delete m_pbnSetting;
    delete m_pbnLock;
    delete m_pbnClose;
}

void LyrcToolBarWidget::initForm()
{
    //背景透明
    this->setAttribute(Qt::WA_TranslucentBackground);
}

void LyrcToolBarWidget::initWidget()
{
    m_pbnMainMusic = new LyrcPushButton(this);
    m_pbnPreviousMusic = new LyrcPushButton(this);
    m_pbnPlayMusic = new LyrcPushButton(this);
    m_pbnNextMusic =new LyrcPushButton(this);
    m_pbnSetting = new LyrcPushButton(this);
    m_pbnLock = new LyrcPushButton(this);
    m_pbnClose = new LyrcPushButton(this);

    m_pbnLock->setIcon(QIcon(QPixmap(":/image/desktopTool/ds_lockWindow.png").scaled(30,30)));
}

void LyrcToolBarWidget::initLayout()
{
    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->addStretch();
    m_mainLayout->addWidget(m_pbnMainMusic);
    m_mainLayout->addWidget(m_pbnPreviousMusic);
    m_mainLayout->addWidget(m_pbnPlayMusic);
    m_mainLayout->addWidget(m_pbnNextMusic);
    m_mainLayout->addWidget(m_pbnSetting);
    m_mainLayout->addWidget(m_pbnLock);
    m_mainLayout->addWidget(m_pbnClose);
    m_mainLayout->addStretch();
    m_mainLayout->setContentsMargins(0,0,0,0);

}

void LyrcToolBarWidget::initConnect()
{
    connect(m_pbnClose,SIGNAL(clicked(bool)),
            this,SIGNAL(signalClose()));
    connect(m_pbnLock,SIGNAL(clicked(bool)),
            this,SIGNAL(signalLock()));
}

