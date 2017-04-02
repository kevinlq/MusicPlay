#include "songmenu.h"
#include <QAction>


SongMenu::SongMenu(QWidget *parent) :
    QMenu(parent)
{
    initForm();
    initAction();
    initConnect();
}

SongMenu::~SongMenu()
{
}

void SongMenu::initForm()
{
}

void SongMenu::initAction()
{
    m_actionAddNewList = new QAction(QIcon(":/image/contextMenu/context_add.png"),
                                     "新建列表",this);
    m_actionDeleteList = new QAction(QIcon(":/image/contextMenu/context_delete.png"),
                                     "删除列表",this);
    m_actionReName = new QAction("重命名",this);

    addAction(m_actionAddNewList);
    addSeparator();
    addAction(m_actionDeleteList);
    addAction(m_actionReName);
}

void SongMenu::initConnect()
{
    connect(m_actionAddNewList,SIGNAL(triggered()),
            this,SIGNAL(signalAddNewList()));
    connect(m_actionDeleteList,SIGNAL(triggered()),
            this,SIGNAL(signalDeleteList()));
    connect(m_actionReName,SIGNAL(triggered()),
            this,SIGNAL(signalRename()));
}
