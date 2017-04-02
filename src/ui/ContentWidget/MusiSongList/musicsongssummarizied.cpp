/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2016-03-12
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:基于Qt的音乐播放器---歌曲汇总实现
Function:
**************************************************/
#include "musicsongssummarizied.h"
#include "musicsongslistwidget.h"
#include "musicsongstoolitemrenamedwidget.h"
#include "musicprogresswidget.h"
#include <QLayout>
#include <QDebug>
#include <QContextMenuEvent>
#include "songmenu.h"
#include "myhelper.h"
#include <QFileDialog>
#include <QStringList>
#include "controlvalues.h"

MusicSongsSummarizied::MusicSongsSummarizied(QWidget *parent)
    :QToolBox(parent),m_renameLine(NULL)
{
    initForm();
    initWidget();
    initConnect();
}

MusicSongsSummarizied::~MusicSongsSummarizied()
{
    clearAllLists();
}

//导入歌曲：只有歌曲的名称
void MusicSongsSummarizied::importMusicSongsName(const QStringList &file_name_list)
{
    //获取当前列表索引
    int index = currentIndex();
    QFileInfo finfo;
    QStringList fileNameList;
    QStringList filePath;

    if (file_name_list.isEmpty())
    {
        return;
    }
    //提取出歌曲名称
    foreach (QString str, file_name_list) {
        finfo = QFileInfo(str);
        fileNameList <<finfo.fileName();
        filePath << finfo.filePath();
    }

    //插入多条歌曲到列表中
    for (int i = 0; i <fileNameList.count(); i++)
    {
        //将歌曲名称插入到列表中
        m_mainSongLists.at(index)->addItemContent(fileNameList.at(i));
        //保存歌曲信息，以便进行歌曲播放
        m_mainSongLists.at(index)->saveMusicInfo(fileNameList.at(i),filePath.at(i));
    }
}

void MusicSongsSummarizied::importMusicSongs(const QStringList &file_list)
{
    MusicProgressWidget progress;
    progress.show();
    progress.setTitle("导入歌曲");
    progress.setRange(0, file_list.count());

    for(int i = 0; i < file_list.count(); ++i)
    {
        //        if(tag.readFile(file_list[i]))
        //        {
        //            m_musicFileNames[0] << MusicSong(file_list[i], 0, tag.getLengthString(), QString());
        //        }
        progress.setValue(i + 1);
    }
    //    m_mainSongLists[0]->updateSongsFileName(m_musicFileNames[0]);
}

//导入歌曲：包含歌曲的路径和名称
void MusicSongsSummarizied::musicImportSongsSettingPath(const QStringList &path)
{
    //获取当前列表索引
    int index = currentIndex();
    if (path.isEmpty())
    {
        return;
    }
    //插入多条歌曲到列表中
    for (int i = 0; i <path.count(); i++)
    {
        m_mainSongLists.at(index)->addItemContent(path.at(i));
    }
}

void MusicSongsSummarizied::initForm()
{
    setAttribute(Qt::WA_TranslucentBackground,true);

    //设置toolBox按钮样式
    setStyleSheet("QToolBoxButton{min-height:40px;font-size:14px;color:white;}");

    m_currentIndexs = 0;
    //默认为新建列表1,以后每次创建列表后，会依次增加(新建列表2,新建列表3……)
    m_newPlayListNum = 0;
}

void MusicSongsSummarizied::initWidget()
{
    for (int i = 0; i < 3; i++)
    {
        MusicSongsListWidget *list = new MusicSongsListWidget(this);
        m_mainSongLists.append(list);
    }
    addItem(m_mainSongLists.at(0),QIcon(":/image/arrow-right"),"默认列表");
    addItem(m_mainSongLists.at(1),QIcon(":/image/arrow-right"),"我的喜爱");
    addItem(m_mainSongLists.at(2),QIcon(":/image/arrow-right"),"我的收藏");

    //关联歌曲列表信息界面数据邮件菜单信号
    this->initMusicActionConnect();

    layout()->setSpacing(0);
    m_menu = new SongMenu(this);
}

