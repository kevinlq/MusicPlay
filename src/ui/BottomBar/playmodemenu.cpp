#include "playmodemenu.h"
#include <QAction>
#include <QDebug>
#include "app.h"
#include "controlvalues.h"

PlayModeMenu::PlayModeMenu(QWidget *parent)
    :QMenu(parent)
{
    initForm();
    initAction();
    initConnect();
}

PlayModeMenu::~PlayModeMenu()
{

}

void PlayModeMenu::initForm()
{
}

void PlayModeMenu::initAction()
{
    m_pOrderPlay = new QAction(QIcon(":/image/playControl/order_play_pressed.png"),
                               "顺序播放",this);
    m_pListCircual = new QAction(QIcon(":/image/playControl/list_cirtual.png"),
                                 "列表循环",this);
    m_pSingleCircual = new QAction(QIcon(":/image/playControl/single_play.png"),
                                   "单曲循环",this);
    m_pSnglePlay = new QAction(QIcon(":/image/playControl/signal.png"),
                               "单曲播放",this);
    m_pRadomPlay = new QAction(QIcon(":/image/playControl/radom_pressed.png"),"随机播放",this);

    this->addAction(m_pOrderPlay);
    this->addAction(m_pListCircual);
    this->addAction(m_pSingleCircual);
    this->addAction(m_pSnglePlay);
    this->addAction(m_pRadomPlay);

    m_pOrderPlay->setCheckable(true);


}

void PlayModeMenu::initConnect()
{
    connect(m_pOrderPlay,SIGNAL(triggered(bool)),
            this,SLOT(slotOrderPlay(bool)));
    connect(m_pListCircual,SIGNAL(triggered(bool)),
            this,SLOT(slotListCirtual(bool)));
    connect(m_pSingleCircual,SIGNAL(triggered(bool)),
            this,SLOT(slotSingleCirtual(bool)));
    connect(m_pSnglePlay,SIGNAL(triggered(bool)),
            this,SLOT(slotSinglePlay(bool)));
    connect(m_pRadomPlay,SIGNAL(triggered(bool)),
            this,SLOT(slotRadomPlay(bool)));
}

void PlayModeMenu::slotOrderPlay(bool)
{
    emit signalSendPlayMode(ORDER_PLAY);
    App::AppPlayMode = ORDER_PLAY;
    App::WriteConfig();
}

void PlayModeMenu::slotListCirtual(bool)
{
    emit signalSendPlayMode(LIST_CIRCUAL);
    App::AppPlayMode = LIST_CIRCUAL;
    App::WriteConfig();
}

void PlayModeMenu::slotSingleCirtual(bool)
{
    emit signalSendPlayMode(SINGLE_CIRCUAL);
    App::AppPlayMode = SINGLE_CIRCUAL;
    App::WriteConfig();
}

void PlayModeMenu::slotSinglePlay(bool)
{
    emit signalSendPlayMode(SINGLE_PLAY);
    App::AppPlayMode = SINGLE_PLAY;
    App::WriteConfig();
}

void PlayModeMenu::slotRadomPlay(bool)
{
    emit signalSendPlayMode(RADOM_PLAY);
    App::AppPlayMode = RADOM_PLAY;
    App::WriteConfig();
}

