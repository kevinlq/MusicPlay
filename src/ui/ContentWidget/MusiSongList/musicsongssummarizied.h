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
#ifndef MUSICSONGSSUMMARIZIED_H
#define MUSICSONGSSUMMARIZIED_H

#include <QToolBox>
class MusicSongsListWidget;
class SongMenu;
class MusicSongsToolItemRenamedWidget;

class MusicSongsSummarizied : public QToolBox
{
    Q_OBJECT
public:
    explicit MusicSongsSummarizied(QWidget *parent = 0);
    virtual ~MusicSongsSummarizied();

    //导入歌曲
    void importMusicSongsName(const QStringList &file_name_list);
    void importMusicSongs(const QStringList &file_list);
    void musicImportSongsSettingPath(const QStringList &path);

private:
    void initForm();
    void initWidget();
    void initMusicActionConnect();
    void initConnect();
    //关联歌曲列表(用于第一次请求播放时的关联)
    void connectMusicList(int index);

    QString getCurPlayListName()const;             //返回当前播放列表名称
    void changeItemIcon();
    void clearAllLists();                           //清除所有的列表内容

protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);
Q_SIGNALS:
    void signalDeletePlayList();                    //删除某个列表时发出信号
    //发送要播放的音乐(包括音乐具体信息,在contentWidget类中关联此信号)
    void signalPlayMusic(QString music);

    //请求歌曲列表，请求下一首歌曲和上一首歌曲
    void signalRequestNextMusic();
    void signalRequestPreviousMusic();
    //向下层发送歌曲信息
    void signalSendNextMusic(const QString &);
    void signalSendPreviousMusic(const QString &);

    /************第一次播放时，请求播放信息***************/
    void signalRequestFirstPlayMusic();
    //请求成功后，下下层发送所请求的歌曲信息
    void signalSendFirstPlayMusic(const QString &);

    //根据播放模式请求播放的歌曲
    void signalRequestPlayCmd(int);
    void signalSendPlayCmdMusic(const QString &);

private Q_SLOTS:
    void slotShowCurPlayList(int index);
    void slotPlayMusic();                           //播放音乐
    void slotPlayMusic(const QString&name);         //播放音乐--参数为音乐名称
    void slotAddNewPlayList();                      //添加播放列表
    void slotAddMusic();                            //添加歌曲
    void slotAddMusicFolder();                      //添加歌曲文件夹
    void slotDeletePlayList();                      //删除播放列表
    void slotRename();                              //重命名列表
    void slotSetChangItemName(const QString&name);

    void slotDeleteMusic();                         //删除音乐
    void slotDeleteAllMusic();                      //删除本列表所有音乐

    void slotChangeListStatus();                    //当删除列表是，改变列表参数

private:
    int m_currentIndexs;                            //当前索引
    int m_renameIndex;                              //当前要重命名的索引
    QString m_curPlayListName;                      //当前播放列表名称
    int m_PlayListNum;                              //播放列表数量
    quint8 m_newPlayListNum;                        //新建列表编号
    QList<MusicSongsListWidget *>m_mainSongLists;
    MusicSongsToolItemRenamedWidget *m_renameLine;  //重命名输入框
    SongMenu *m_menu;
};

#endif // MUSICSONGSSUMMARIZIED_H
