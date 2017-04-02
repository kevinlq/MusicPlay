#include "musicsongslistwidget.h"
#include <QHeaderView>
#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>
#include <QDebug>

MusicSongsListWidget::MusicSongsListWidget(QWidget *parent) :
    MusicAbstractTableWidget(parent)
{
    initForm();
    initAction();
    initConnect();
}

MusicSongsListWidget::~MusicSongsListWidget()
{
}

void MusicSongsListWidget::initForm()
{
    setStyleSheet("QTableWidget{selection-background-color: rgba(20,20,20,100);}");

    qDebug()<<rowCount();
    if (rowCount() == 0)
    {
        setItem(0,0,new QTableWidgetItem("歌曲"));
    }
}

//右键菜单初始化
void MusicSongsListWidget::initAction()
{
    m_menu = new QMenu(this);

    m_actionPlayMusic = new QAction("播放音乐",m_menu);

    m_actionAddMusic = new QAction("添加歌曲",m_menu);

    m_actionAddMusicFolder = new QAction("添加歌曲文件夹",m_menu);

    m_actionDeleteMusic = new QAction(QIcon(":/image/contextMenu/context_delete.png"),
                                      "删除音乐",m_menu);

    m_actionDeleteAll = new QAction("删除所有音乐",m_menu);

    m_menu->addAction(m_actionPlayMusic);
    m_menu->addSeparator();
    m_menu->addAction(m_actionAddMusic);
    m_menu->addAction(m_actionAddMusicFolder);
    m_menu->addSeparator();
    m_menu->addAction(m_actionDeleteMusic);
    m_menu->addAction(m_actionDeleteAll);
}

//信号和槽初始化
void MusicSongsListWidget::initConnect()
{
    connect(m_actionPlayMusic,SIGNAL(triggered(bool)),
            this,SIGNAL(signalPlayMusic()));
    connect(m_actionAddMusic,SIGNAL(triggered(bool)),
            this,SIGNAL(signalAddMusic()));
    connect(m_actionAddMusicFolder,SIGNAL(triggered(bool)),
            this,SIGNAL(signalAddMusicFolder()));
    connect(m_actionDeleteMusic,SIGNAL(triggered(bool)),
            this,SIGNAL(signalDeleteMusic()));
    connect(m_actionDeleteAll,SIGNAL(triggered(bool)),
            this,SIGNAL(signalDeleteAllMusic()));
}

void MusicSongsListWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QTableWidget::contextMenuEvent(event);
    m_menu->exec(QCursor::pos());
    event->accept();
}

void MusicSongsListWidget::listCellEntered(int row, int column)
{

}

void MusicSongsListWidget::listCellClicked(int row, int column)
{

}