void MusicSongsSummarizied::initMusicActionConnect()
{
    for (int i = 0; i < m_mainSongLists.count();i++)
    {
        connect(m_mainSongLists.at(i),SIGNAL(signalPlayMusic(QString)),
                this,SLOT(slotPlayMusic(QString)));
        connect(m_mainSongLists.at(i),SIGNAL(signalPlayMusic()),
                this,SLOT(slotPlayMusic()));
        connect(m_mainSongLists.at(i),SIGNAL(signalAddMusic()),
                this,SLOT(slotAddMusic()));
        connect(m_mainSongLists.at(i),SIGNAL(signalDeleteMusic()),
                this,SLOT(slotDeleteMusic()));
        connect(m_mainSongLists.at(i),SIGNAL(signalDeleteAllMusic()),
                this,SLOT(slotDeleteAllMusic()));
        //请求上一首、下一首歌曲
        connect(this,SIGNAL(signalRequestNextMusic()),
                m_mainSongLists.at(i),SLOT(slotGetNextMusic()));
        connect(this,SIGNAL(signalRequestPreviousMusic()),
                m_mainSongLists.at(i),SLOT(slotGetPreviouseMusic()));
        //接收上层发送过来的歌曲信息
        connect(m_mainSongLists.at(i),SIGNAL(signalSendNextMusic(QString)),
                this,SIGNAL(signalSendNextMusic(QString)));
        connect(m_mainSongLists.at(i),SIGNAL(signalSendPreviousMusic(QString)),
                this,SIGNAL(signalSendPreviousMusic(QString)));
        /*****************根据播放模式请求歌曲******************/
        connect(this,SIGNAL(signalRequestPlayCmd(int)),
                m_mainSongLists.at(i),SLOT(slotSendPlayCmd(int)));
        connect(m_mainSongLists.at(i),SIGNAL(signalSendPlayCmdMusicInfo(QString)),
                this,SIGNAL(signalSendPlayCmdMusic(QString)));

    }
}


void MusicSongsSummarizied::initConnect()
{
    connect(this,SIGNAL(currentChanged(int)),
            this,SLOT(slotShowCurPlayList(int)));

    connect(m_menu,SIGNAL(signalAddNewList()),
            this,SLOT(slotAddNewPlayList()));
    connect(m_menu,SIGNAL(signalDeleteList()),
            this,SLOT(slotDeletePlayList()));
    connect(m_menu,SIGNAL(signalRename()),
            this,SLOT(slotRename()));
    //请求第一次播放时的歌曲信息
//    connect(this,SIGNAL(signalRequestFirstPlayMusic()),
//            m_mainSongLists.at(m_currentIndexs),SLOT(slotGetFirstPlayMusic()));
//    connect(m_mainSongLists.at(m_currentIndexs),SIGNAL(signalSendFirstPlayMusic(QString)),
//            this,SIGNAL(signalSendFirstPlayMusic(QString)));
    //修改为以下一个函数调用
    this->connectMusicList(m_currentIndexs);

}

/*当当前歌曲列表改变关联对应列表信号
 * 本类调用
*/

void MusicSongsSummarizied::connectMusicList(int index)
{
    connect(this,SIGNAL(signalRequestFirstPlayMusic()),
            m_mainSongLists.at(index),SLOT(slotGetFirstPlayMusic()));
    connect(m_mainSongLists.at(index),SIGNAL(signalSendFirstPlayMusic(QString)),
            this,SIGNAL(signalSendFirstPlayMusic(QString)));
}

QString MusicSongsSummarizied::getCurPlayListName() const
{
    return m_curPlayListName;
}

//改变item图标
void MusicSongsSummarizied::changeItemIcon()
{
    for (int i = 0; i < count(); i++)
    {
        setItemIcon(i,QIcon(":/image/arrow-down.png"));
    }
    setItemIcon(currentIndex(), QIcon(":/image/arrow-right.png"));
}

void MusicSongsSummarizied::clearAllLists()
{
    while (!m_mainSongLists.isEmpty()) {
        MusicSongsListWidget *w = m_mainSongLists.takeLast();
        delete w;
        w = NULL;
    }
}

//显示鼠标右键菜单
void MusicSongsSummarizied::contextMenuEvent(QContextMenuEvent *event)
{
    QToolBox::contextMenuEvent(event);
    m_menu->exec(event->globalPos());
}

void MusicSongsSummarizied::slotShowCurPlayList(int index)
{
    m_currentIndexs = index;
    if (index == -1)
    {
        return;
    }

    //当当前鼠标点击的item改变时，改变对应的item图标
    changeItemIcon();
    if(m_renameLine)
    {
        m_renameLine->slotRenameFinished();
    }

    m_curPlayListName = itemText(index);

    this->connectMusicList(m_currentIndexs);
}

void MusicSongsSummarizied::slotPlayMusic()
{
    //获取当前的音乐列表
    int index = currentIndex();

    qDebug()<<m_mainSongLists.at(index)->getSelectContent();
}

