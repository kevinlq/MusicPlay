#include "musiclistmenu.h"
#include <QAction>

MusicListMenu::MusicListMenu(QWidget *parent)
    :QMenu(parent)
{
    initAction();
    initConnect();
}

MusicListMenu::~MusicListMenu()
{
    delete m_actionPlayMusic;
    delete m_actionAddMusic;
//    delete m_actionAddMusicFolder;
    delete m_actionDeleteMusic;
    delete m_actionDeleteAll;
}

void MusicListMenu::initAction()
{

    m_actionPlayMusic = new QAction("播放音乐",this);

    m_actionAddMusic = new QAction("添加歌曲",this);

//    m_actionAddMusicFolder = new QAction("添加歌曲文件夹",this);

    m_actionDeleteMusic = new QAction(QIcon(":/image/contextMenu/context_delete.png"),
                                      "删除音乐",this);

    m_actionDeleteAll = new QAction("删除所有音乐",this);

    addAction(m_actionPlayMusic);
    addSeparator();
    addAction(m_actionAddMusic);
//    addAction(m_actionAddMusicFolder);
    addSeparator();
    addAction(m_actionDeleteMusic);
    addAction(m_actionDeleteAll);
}

void MusicListMenu::initConnect()
{
    connect(m_actionPlayMusic,SIGNAL(triggered(bool)),
            this,SIGNAL(signalPlayMusic()));
    connect(m_actionAddMusic,SIGNAL(triggered(bool)),
            this,SIGNAL(signalAddMusic()));
    /*
    connect(m_actionAddMusicFolder,SIGNAL(triggered(bool)),
            this,SIGNAL(signalAddMusicFolder()));
    */
    connect(m_actionDeleteMusic,SIGNAL(triggered(bool)),
            this,SIGNAL(signalDeleteMusic()));
    connect(m_actionDeleteAll,SIGNAL(triggered(bool)),
            this,SIGNAL(signalDeleteAllMusic()));
}