void MusicSongsSummarizied::slotPlayMusic(const QString &name)
{
    int index = currentIndex();
    QString musicPath = "";
    if (m_mainSongLists.at(index)->tableWidgetIsEmpty())
    {
        return;
    }else{
        musicPath = m_mainSongLists.at(index)->getMusicPath(name);
    }
#if QDEBUG_OUT
    qDebug()<<"要播放的歌曲为：";
    qDebug()<<"名称:"<<name;
    qDebug()<<"路径："<<musicPath;
#endif
    emit signalPlayMusic(musicPath);
}

//添加新的播放列表
void MusicSongsSummarizied::slotAddNewPlayList()
{
    //对数新建列表个数进行限制
    if (m_mainSongLists.count() > 10)
    {
        myHelper::ShowMessageBoxInfo("所添加列表数目已经达到最大值，请删除后在添加!");
        return;
    }
    m_newPlayListNum++;
    MusicSongsListWidget *newList = new MusicSongsListWidget(this);
    m_mainSongLists.append(newList);
    addItem(newList,QString("新建列表%1").arg(m_newPlayListNum));

    //对新建的列表右键菜单进行关联
    for(int i = m_newPlayListNum + 2;i < m_mainSongLists.count();i++)
    {
        connect(m_mainSongLists.at(i),SIGNAL(signalPlayMusic(QString)),
                this,SLOT(slotPlayMusic(QString)));
        connect(m_mainSongLists.at(i),SIGNAL(signalPlayMusic()),
                this,SLOT(slotPlayMusic()));
        connect(m_mainSongLists.at(i),SIGNAL(signalAddMusic()),
                this,SLOT(slotAddMusic()));
    }
}

//打开添加音乐对话框，添加音乐
void MusicSongsSummarizied::slotAddMusic()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles );
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilters(myHelper::supportFormatsFilterDialogString());

    if(dialog.exec())
    {
        //导入歌曲名称
        importMusicSongsName(dialog.selectedFiles());
        //导入歌曲名称和路径(程序需要保存歌曲信息时，需要将歌曲的路径存入数据库中，这里暂时没有用到数据库)
        //musicImportSongsSettingPath(dialog.selectedFiles());
    }
}

void MusicSongsSummarizied::slotAddMusicFolder()
{
}

/*删除列表
 * 在删除列表时：1.默认列表不允许删除；
 *             2.若列表中有歌曲存在，给出提示，是否删除，否则直接删除，没有提示
 */
void MusicSongsSummarizied::slotDeletePlayList()
{
    int index = currentIndex();
    if (index == 0 ||  index ==  1 || index == 2 )
    {
        myHelper::ShowMessageBoxError("默认列表不能删除!");
        return;
    }else if (!m_mainSongLists.at(index)->tableWidgetIsEmpty())
    {
        if (myHelper::ShowMessageBoxQuesion("列表不为空，是否要删除?"))
        {
            removeItem(index);
            m_mainSongLists.removeAt(index);
        }else
            return;
    }else
    {
        removeItem(index);
        m_mainSongLists.removeAt(index);
    }
}

void MusicSongsSummarizied::slotRename()
{
    int index = currentIndex();

    if (index == 0 || index == 1 || index == 2)
    {
        myHelper::ShowMessageBoxError("默认播放列表不能修改!");
        return;
    }
    if (!m_renameLine)
    {
        m_renameIndex = currentIndex();
        m_renameLine = new MusicSongsToolItemRenamedWidget(m_renameIndex*26,
                                                           QToolBox::itemText(m_renameIndex),this);
        connect(m_renameLine,SIGNAL(signalRenameFinished(QString)),
                this,SLOT(slotSetChangItemName(QString)));
        m_renameLine->show();
    }
}

//这里真正改变了列表名称
void MusicSongsSummarizied::slotSetChangItemName(const QString &name)
{
    setItemText(m_renameIndex,name);
    delete m_renameLine;
    m_renameLine = NULL;
}

//删除当前鼠标所点击的音乐
void MusicSongsSummarizied::slotDeleteMusic()
{
    int index = currentIndex();
    if (m_mainSongLists.at(index)->tableWidgetIsEmpty())
    {
        return;
    }else
    {
        m_mainSongLists.at(index)->removeItem();
    }
}

//删除本列表中的所有音乐
void MusicSongsSummarizied::slotDeleteAllMusic()
{
    //获取当前列表
    int index = currentIndex();
    if (!m_mainSongLists.at(index)->tableWidgetIsEmpty())
    {
        m_mainSongLists.at(index)->removeAllItem();
    }
}

void MusicSongsSummarizied::slotChangeListStatus()
{
}
